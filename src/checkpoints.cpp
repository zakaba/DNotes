// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 DNotes Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

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
            (     0, uint256("0x20bbf1cb1115ccda06c0cce115f5b72a78055a163892575988d1c8ee085f5e86"))
			(	  1, uint256("0x688fb0fafd32a74289ce878106791a55be55ed54bb034de8923dd92e6ed9dee7"))
			(	 80, uint256("0xca1c4fe37b2b16487987725c40c33b57c353c2d6289e87e3ac5d37dc75969ca1"))
			(	144, uint256("0x2dcf3e19fe6eb2cf0d452efc5120746487ef82eb102e744ed041696d0e51b92f"))
			(	1870, uint256("0x05e4d824b5f50144140af5e85ef380e8880ae2e273f48d59faa715c6d2830720"))
			(	4635, uint256("0x8c956cddc395b47e34068cbdb5d7821aa829bd4adbe0571be4ce19949485feef"))
			(	7772, uint256("0xe2f33a0cdafbebfe37cdf119c0bcd15a4b106d171fee4110ef8281eda49a3c09"))
			(	17793, uint256("0x41954077983444d470b7e236c4dccc3f1bb92270485953dda87980a02c6f9070"))
			(	50039, uint256("0xe91aba141ed0e551a153071caeac8a70d4bf0b240118cbd9a93f002903ab3ab6"))
			(	99812, uint256("0x0a219f74e475dbb10c2af0ae30523ddb482cf0182a6fc20875bf95df0684780a"))
			(	353739, uint256("0xbbc9487af28151632382cb946e96208bf40cd0e4b5297da1b522c9ca322c7537"))
			(	500000, uint256("0xd19972fb0046b5d91a5adc37e58bb01a00e887c1aa18a19e9f8dabb1ec1f9893"))
			(	541300, uint256("0x6b172ceb927ea07fd2280d5199b1b8ef694fa53a0dc148488136f193e930be2d"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
