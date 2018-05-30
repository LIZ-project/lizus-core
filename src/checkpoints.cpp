// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
     (     0, uint256("0xb87084064a7dd33722ddd2c9435692bd2fe8e9937553bd3ead2674e6a0f3c357") )
     ( 1000, uint256("0x00000000000004e90a456c385471e33c732131430167395d3878e492ab0e014a") )
     ( 10000, uint256("0x1151599b6e5220e7386de81948c879849172d410dc06edb35b0eb4ae93ec53be") )
     ( 50000, uint256("0x000000000000fe86c41210b620a87420e5bb52b522085f6a45835f6302b7152b") )
     ( 100000, uint256("0x05d2eb866b4336440b7abcd03160c12a4fe1c714663a7516c989909b08f2fe41") )
     ( 140000, uint256("0x0000000000055f92b81fd93b9549765992b6827018c81fe03fc594d96f19f569") )
     ( 155000, uint256("0x00000000001087891767a571e6ef13e5e09a32ebd92be35941dcca05af648b40") )
     ( 250000, uint256("0x00000000000030691ac6538ad577d774855089e24d2a91ff251992ac89263cc8") )
     ( 251000, uint256("0x00000000003ced020ddd7c8fd9ad8ce81167f575b595de5c78b28ce7d8fb0162") )
     ( 252000, uint256("0x090ed0ed3cd7d2a691038efff634e3bc5d0f754342a5726fbce61e0b70d9e5bb") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
