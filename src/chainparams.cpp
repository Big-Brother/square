// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The D*a*sh Core developers
// Copyright (c) 2018- The Square Core developers
// Copyright (c) 2018- The Square Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    
    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 *
 CBlock(hash=000009ce3dbc7226f90591453e668d25b37b019b6f1495d37470d43ed793055e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8, nTime=1517756773, nBits=1e0ffff0, nNonce=6219155, vtx=1)
 CTransaction(hash=6340383f63, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043f30342e30322e32303138202d20426974636f696e20696e766573746f72732066696e64207461782064656d616e647320617265206e6f74207669727475616c)
 CTxOut(nValue=10.00000000, scriptPubKey=4104dbf05d8d9b3ab05aab794df8fa)
 vMerkleTree: 634038
 */

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "04.02.2018 - Bitcoin investors find tax demands are not virtual";
    const CScript genesisOutputScript = CScript() << ParseHex("04dbf05d8d9b3ab05aab794df8fab204b254fa917ad0189ca8ed357cbef5aacb6c9878558b4f6e485484e3b9f5ac47116944e19945037779e26a5cc16ef88fb8d3") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210240; // Note: actual number of blocks per calendar year with DGW v3 is ~200700 (for example 449750 - 249050)
        consensus.nMasternodePaymentsStartBlock = 100000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 158000; // actual historical value
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // 17280 - actual historical value
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 328008; // actual historical value
        consensus.nBudgetPaymentsCycleBlocks = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 100; // The block at which 12.1 goes live (end of final 12.0 budget cycle)
        consensus.nSuperblockCycle = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x000009ce3dbc7226f90591453e668d25b37b019b6f1495d37470d43ed793055e"); // genesis hash if want to start from 0
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Square: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Square: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 15200;
        consensus.nPowDGWHeight = 34140;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        //consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1522553613; // Sunday, 1 April 2018 03:33:33
        //consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1543635213; // Saturday, 1 December 2018 03:33:33
        
        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1518187550; // Friday, 9 February 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1549811869; // Saturday, 10 February 2019
        //consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1529552013; // Thursday, 21 June 2018 03:33:33
        //consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1561088013; // Friday, 21 June 2019 03:33:33
        
        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1545708813; // 25 December 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1577244813; // 25 December 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032
        
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // 0
        
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000009ce3dbc7226f90591453e668d25b37b019b6f1495d37470d43ed793055e"); // genesis
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0xec;
        pchMessageStart[2] = 0xe1;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("0445aa0ac5e6d9302486f761bdde59f1982e4985d7d35b1958b68ee1744e8bd5f2638aaef803167b86bce80b7ccd5a582b2abb5a52023062554c88eb4af4f46ddb");
        nDefaultPort = 6666;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        
        genesis = CreateGenesisBlock(1517756773, 6219155, 0x1e0ffff0, 1, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        assert(consensus.hashGenesisBlock == uint256S("0x000009ce3dbc7226f90591453e668d25b37b019b6f1495d37470d43ed793055e"));
        assert(genesis.hashMerkleRoot == uint256S("0x6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8"));
        
        
        vSeeds.push_back(CDNSSeedData("cryptoseeds.xyz", "seeds.cryptoseeds.xyz"));
        
        // Square addresses start with 'X'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);
        // Square script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        // Square private keys start with '7' or 'X'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        // Square BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Square BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        
        // Square BIP44 coin type is '5'
        nExtCoinType = 5;
        
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04e12501b5d787cbf2ffe78758f63a2d3d0bd205d0467d63bda7dae054ccf529001b09767c98a10c29a9ccd679beaa30ce3ec5057d041e772fdd5eacd2195a19a4";
        
        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x000009ce3dbc7226f90591453e668d25b37b019b6f1495d37470d43ed793055e")),
            1517756773, // * UNIX timestamp of last checkpoint block
            0,    // * total number of transactions between genesis and last checkpoint
            //   (the tx=... number in the SetBestChain debug.log lines)
            5000        // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
/**
 *
 CBlock(hash=000001f59bc87b58d6aa505b724e84b7df9ddafee7269bde78fe712654e6d2ea, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8, nTime=1517756706, nBits=1e0ffff0, nNonce=1388910, vtx=1)
 CTransaction(hash=6340383f63, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043f30342e30322e32303138202d20426974636f696e20696e766573746f72732066696e64207461782064656d616e647320617265206e6f74207669727475616c)
 CTxOut(nValue=10.00000000, scriptPubKey=4104dbf05d8d9b3ab05aab794df8fa)
 
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210240;
        consensus.nMasternodePaymentsStartBlock = 4010; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 4030;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 4100;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 4200; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x000001f59bc87b58d6aa505b724e84b7df9ddafee7269bde78fe712654e6d2ea");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Square: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Square: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 4001; // nPowKGWHeight >= nPowDGWHeight means "no KGW"
        consensus.nPowDGWHeight = 4001;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        
        
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        //consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1522553613; // Sunday, 1 April 2018 03:33:33
        //consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1543635213; // Saturday, 1 December 2018 03:33:33
        
        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1518187550; // Friday, 9 February 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1549811869; // Saturday, 10 February 2019
        //consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1529552013; // Thursday, 21 June 2018 03:33:33
        //consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1561088013; // Friday, 21 June 2019 03:33:33
        
        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1545708813; // 25 December 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1577244813; // 25 December 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100
        
        
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // 0
        
        // By default assume that the signatures in ancestors of this block are valid.
        // consensus.defaultAssumeValid = uint256S("0x0000000004f5aef732d572ff514af99a995702c92e4452c7af10858231668b1f"); // 37900
        consensus.defaultAssumeValid = uint256S("0x000001f59bc87b58d6aa505b724e84b7df9ddafee7269bde78fe712654e6d2ea"); // genesis
        
        pchMessageStart[0] = 0xec;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0xfe;
        vAlertPubKey = ParseHex("0436537f340703b9772f2030b29518914fd466685cc18a1ce0344877c4d82086821fafca8c7f8bcf9d5a1c5eb21416a87a3ba3a0f3bcb2e611a710c1a45587f5aa");
        nDefaultPort = 16666;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        
        genesis = CreateGenesisBlock(1517756706UL, 1388910UL, 0x1e0ffff0, 1, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        assert(consensus.hashGenesisBlock == uint256S("0x000001f59bc87b58d6aa505b724e84b7df9ddafee7269bde78fe712654e6d2ea"));
        assert(genesis.hashMerkleRoot == uint256S("0x6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8"));
        
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("cryptoseeds.xyz",  "seeds.cryptoseeds.xyz"));
        
        // Testnet Square addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        // Testnet Square script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Square BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Square BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        
        // Testnet Square BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
        
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04d96271653a89958e17beb02d22babc960dfe2eee6a15b9e375095f26627c613a6e056e514ab7b6c40822dc312d537c19ce6aa6883304dea879026a40b8b5ce03";
        
        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    0, uint256S("0x000001f59bc87b58d6aa505b724e84b7df9ddafee7269bde78fe712654e6d2ea")),
            
            1517756706, // * UNIX timestamp of last checkpoint block
            0,       // * total number of transactions between genesis and last checkpoint
            //   (the tx=... number in the SetBestChain debug.log lines)
            500         // * estimated number of transactions per day after checkpoint
        };
        
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
/**
 *
 CBlock(hash=51554a115eec116070417085ae9e35f5b13a59b5dc30c3b5628e14ba2279cb78, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8, nTime=1517756649, nBits=207fffff, nNonce=16, vtx=1)
 CTransaction(hash=6340383f63, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043f30342e30322e32303138202d20426974636f696e20696e766573746f72732066696e64207461782064656d616e647320617265206e6f74207669727475616c)
 CTxOut(nValue=10.00000000, scriptPubKey=4104dbf05d8d9b3ab05aab794df8fa)
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 0;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Square: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Square: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowKGWHeight = 15200; // same as mainnet
        consensus.nPowDGWHeight = 34140; // same as mainnet
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;
        
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");
        
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");
        
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0xdd;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 16664;
        nPruneAfterHeight = 1000;
        
        genesis = CreateGenesisBlock(1517756649, 16, 0x207fffff, 1, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        assert(consensus.hashGenesisBlock == uint256S("0x51554a115eec116070417085ae9e35f5b13a59b5dc30c3b5628e14ba2279cb78"));
        assert(genesis.hashMerkleRoot == uint256S("0x6340383f63a22962bc62325640d75b3b634c7bfdde046093cde93201dbd1fae8"));
        
        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.
        
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        
        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x51554a115eec116070417085ae9e35f5b13a59b5dc30c3b5628e14ba2279cb78")),
            0,
            0,
            0
        };
        // Regtest Square addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        // Regtest Square script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Regtest Square BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Square BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        
        // Regtest Square BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
