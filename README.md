<div align="center">

# Obsidian Core (OSD)
### *Next-Generation Anti-ASIC, High-Speed Layer-1 Blockchain for Global Commerce*

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/Language-C%2B%2B17-00599C.svg)](https://isocpp.org/)
[![PoW: Yespower 1.0](https://img.shields.io/badge/PoW-Yespower%201.0%20(CPU)-darkgreen.svg)](https://www.openwall.com/yespower/)
[![Difficulty: LWMA-1](https://img.shields.io/badge/Difficulty-LWMA--1%20(Zawy)-orange.svg)]()
[![Block Time: 30s](https://img.shields.io/badge/Block%20Time-30%20Seconds-purple.svg)]()
[![Max Supply: 45M](https://img.shields.io/badge/Max%20Supply-45%2C000%2C000%20OSD-gold.svg)]()

**Official Website**: [https://obsidian.cygnusium.com](https://obsidian.cygnusium.com)  
**Organization**: **Cygnusium LLC**  
**Lead Developer & Architect**: **MrHat**

---

</div>

## 1. Vision & Philosophy

**Obsidian (OSD)** is an independent, decentralized, proof-of-work cryptocurrency engineered from the ground up to solve the three core limitations facing legacy blockchains:

1. **Everyday Commerce & Rapid Confirmation**:
   Legacy chains with 10-minute (Bitcoin) or 2.5-minute (Litecoin) block intervals force merchants and consumers to wait up to an hour for transaction certainty. Obsidian features an optimized **30-second block target**, enabling near-instant transaction finality ideal for point-of-sale payments, microtransactions, and high-frequency digital commerce.
2. **Democratized, ASIC-Resistant CPU Mining**:
   Centralized ASIC mining farms and FPGA cartels undermine true Satoshi-style decentralization. Obsidian deploys **Yespower 1.0** with a custom `"Obsidian"` personalization matrix. Requiring 2 MB of memory per thread, Yespower saturates on-die CPU L3 caches, neutralizing specialized hardware and enabling any standard computer or laptop to actively participate in consensus.
3. **Hash-Hopping & Stall Resilience**:
   Smaller proof-of-work networks are often vulnerable to sudden hashrate spikes and abandonments from rental pools. Obsidian solves this with a two-stage difficulty defense system:
   - **LWMA-1 Per-Block Retargeting**: Linearly weights the most recent 45 blocks (giving the newest block weight 45 down to weight 1 for the oldest), responding to hashrate spikes within single-digit blocks while preventing timestamp manipulation.
   - **Emergency Difficulty Adjuster (EDA)**: If a massive hashrate burst suddenly disconnects and no block is found for more than 3 minutes ($6 \times T$), target difficulty automatically scales down in real time so CPU miners never face a frozen chain.

---

## 2. Blockchain Specifications

| Parameter | Specification | Details |
| :--- | :--- | :--- |
| **Blockchain Name** | **Obsidian** | Native Layer-1 Proof-of-Work Blockchain |
| **Ticker Symbol** | **OSD** | Primary currency denomination |
| **Base Sub-Unit** | **Sidian (sid)** | $1\text{ OSD} = 100{,}000{,}000\text{ Sidians}$ |
| **Unit Hierarchy** | **OSD, mOSD, µOSD, Sidian** | Full native decimal precision |
| **Block Target Spacing** | **30 seconds** | Rapid transaction confirmations |
| **Initial Block Subsidy** | **10 OSD** | Sustainable initial yield for network participants |
| **Subsidy Halving Interval** | **2,250,000 blocks** | Halving era every ~2.14 years |
| **Total Maximum Supply** | **45,000,000 OSD** | Exact geometric progression: $2{,}250{,}000 \times 10 \times 2$ |
| **Proof-of-Work Algorithm** | **Yespower 1.0 (Obsidian)** | Memory-hard ($N=2048, r=32$, 2MB RAM footprint per thread) |
| **PoW Personalization Salt** | `"Obsidian"` | Prevents cross-chain hash replay and collision |
| **Difficulty Algorithm** | **LWMA-1 (Zawy v8) + EDA** | Per-block real-time difficulty retargeting (45-block window) + anti-stall decay |
| **Coinbase Maturity** | **100 blocks** | Standard security threshold for mined coins |
| **Native Address Format** | **Bech32 Native SegWit** | Mainnet prefix: `osd1q...` |
| **Testnet Address Format** | **Bech32 Native SegWit** | Testnet prefix: `tosd1q...` |
| **Regtest Address Format** | **Bech32 Native SegWit** | Regtest prefix: `rosd1q...` |
| **Mainnet P2P / RPC Ports** | **18833 / 18832** | Default communication ports |
| **Testnet P2P / RPC Ports** | **28833 / 28832** | Public testbed ports |
| **Regtest P2P / RPC Ports** | **18444 / 18443** | Local private testing sandbox ports |

---

## 3. Sub-Unit Hierarchy: The Sidian

Like Bitcoin's satoshi, Obsidian coins are divisible down to 8 decimal places:

$$\begin{aligned}
1\text{ OSD} &= 1.00000000\text{ Obsidian} \\
1\text{ mOSD} &= 0.00100000\text{ Milli-Obsidian} \\
1\text{ µOSD} &= 0.00000100\text{ Micro-Obsidian (bits)} \\
1\text{ Sidian} &= 0.00000001\text{ Sidian (sid)}
\end{aligned}$$

---

## 4. Genesis Blocks

All Obsidian genesis blocks were custom-mined with the immutable genesis headline:
> **`"Obsidian 03/Nov/2026 The Fast Anti-ASIC Secure CPU Blockchain"`**

- **Merkle Root**: `0xc678af7f5353d97f340e834bd2f52d685ae988d64bf08c913d6d2837836174db`

### Network Genesis Details
- **Mainnet**:
  - Hash: `0x9c1dc64d2aa5d7fea3964b3da93e4ece7d3fc444c22e67a0995e9c05af38de6d`
  - PoW Hash: `0x000048da4a3de6a41a773b3bc57e6759239cc0311268f06be208d06e836eca92`
  - Nonce: `6932` | nBits: `0x1f00ffff` | Timestamp: `1793654584`
- **Testnet**:
  - Hash: `0x9c1dc64d2aa5d7fea3964b3da93e4ece7d3fc444c22e67a0995e9c05af38de6d`
  - Nonce: `6932` | nBits: `0x1f00ffff` | Timestamp: `1793654584`
- **Regtest**:
  - Hash: `0xa8de02a321a753bd4631caba8f2c0cd605a96d39b3fa494a3706227206790d70`
  - Nonce: `5` | nBits: `0x207fffff` | Timestamp: `1793654584`

---

## 5. Building Obsidian From Source

### Dependencies

#### Debian / Ubuntu / Mint:
```bash
sudo apt-get update
sudo apt-get install build-essential libtool autotools-dev automake pkg-config bsdmainutils python3 \
                     libevent-dev libboost-dev libboost-system-dev libboost-filesystem-dev libboost-test-dev \
                     libsqlite3-dev libzmq3-dev qtbase5-dev qttools5-dev-tools libqrencode-dev
```

#### Arch Linux / Manjaro / CachyOS:
```bash
sudo pacman -S base-devel boost libevent sqlite zeromq qt5-base qt5-tools qrencode
```

#### Fedora / RHEL:
```bash
sudo dnf install gcc-c++ libtool make autoconf automake pkgconfig python3 \
                 libevent-devel boost-devel sqlite-devel zeromq-devel qt5-qtbase-devel qt5-linguist qrencode-devel
```

### Build Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/obsidian-chain/obsidian.git
   cd obsidian
   ```

2. **Generate build configuration**:
   ```bash
   ./autogen.sh
   ```

3. **Configure the build**:
   ```bash
   # Standard configuration with GUI and wallet:
   ./configure --with-gui=qt5

   # Or Headless Server Node (No GUI):
   ./configure --without-gui
   ```

4. **Compile using all CPU cores**:
   ```bash
   make -j$(nproc)
   ```

5. **Verify compiled binaries** in `src/`:
   - `obsidiand`: Full node headless daemon
   - `obsidian-qt`: Full graphical Qt desktop wallet
   - `obsidian-cli`: RPC client utility
   - `obsidian-tx`: Offline transaction crafting tool
   - `obsidian-wallet`: Offline wallet management tool

---

## 6. Running an Obsidian Full Node

### Configuration File (`obsidian.conf`)

By default, the daemon reads configuration from:
- **Linux**: `~/.obsidian/obsidian.conf`
- **macOS**: `~/Library/Application Support/Obsidian/obsidian.conf`
- **Windows**: `%APPDATA%\Obsidian\obsidian.conf`

Create the data directory and configuration file:
```bash
mkdir -p ~/.obsidian
nano ~/.obsidian/obsidian.conf
```

Add standard production parameters:
```ini
# Obsidian Network Configuration
server=1
daemon=1
listen=1
txindex=1

# RPC Settings
rpcuser=obsidianrpc
rpcpassword=CHANGEME_SECURE_STRONG_PASSWORD_HERE
rpcport=18832
rpcallowip=127.0.0.1

# Performance
dbcache=450
maxconnections=64
```

### Starting the Daemon
```bash
./src/obsidiand -daemon
```

### Checking Node Status
```bash
./src/obsidian-cli getblockchaininfo
./src/obsidian-cli getnetworkinfo
```

### Stopping the Node
```bash
./src/obsidian-cli stop
```

---

## 7. Using the Graphical Desktop Wallet (`obsidian-qt`)

Launch the Obsidian Qt graphical wallet:
```bash
./src/obsidian-qt
```

Features included in the Obsidian GUI:
- **Obsidian Dark & Clean Visual Branding** with custom icon assets.
- **Accurate Unit Selector**: Choose between `OSD`, `mOSD`, `µOSD`, and `Sidian (sid)` on the bottom status bar.
- **Send & Receive**: Generate native `osd1q...` Bech32 addresses with QR codes.
- **Coin Control**: Granular UTXO selection, fee management, and lock control.
- **Interactive RPC Console**: Accessible via `Help -> Debug window -> Console`.

---

## 8. Mining Obsidian (OSD)

Obsidian is strictly memory-hard and CPU-mined using **Yespower 1.0**.

### Method 1: Mining Directly From the Terminal (Node RPC)

For private testing, testnets, or self-hosted mining nodes, Obsidian Core includes native block generation commands.

#### Step 1: Create a wallet and get a mining payout address
```bash
./src/obsidian-cli createwallet "miner"
export MINING_ADDR=$(./src/obsidian-cli getnewaddress)
echo "Mining to address: $MINING_ADDR"
```

#### Step 2: Mine a single block or multiple blocks
```bash
# Mine 1 block:
./src/obsidian-cli generatetoaddress 1 "$MINING_ADDR"

# Mine 100 blocks:
./src/obsidian-cli generatetoaddress 100 "$MINING_ADDR"
```

#### Step 3: Continuous Automated Terminal Mining Script
To continuously mine new blocks automatically in the background using your CPU:

```bash
#!/bin/bash
# Continuous Obsidian CPU Miner
WALLET_ADDR="osd1qYourAddressHere"

echo "Starting continuous CPU miner on Obsidian..."
while true; do
    RESULT=$(./src/obsidian-cli generatetoaddress 1 "$WALLET_ADDR" 2>&1)
    if [[ $RESULT == *"["* ]]; then
        BLOCK_HASH=$(echo "$RESULT" | grep -o '"[0-9a-f]*"' | tr -d '"')
        echo "[$(date '+%Y-%m-%d %H:%M:%S')] Mined block successfully! Hash: $BLOCK_HASH"
    else
        echo "[$(date '+%Y-%m-%d %H:%M:%S')] Mining attempt: $RESULT"
        sleep 1
    fi
done
```

---

### Method 2: High-Performance Standalone CPU Mining

For production mining, you can use any modern Yespower-capable miner (such as `cpuminer-opt` or `SRBMiner-MULTI`):

1. **Configure `obsidian.conf`** with RPC credentials and server enabled:
   ```ini
   server=1
   rpcuser=mineruser
   rpcpassword=minerpass
   rpcallowip=127.0.0.1
   rpcport=18832
   ```

2. **Launch cpuminer-opt**:
   ```bash
   cpuminer -a yespower -o http://127.0.0.1:18832 -u mineruser -p minerpass --coinbase-addr=osd1qYourPayoutAddress -t $(nproc)
   ```

---

## 9. Developer Testing Sandbox (Regtest)

To develop apps, test transactions, or simulate network conditions instantly:

1. **Start Regtest Daemon**:
   ```bash
   ./src/obsidiand -regtest -daemon
   ```

2. **Interact with Regtest**:
   ```bash
   ./src/obsidian-cli -regtest createwallet "devwallet"
   ADDR=$(./src/obsidian-cli -regtest getnewaddress)
   # Mine 101 blocks to unlock coinbase maturity:
   ./src/obsidian-cli -regtest generatetoaddress 101 "$ADDR"
   # Verify balance (10 OSD):
   ./src/obsidian-cli -regtest getbalance
   ```

3. **Stop Regtest**:
   ```bash
   ./src/obsidian-cli -regtest stop
   ```

---

## 10. Organization & Credits

- **Developing Organization**: **[Cygnusium LLC](https://obsidian.cygnusium.com)**
- **Lead Developer**: **MrHat**
- **Based on**: Bitcoin Core & Litecoin Project Open-Source Architecture

---

## 11. License

Obsidian Core is released under the terms of the **MIT license**. See [COPYING](COPYING) or [https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT) for more information.
