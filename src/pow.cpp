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

    for (int64_t i = 1; i <= N; ++i) {
        arith_uint256 target;
        target.SetCompact(pindex->nBits);
        sum_target += target / N;

        int64_t solvetime = pindex->GetBlockTime() - pindex->pprev->GetBlockTime();
        if (solvetime > 6 * T) solvetime = 6 * T;
        if (solvetime < -6 * T) solvetime = -6 * T;

        sum_weighted_solvetimes += solvetime * i;
        pindex = pindex->pprev;
    }

    if (sum_weighted_solvetimes < 1) sum_weighted_solvetimes = 1;

    arith_uint256 next_target = (sum_target * sum_weighted_solvetimes) / k;

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
        if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing * 2)
            return nProofOfWorkLimit;
        else
        {
            const CBlockIndex* pindex = pindexLast;
            while (pindex->pprev && pindex->nBits == nProofOfWorkLimit)
                pindex = pindex->pprev;
            return pindex->nBits;
        }
    }

    return LWMASolvetimes(pindexLast, params);
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
