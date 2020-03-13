/**
    File    : SimuVar_Life.cpp
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
