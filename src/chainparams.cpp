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

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}



class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xec;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xc7;
        vAlertPubKey = ParseHex("04ef0114c2f98ffa5ce31beddacec699e1b267888ec2f71ef4e78e007155d23ed38cf5836f8724e23c1dee43dbdefc7a9764f6d93044ced1c29404f35b10d46ea4");
        nDefaultPort = 19700;
        nRPCPort = 19701;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "ChristenUnie denkt aan uitstel opening Lelystad Airport";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1515144189, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1515144189;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 954286;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("b87084064a7dd33722ddd2c9435692bd2fe8e9937553bd3ead2674e6a0f3c357"));
        assert(genesis.hashMerkleRoot == uint256("ce4dff8b93355e2e579775a76297e4ef517d0ef29168eb5428597704e1d32eb4"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,48);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,48);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,80);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,81);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0","188.226.192.178"));
        vSeeds.push_back(CDNSSeedData("1","188.226.189.36"));
        vSeeds.push_back(CDNSSeedData("2","146.185.168.10"));
        vSeeds.push_back(CDNSSeedData("3","188.226.192.182"));
        vSeeds.push_back(CDNSSeedData("4","188.226.192.179"));
        vSeeds.push_back(CDNSSeedData("5","45.76.141.201"));
        vSeeds.push_back(CDNSSeedData("6","199.247.14.227"));
        vSeeds.push_back(CDNSSeedData("7","108.61.177.0"));
        vSeeds.push_back(CDNSSeedData("8","107.191.47.17"));
        vSeeds.push_back(CDNSSeedData("9","45.32.148.192"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        // strSporkKey = "044641223ef068e61bee2f836eaf65a0f364cbd9d634c0b3c4211db1911d885e2cf3836ae2eb9c002827b67de999c71920a33f01ff75161f0ddbea63916d879ae7"
        // strMasternodePaymentsPubKey = "048598d4a1db6a25ae5916d3ceea0144ba9bc6442f7f96e07f49ca224b8e643f54d18d3c78d7dbd04644b55871eab1137d34ac14d2422aaae74ca816bcd470169c"
        strDarksendPoolDummyAddress = "9frEPbxv2ANZzrViEqTCWaBL8S63FQHz9s";
        nLastPOWBlock = 2685000; // 5 years
        nPOSStartBlock = 100;
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
        pchMessageStart[0] = 0x1f;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x05;
        pchMessageStart[3] = 0x30;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0488d4a6bf0e8a0389e904c6026915db6585ebce45d426ed90c2148d2aba7f34ebbd7cde6a85cb2d254d8ac20acf70fe4400885674402715cea1640cce13d027e9");
        nDefaultPort = 19800;
        nRPCPort = 19801;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1515059638+120;
        genesis.nNonce = 112;

       if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        }
        //assert(hashGenesisBlock == uint256("6a7cb13f9c1bdd73bc0a76b7a5034e80716fdf6a13d64b7cd5ccba790c8441e7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,44);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,50);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,52);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);
        // strSporkKey = "04a5afa83fc1d05b02cc191cb4b27a12ec61811650d200173f5fa712b78e4221f236cb3e6f56d46ff8ee7597cadbb54ae37380c78d348dd2995292c6cffbebc3bf"
        // strMasternodePaymentsPubKey = "045608ba481008f7ca6700e56b43b610b4fc660b0d5dddfc62c23dad0107f5dde3a04bf48e28791afe6642ef68b8f12f70eb083a94b4036704120eb6db6b59a533"
        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
