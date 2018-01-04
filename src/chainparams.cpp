// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0xc6c74b1a, 0x6baaffeb, 0xa2f3d1bc, 0xb6e287b5, 0xbce237b8, 0x688367e5, 0xb23a116a, 0x81c789bb,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0x26;
        pchMessageStart[3] = 0xda;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 55444;
        nRPCPort = 55443;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;

        // PoSV
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        nLastProofOfWorkHeight = 120;
        nStakeMinAge = 12 * 60 * 60; // 16 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        // Genesis Block:
        // CBlock(hash=12a765e31ffd4059bada, PoW=0000050c34a64b415b6b, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=97ddfbbae6, nTime=1317972665, nBits=1e0ffff0, nNonce=2084524493, vtx=1)
        //   CTransaction(hash=97ddfbbae6, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d0104404e592054696d65732030352f4f63742f32303131205374657665204a6f62732c204170706c65e280997320566973696f6e6172792c2044696573206174203536)
        //     CTxOut(nValue=50.00000000, scriptPubKey=040184710fa689ad5023690c80f3a4)
        //   vMerkleTree: 97ddfbbae6
        const char* pszTimestamp = "January 3rd 2017 was such a odd day...";
        CTransaction txNew(1514999815);
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1514999815;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 3696673;

        // If genesis block hash does not match, then generate new genesis hash.
//         if (true && genesis.GetHash() != hashGenesisBlock)
//         {
//             printf("Searching for genesis block...\n");
//             // This will figure out a valid hash and Nonce if you're
//             // creating a different genesis block:
//             uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
//             uint256 thash;
//             char scratchpad[SCRYPT_SCRATCHPAD_SIZE];
 
//             while(true)
//             {
// #if defined(USE_SSE2)
//                 // Detection would work, but in cases where we KNOW it always has SSE2,
//                 // it is faster to use directly than to use a function pointer or conditional.
// #if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
//                 // Always SSE2: x86_64 or Intel MacOS X
//                 scrypt_1024_1_1_256_sp_sse2(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
// #else
//                 // Detect SSE2: 32bit x86 Linux or Windows
//                 scrypt_1024_1_1_256_sp(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
// #endif
// #else
//                 // Generic scrypt
//                 scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
// #endif
//                 if (thash <= hashTarget)
//                     break;
//                 if ((genesis.nNonce & 0xFFF) == 0)
//                 {
//                     LogPrintf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
//                 }
//                 ++genesis.nNonce;
//                 if (genesis.nNonce == 0)
//                 {
//                     LogPrintf("NONCE WRAPPED, incrementing time\n");
//                     ++genesis.nTime;
//                 }
//             }
//             LogPrintf("block.nTime = %u \n", genesis.nTime);
//             LogPrintf("block.nNonce = %u \n", genesis.nNonce);
//             LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
//         }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd9e128be81987a6878f54775494806885ac007a060161a954a33172046c4a5fc"));
        assert(genesis.hashMerkleRoot == uint256("0xbaacbd35f57d1a863ca824c32e38dcaf2a67b44d89f72e324ad566af85a47cc8"));

        vSeeds.push_back(CDNSSeedData("104.131.33.106", "104.131.33.106"));
        vSeeds.push_back(CDNSSeedData("95.85.38.235", "95.85.38.235"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,189);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 55444;
        nRPCPort = 55443;
        strDataDir = "testnet3";
        nLastProofOfWorkHeight = 350 - 1; // Last POW block

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        // CTransaction txGenesis = genesis.vtx[0];
        genesis.nTime = 1446002303;
        // genesis.vtx[0] = txGenesis;
        genesis.nNonce = 1632510;
        //GENESIS HASH
//         hashGenesisBlock = uint256("0x01");
//         if (genesis.GetHash() != hashGenesisBlock)
//         {
//             LogPrintf("recalculating params for mainnet.\n");
//             LogPrintf("old mainnet genesis nonce: %u\n", genesis.nNonce);
//             LogPrintf("old mainnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
//             // deliberately empty for loop finds nonce value.
//             for(genesis.nNonce = 0; CBigNum(genesis.GetHash()) > bnProofOfWorkLimit; genesis.nNonce++){ } 
//             LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
//             LogPrintf("new mainnet genesis nonce: %u\n", genesis.nNonce); 
//             LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
//         }
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e6b14f384cb234d90a6b1e81209fed84e7652b053e39770669c5a6569ad"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("coinking.com", "testnet-seed.coinking.com"));
        vSeeds.push_back(CDNSSeedData("redd.ink", "testnet-dnsseed.redd.ink"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xdf;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = bnProofOfStakeLimit = CBigNum(~uint256(0) >> 1);
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1401051600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        strDataDir = "regtest";
        
        assert(hashGenesisBlock == uint256("0x37ef43504ca1878a897ce067937c952372998aa615670367c218c44b189d8303"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
