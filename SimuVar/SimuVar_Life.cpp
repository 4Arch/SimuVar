/**
    File    : SimuVar_Life.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190228.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/

#include "SimuVar_Life.h"

LifeGrowth::LifeGrowth() : FindOutAFriend(chrono::steady_clock::now().time_since_epoch().count()) {}
LifeGrowth::~LifeGrowth() = default;

Status LifeGrowth::Begin(Environment LifeLimits) {
       CurrentGeneration = 0;
       LiLi = move(LifeLimits);

       if (!(IsInRange(LiLi.InitialPopulation, 2, numeric_limits<decltype(LiLi.InitialPopulation)>::max())              &&
            IsInRange(LiLi.MeetingMaxPerGeneration, 1,  numeric_limits<decltype(LiLi.MeetingMaxPerGeneration)>::max())  &&
//          IsInRange(LiLi.MinAgeOfFertility,    0, numeric_limits<decltype(LiLi.MinAgeOfFertility)>::max())            &&
            IsInRange(LiLi.ChildMortalityRate,                          0.00, 1.0)                                      &&
            IsInRange(LiLi.MaxFertility,                                0.01, 1.0)                                      &&
            IsInRange(LiLi.MaxDecayOfNaturalFertilityPerGeneration[0],  0.0, 1.0)                                       &&
            IsInRange(LiLi.MaxDecayOfNaturalFertilityPerGeneration[1],  0.0, 1.0)                                       &&
            IsInRange(LiLi.MaxDecayOfFertilityAfterChildBirth[0],       0.0, 1.0)                                       &&
            IsInRange(LiLi.MaxDecayOfFertilityAfterChildBirth[1],       0.0, 1.0)                                       &&
            IsInRange(LiLi.InitialWilling2Marry,                        0.01, 1.0)                                      &&
            IsInRange(LiLi.MaxDecayofWillingness2MarryPerGeneration[0], 0.0, 1.0)                                       &&
            IsInRange(LiLi.MaxDecayofWillingness2MarryPerGeneration[1], 0.0, 1.0)))
          throw runtime_error("\n\nThe environment you chose isn't possible.\n");

       Population.clear();
       Idx_Population.clear();
       Statistics = DataStatistics();

       for (uint8_t Baby = 0; Baby < LiLi.InitialPopulation; ++Baby)
            this->AdamVeHavah(uniform_int_distribution<GeneType>(1, numeric_limits<GeneType>::max())(FindOutAFriend));

       return Statistics.Current(CurrentGeneration, Population);
}

Status LifeGrowth::NextGeneration() {

       EveryOneGetOldAndDecease();

       for (auto& EveryOne : Population) {
            FriendsTo(EveryOne);
            FamilyTo(EveryOne);
       }

       LastGoodbye();

       CurrentGeneration++;

       return Statistics.Current(CurrentGeneration, Population);
}

FinalStatus LifeGrowth::FinalResults() const {
            return Statistics.FinalResults();
}
