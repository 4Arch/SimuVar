/**
    File    : SimuVar_Statistics_Results.h
    Author  : Menashe Rosemberg
    Created : 2019.02.16            Version: 20190302.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef STATISTICS_RESULTS_H
#define STATISTICS_RESULTS_H

#include "SimuVar_Environment.h"

#include <map>

using namespace std;

using Frequency     = uint32_t;
using ListOfGenes   = map<GeneType, Frequency>;

using People        = uint32_t;

struct Status {
       YearType Generation = 0;

       ListOfGenes::size_type GeneticVariation = 0;

       People Tot_Women_Alive       = 0;
       People Tot_Men_Alive         = 0;
       float Av_Women_Alive         = 0.0;
       float Av_Men_Alive           = 0.0;
       float Av_Age_Womens_Alive    = 0.0;
       float Av_Age_Mens_Alive      = 0.0;

       People Tot_Women_Souls       = 0;
       People Tot_Men_Souls         = 0;
       float Av_Women_Souls         = 0.0;
       float Av_Men_Souls           = 0.0;
       float Av_Age_Womens_Souls    = 0.0;
       float Av_Age_Mens_Souls      = 0.0;

       float Av_Livings_Ages        = 0.0;
       float Av_Souls_Ages          = 0.0;

       float Av_Couples             = 0.0;
       float Av_Relatives           = 0.0;
       float Av_Friends             = 0.0;

       float Growth_GenVar          = 0.0;
       float Growth_Population      = 0.0;
};

struct FinalStatus {
       YearType LastGeneration  = 0;
       People MaxPopulation     = 0;

       ListOfGenes::size_type MaxGeneticVariation = 0;

       float MaxAvAge           = 0.0;
       float MaxAvFamilySize    = 0.0;
       float MaxAvFriendsSize   = 0.0;
       float MaxAvCouples       = 0.0;
};

#endif // STATISTICS_RESULTS_H
