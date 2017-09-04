// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
/*
#include <stdio.h>
#include "hash.h"
#include "scrypt.h"
bool static ScanHash(CBlock* pblock, uint256& thash)
{
    uint256 hashTarget = CBigNum().SetCompact(pblock->nBits).getuint256();
    while(true)
    {
        pblock->nNonce +=1;
        thash = scrypt_blockhash(CVOIDBEGIN(pblock->nVersion));
        if(thash <= hashTarget)
            break;
    }
    return true;
}
        uint256 hash;
        if(ScanHash(&genesis, hash))
        {
            printf("nonce: %lld\n", genesis.nNonce);
            printf("hash: %s\n", hash.ToString().data());
            printf("genesis.hash: %s\n", genesis.GetHash().ToString().data());
            printf("genesis.merkle: %s\n", genesis.hashMerkleRoot.ToString().data());
        }
*/
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xec;
        pchMessageStart[1] = 0xe5;
        pchMessageStart[2] = 0xed;
        pchMessageStart[3] = 0xe2;
        vAlertPubKey = ParseHex("04a8dc25b4dde15260549dd3991139ce283ded007c6cbd83649387b09c9ccd17f28b0d6ae0603f27773f40ea13f5158568545575cfd7740618f7e4a822fdef49bd");
        nDefaultPort = 12357;
        nRPCPort = 12358;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 12);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "election chain";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1501664400, vin, vout, 0); // 2017-08-02 00:00:00 UTC+8
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1501664400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 304;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0006ea19b656e7f70cf6b28c11fdf63e68153079071bd240c056b919bf1369b3"));
        assert(genesis.hashMerkleRoot == uint256("0x023dd42ec0ab5154fc97dd309feee9711938142ff10d3cdd3dd5ec57d31be122"));

        vSeeds.push_back(CDNSSeedData("118.190.119.135", "118.190.119.135"));
        vSeeds.push_back(CDNSSeedData("47.94.44.131", "47.94.44.131"));
        vSeeds.push_back(CDNSSeedData("101.37.161.102", "101.37.161.102"));
        vSeeds.push_back(CDNSSeedData("101.132.24.151", "101.132.24.151"));
        vSeeds.push_back(CDNSSeedData("106.14.56.134", "106.14.56.134"));
        vSeeds.push_back(CDNSSeedData("39.108.195.99", "39.108.195.99"));
        vSeeds.push_back(CDNSSeedData("39.108.195.47", "39.108.195.47"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(93).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY] =     list_of(251).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 5000;
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe2;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xee;
        pchMessageStart[3] = 0xeb;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 10);
        vAlertPubKey = ParseHex("04b99534f71e0f874e3ed9c804873605be75efb5ede2937467e86062ed471cecf0f59d8a77270e30a7e4856e8205b17d8b97ca660875ab3949f19c171d27ca6ede");
        nDefaultPort = 22357;
        nRPCPort = 22358;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1104;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000f99221919262a0fb712f84b7488f43a8c5561baea963c69ac7a089b66335e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(93).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(251).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0xffffffff;
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
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xb7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 32357;
        nRPCPort = 32358;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x797cc25f8640768648737ca1029790170e5fa080404e9bf6540cc3f1bcc2bb0a"));

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
