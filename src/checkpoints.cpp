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
      (    0, uint256("0xb87084064a7dd33722ddd2c9435692bd2fe8e9937553bd3ead2674e6a0f3c357") )
      ( 1000, uint256("0x00000000000004e90a456c385471e33c732131430167395d3878e492ab0e014a") )
     ( 10000, uint256("0x1151599b6e5220e7386de81948c879849172d410dc06edb35b0eb4ae93ec53be") )
     ( 15000, uint256("0x71ebc741a295c9aa0278a8c64da91bd6486bc402134ec19bc194e94c284166b2") )
     ( 20000, uint256("0x0000000000008c3bce6392059167b2018077c23d899f0b0544e33b79a858fa54") )
     ( 25000, uint256("0x00000000000018ffa03555fe9ac252abccb0e79c601472484f9a6411444a7bd7") )
     ( 30000, uint256("0x0000000000005ff2e9dde7b881708bcccc686c6879bc7d0d847824db7e851d72") )
     ( 35000, uint256("0x9d8ae179ed0a32d6a4839ff28774ca24efe8feeab590829ccd8e3a3b0e3f5db8") )
     ( 40000, uint256("0x6e87f0e09127ef7c41782247ca10196102011185dae9dd52a1b62459cdb060e3") )
     ( 45000, uint256("0x00000000000005fc2df4a0da4b3abea8481ce8236b08f9b76bb1720960f40e21") )
     ( 50000, uint256("0x000000000000fe86c41210b620a87420e5bb52b522085f6a45835f6302b7152b") )
     ( 55000, uint256("0x00000000000018b42185793a8a2a5b85e5e8874872f635f5f87e58dc5004e0c8") )
     ( 60000, uint256("0xe794b15b1f5ef36c057f1052ee7dfa13c36857a22d17d582e8e94367692a78d1") )
     ( 65000, uint256("0x3d1a03b2f1a38c38cf59c8a3eb358418899d0f95755bd3cfdfa52f025cfb57a3") )
     ( 70000, uint256("0x00000000000262f7e5cc32f8d8a2153a5d758f7bd16da484537ac5f823709894") )
     ( 75000, uint256("0x927fb2a47bc78771c1815a0e08387d4604ae3c90832017a0224a500a462b5877") )
     ( 80000, uint256("0x000000000002b92ce1cfde080134cad2771ebba31fed0ef2d8aef5f3988b289d") )
     ( 85000, uint256("0x00000000000071e43c82f9c9156ab8644fdead7dbc306d1510b339a4383af73e") )
     ( 90000, uint256("0x1dee9d6a7fa5b7ae87680411b17ed39aa044066e8b4649381b03ec59a769b21e") )
     ( 95000, uint256("0x000000000004584d7b692e598f76d8a4050c19221519c04d9a4932bae1dfd63e") )
    ( 100000, uint256("0x05d2eb866b4336440b7abcd03160c12a4fe1c714663a7516c989909b08f2fe41") )
    ( 120000, uint256("0x000000000007eac1326cd115bccf03f511fb37dc25a5da446fdb45905e9c35d2") )
    ( 140000, uint256("0x0000000000055f92b81fd93b9549765992b6827018c81fe03fc594d96f19f569") )
    ( 155000, uint256("0x00000000001087891767a571e6ef13e5e09a32ebd92be35941dcca05af648b40") )
    ( 200000, uint256("0x000000000019bcba8a14e5460a302eabb4b2139388220f544a3894880d087b36") )
    ( 210000, uint256("0xafb2867ad4175a75659b896338479d5042bbd8e7912b6e3857b18d54f09a531f") )
    ( 220000, uint256("0x00000000000ef55b267db31b241d7dd5437d34593712ce8fc476b4b4680eec4a") )
    ( 230000, uint256("0x000000000003e38a0be816a83569823b08746f7bf1b1bf0bb9333f9b034da116") )
    ( 240000, uint256("0x37e72275673540d08178134988833d8cf64ca66aee979a7bd9347e67615b931b") )
    ( 250000, uint256("0x00000000000030691ac6538ad577d774855089e24d2a91ff251992ac89263cc8") )
    ( 251000, uint256("0x00000000003ced020ddd7c8fd9ad8ce81167f575b595de5c78b28ce7d8fb0162") )
    ( 252000, uint256("0x090ed0ed3cd7d2a691038efff634e3bc5d0f754342a5726fbce61e0b70d9e5bb") )
    ( 253760, uint256("0xbac058e969893b9b301428cafeaae4f08260e1ea6e723e6cc12d7eac23417748") )
    ( 254000, uint256("0xbf0103ce79dec8773b6c4e983fd84200f250941317efae6d6cd491b8d5c497b4") )
    ( 254600, uint256("0xcc04e3f94028a752613a5623f1f1e07e47fdd1a0d7c464c4ef97f36883a5104f") )
    ( 255000, uint256("0x352bb2d4a4105b3784270b658ebea2ed2b6e47da0f4199eb8657cbf8a5024a4a") )
    ( 255500, uint256("0x0000000000ab979f896da6fe41f6f3b97604948112c5b0e6d3f5f49add2f46e2") )
    ( 256000, uint256("0x04347898a4e64c9682b8e21662ce682383c5a12612c5015d3963c44461643686") )
    ( 257000, uint256("0x986114d8039a3c8191d17ec09732ccdfd29a14c22568a9bceb88e264a3c5cd07") )
    ( 258000, uint256("0xb678f1bed44a1bf48fb2124bec749c46e6d590589ad8cc31664f498e7ad29585") )
    ( 258500, uint256("0x000000000006f7d37d6bdeaa984e0ad04cd213bc988674e087ceb428df961979") )
    ( 260000, uint256("0x693fa8c7599443738d7cae2664c44a387ee861f1c1e41daf960efec5b08e636c") )
    ( 261000, uint256("0x0230d087227daa2b321424bc23bbf42159aa62777d5598bd79daa92e8148d1c5") )
    ( 262388, uint256("0x3ba37e3ae52cb905fb0b6083f5e56430255c61c04f48e6161eb8d4d9663358c8") )
    ( 262393, uint256("0xe9ee2293a7fbe82e153290e09a7627fa9efad380a13ec3344f0de821ad4a5db7") )
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
