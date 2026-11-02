// Copyright (c) 2026 The Obsidian developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_YESPOWER_HASH_H
#define BITCOIN_CRYPTO_YESPOWER_HASH_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int yespower_hash(const char *input, size_t input_len, char *output);

#ifdef __cplusplus
}
#endif

#endif // BITCOIN_CRYPTO_YESPOWER_HASH_H
