/**
    File    : SimuVar_Statistics_Results.h
    Author  : Menashe Rosemberg
    Created : 2019.02.16            Version: 20190217.1

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
       YearType Generation;

       ListOfGenes::size_type GeneticVariation;

       People Tot_Women_Alive;
       People Tot_Men_Alive;
       float Av_Women_Alive;
       float Av_Men_Alive;
       float Av_Age_Womens_Alive;
       float Av_Age_Mens_Alive;

       People Tot_Women_Souls = 0;
       People Tot_Men_Souls = 0;
       float Av_Women_Souls;
       float Av_Men_Souls;
       float Av_Age_Womens_Souls;
       float Av_Age_Mens_Souls;

       float Av_Livings_Ages;
       float Av_Souls_Ages;

       float Av_Couples;
       float Av_Relatives;
       float Av_Friends;
};

struct FinalStatus {
       YearType LastGeneration = 0;
       People MaxPopulation = 0;

       ListOfGenes::size_type MaxGeneticVariation;

       float MaxAvAge;
       float MaxAvFamilySize;
       float MaxAvFriendsSize;
       float MaxAvCouples;
};

#endif // STATISTICS_RESULTS_H
