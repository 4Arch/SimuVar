/**
    File    : SimuVar_Life.h
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190228.1

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
/*
    UPGRADES:
    1. Better randomization over Ages
    2. Consider the siblings as Relative
*/
#ifndef LIFEGROWTH_H
#define LIFEGROWTH_H

#include "../../C++_lib/SpinLock/SpinLock.h"
#include "SimuVar_Template_IsInRange.h"
#include "SimuVar_Environment.h"
#include "SimuVar_DataBase.h"
#include "SimuVar_Statistics.h"

#include <chrono>
#include <random>
#include <thread>
#include <iterator>

using namespace std;

struct LifeGrowth {
       LifeGrowth();
      ~LifeGrowth();

    Status Begin(Environment LifeLimits);
    Status NextGeneration();
    FinalStatus FinalResults() const;

    private:
        Environment LiLi;
        YearType CurrentGeneration;

        DataStatistics Statistics;

        mt19937 FindOutAFriend;

        BookOfLife Population;
        BookOfLife_Idx Idx_Population;
        NOTSigningUp SoulsDeparture;
        SpinLock SoulDepProtection;

        void EveryOneGetOldAndDecease();
        void FriendsTo(Person& Individual);
        void FamilyTo(Person& Individual);
        void LastGoodbye();

        inline NOfTwins IamDTwinNumber(const GeneType ChildGenes) const;
        BookOfLife::iterator FindPeople(const FullGene& Genes2Search);
        inline BookOfLife_IdxIIt FindIdx(const FullGene& Genes2Search) const;
        void AdamVeHavah(const GeneType ChildGenesSeq);
        void GrowingDPopulation(const GeneType ChildGenes, Person& Mother, const FullGene& Father);

    LifeGrowth(const LifeGrowth&) = delete;
    LifeGrowth& operator=(const LifeGrowth&) = delete;
};

#endif // LIFEGROWTH_H
