// Copyright (c) 2026 The Obsidian developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <crypto/yespower-hash.h>
#include <crypto/yespower/yespower.h>

int yespower_hash(const char *input, size_t input_len, char *output)
{
    static const yespower_params_t params = {
        YESPOWER_1_0,
        2048,
        32,
        (const uint8_t *)"Obsidian",
        8
    };
    return yespower_tls((const uint8_t *)input, input_len, &params, (yespower_binary_t *)output);
}
