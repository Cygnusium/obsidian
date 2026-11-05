// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>

// LWMA-1 (Linear Weighted Moving Average - Zawy v8)
// Fast, robust difficulty algorithm resistant to hash hopping and NiceHash bursts.
unsigned int LWMASolvetimes(const CBlockIndex* pindexLast, const Consensus::Params& params)
{
    const int64_t T = params.nPowTargetSpacing;
    const int64_t N = 45;
    const int64_t k = N * (N + 1) * T / 2;
    const arith_uint256 powLimit = UintToArith256(params.powLimit);

    if (pindexLast->nHeight < N) {
        return powLimit.GetCompact();
    }

    arith_uint256 sum_target;
    int64_t sum_weighted_solvetimes = 0;
    const CBlockIndex* pindex = pindexLast;

    // Walk backwards from most recent block (i = 1, weight = N) to oldest block in window (i = N, weight = 1)
    for (int64_t i = 1; i <= N; ++i) {
        const int64_t weight = N - i + 1;
        arith_uint256 target;
        target.SetCompact(pindex->nBits);
        sum_target += target / N;

        int64_t solvetime = pindex->GetBlockTime() - pindex->pprev->GetBlockTime();
        if (solvetime > 6 * T) solvetime = 6 * T;
        if (solvetime < -6 * T) solvetime = -6 * T;

        sum_weighted_solvetimes += solvetime * weight;
        pindex = pindex->pprev;
    }

    // Clamp minimum weighted solvetimes to k / 3 to cap single-block difficulty increases at 3x
    const int64_t min_weighted_solvetimes = k / 3;
    if (sum_weighted_solvetimes < min_weighted_solvetimes) {
        sum_weighted_solvetimes = min_weighted_solvetimes;
    }

    // Divide by k before multiplying by sum_weighted_solvetimes to prevent 256-bit arith_uint256 overflow
    arith_uint256 next_target = (sum_target / k) * sum_weighted_solvetimes;

    if (next_target > powLimit || next_target == 0) {
        next_target = powLimit;
    }

    return next_target.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    assert(pindexLast != nullptr);
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    if (params.fPowAllowMinDifficultyBlocks)
    {
        // Special difficulty rule for testnet:
        if (pblock && pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing * 2)
            return nProofOfWorkLimit;
        else
        {
            const CBlockIndex* pindex = pindexLast;
            while (pindex->pprev && pindex->nBits == nProofOfWorkLimit)
                pindex = pindex->pprev;
            return pindex->nBits;
        }
    }

    unsigned int nBitsRequired = LWMASolvetimes(pindexLast, params);

    // Emergency Difficulty Adjuster (EDA):
    // If a large hashrate burst leaves and no block is found for >= 6 * T (3 minutes),
    // progressively scale the target easier in discrete 2 * T (60-second) steps so
    // remaining CPU miners can recover the chain without getting stuck, while keeping
    // nBits constant within each 60-second window so miner nTime rolling stays valid.
    const int64_t T = params.nPowTargetSpacing;
    if (pblock != nullptr && pblock->GetBlockTime() >= pindexLast->GetBlockTime() + 6 * T) {
        const int64_t eda_steps = (pblock->GetBlockTime() - pindexLast->GetBlockTime() - 4 * T) / (2 * T);
        const arith_uint256 powLimit = UintToArith256(params.powLimit);
        arith_uint256 target;
        target.SetCompact(nBitsRequired);

        // Increase target by 25% (target += target >> 2) for each 2 * T (60-second) step
        for (int64_t s = 0; s < eda_steps; ++s) {
            arith_uint256 delta = target >> 2;
            if (target > powLimit - delta) {
                target = powLimit;
                break;
            }
            target += delta;
        }

        if (target > powLimit || target == 0) {
            target = powLimit;
        }
        return target.GetCompact();
    }

    return nBitsRequired;
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    return LWMASolvetimes(pindexLast, params);
}

bool PermittedDifficultyTransition(const Consensus::Params& params, int64_t height, uint32_t old_nbits, uint32_t new_nbits)
{
    return true;
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
