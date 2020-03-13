/**
    File    : SimuVar_Person.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190215.6

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
#include "SimuVar_Person.h"

Person::Person(const GeneType newPerson, const NOfTwins TwinNumber, const Environment& LifeLimits) :
        pGenes                          (newPerson, TwinNumber),
        LiLi                            (LifeLimits),
        RandBase                        (chrono::steady_clock::now().time_since_epoch().count()),
        myMaxLifeTime                   (uniform_int_distribution<LifeTime>(0, LiLi.MaxLifeTime[isFemale()])(RandBase)),
        Ages                            (0),
        Idx_Fertility                   (uniform_real_distribution<float>(LiLi.MaxFertility * 0.65, LiLi.MaxFertility)(RandBase)),
        WillNess2Marry                  (LiLi.InitialWilling2Marry),
        DecayFertility                  (0.0, LiLi.MaxDecayOfNaturalFertilityPerGeneration[this->isFemale()]),
        DecayFertilityAfterChildsBirth  (0.0, LiLi.MaxDecayOfFertilityAfterChildBirth[this->isFemale()]),
        DecayWilling2Marry              (0.0, LiLi.MaxDecayofWillingness2MarryPerGeneration[this->isFemale()]) {

        if (myMaxLifeTime <= LiLi.MinAgeOfFertility && bernoulli_distribution(1.0-LiLi.ChildMortalityRate)(RandBase))
           myMaxLifeTime = uniform_int_distribution<LifeTime>(LiLi.MinAgeOfFertility,
                                                              LiLi.MaxLifeTime[isFemale()])(RandBase);
}

Person::~Person() = default;


FullGene Person::Genes() const {
        return pGenes;
}

void Person::GetsOld() {
     if (this->Ages >= LiLi.MinAgeOfFertility) {
        Idx_Fertility  *= 1-DecayFertility(RandBase);
        WillNess2Marry *= 1-DecayWilling2Marry(RandBase);
     }

     Ages++;
}

bool Person::isFemale() const { return (this->pGenes.Sequence & (1 << 0)); }
bool Person::isFemale(const GeneType& Gene2Check) const { return (Gene2Check & (1 << 0)); }
bool Person::CanIGetPregnant() const { return this->Ages >= LiLi.MinAgeOfFertility; }

optional<GeneType> Person::GiveBirth(GeneType Father) {

    bernoulli_distribution IsSheOvulating(Idx_Fertility);

    if (IsSheOvulating(RandBase)) {
        Idx_Fertility *= 1-DecayFertilityAfterChildsBirth(RandBase);
        return AnOffspringWasBorn(move(Father));
    }

    return nullopt;
}


bool Person::MyTimeIsCome() const { return this->Ages >= this->myMaxLifeTime; }

LifeTime Person::Age() const { return this->Ages; }
