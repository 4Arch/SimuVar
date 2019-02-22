/**
    File    : SimuVar_Person.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190215.4

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Redistribution and use of source or/and binary forms, with or without modification are not permitted,
    unless with an express Author's permission.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "SimuVar_Person.h"

Person::Person(const GeneType newPerson, const NOfTwins TwinNumber, const Environment& LifeLimits) :
        Genes                           (newPerson, TwinNumber),
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

void Person::GetsOld() {
     if (this->Ages >= LiLi.MinAgeOfFertility) {
        Idx_Fertility  *= 1-DecayFertility(RandBase);
        WillNess2Marry *= 1-DecayWilling2Marry(RandBase);
     }

     Ages++;
}

bool Person::isFemale() const { return (this->Genes.Sequence & (1 << 0)); }
bool Person::isFemale(const GeneType& Gene2Check) const { return (Gene2Check & (1 << 0)); }
bool Person::CanIGetPregnant() const { return this->isFemale() && this->Ages >= LiLi.MinAgeOfFertility; }

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
