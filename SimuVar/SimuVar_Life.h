/**
    File    : SimuVar_Life.h
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190218.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Redistribution and use of source or/and binary forms, with or without modification are not permitted,
    unless with an express Author's permission.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
/*
    UPDATES:
    1. Better randomization over Ages
*/
#ifndef LIFEGROWTH_H
#define LIFEGROWTH_H

#include "SimuVar_Template_IsInRange.h"
#include "SimuVar_Environment.h"
#include "SimuVar_DataBase.h"
#include "SimuVar_Statistics.h"

#include <chrono>
#include <random>

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

        void FriendsTo(Person& Individual);
        void FamilyTo(Person& Individual);
        void DeceaseTo(Person& Individual);
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
