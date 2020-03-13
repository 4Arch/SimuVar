/**
    File    : SimuVar_Statistics_Results.h
    Author  : Menashe Rosemberg
    Created : 2019.02.16            Version: 20190302.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
