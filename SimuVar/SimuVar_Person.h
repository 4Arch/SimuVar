/**
    File    : SimuVar_Person.h
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190217.3

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
#ifndef PERSON_H
#define PERSON_H

#include "SimuVar_Environment.h"

#include <set>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <climits>
#include <optional>
#include <functional>

using namespace std;

struct FullGene {
       FullGene (const GeneType newGene, const NOfTwins newTwinNumber) : Sequence(newGene), TwinNumber(newTwinNumber) {}
       FullGene (const FullGene& FuGe) : Sequence(FuGe.Sequence), TwinNumber(FuGe.TwinNumber) { }

       const GeneType Sequence;                                                     //It can't be 0 or unit16_t::max()
       const NOfTwins TwinNumber;

       bool operator==(const FullGene& FGene) const { return Sequence == FGene.Sequence && TwinNumber == FGene.TwinNumber; }
       bool operator!=(const FullGene& FGene) const { return Sequence != FGene.Sequence || TwinNumber != FGene.TwinNumber; }
};

namespace std {
          template<> struct less<FullGene> {
            bool operator()(const FullGene& lhs, const FullGene& rhs) const { return lhs.Sequence < rhs.Sequence; }
    };
}

using KnownPeople = multiset<FullGene>;

struct Person {
       Person(const GeneType newPerson, const NOfTwins TwinNumber, const Environment& LifeLimits);
      ~Person();

    //itself
    FullGene Genes() const;
    void GetsOld();
    bool isFemale() const;                              //First bit of myGenes indicate the gender
    optional<GeneType> GiveBirth(GeneType Father);
    LifeTime Age() const;

    //Relationship
    optional<FullGene> MayIPropose();
    bool GetAPartner(FullGene newPartner);
    optional<FullGene> Partner() const;
    bool CanIGetPregnant() const;

    KnownPeople::size_type Quant_Friends() const;
    KnownPeople::size_type Quant_Relatives() const;

    bool MeetNewFriend(const FullGene& newFriend);
    void MeetNewRelative(const FullGene& newRelative);

    //Cycle of Life
    bool MyTimeIsCome() const;
    void SayGoodByeTo(const FullGene& ThisSoul);

    private:

        const FullGene pGenes;

        const Environment& LiLi;
        mt19937 RandBase;
        LifeTime myMaxLifeTime;
        LifeTime Ages;
        float Idx_Fertility;
        float WillNess2Marry;
        bernoulli_distribution GeneticVariation;
        uniform_real_distribution<float> DecayFertility;
        uniform_real_distribution<float> DecayFertilityAfterChildsBirth;
        uniform_real_distribution<float> DecayWilling2Marry;

        optional<FullGene> PartnerGenes;
        KnownPeople FriendsList;
        KnownPeople Relatives;

        bool isFemale(const GeneType& ToPropose) const;

        bool Willingness2Marry();
        GeneType AnOffspringWasBorn(GeneType Father);

        template<template<typename...> typename TContainer, typename TObject>
        auto FindKnownPerson(const FullGene& Genes2Search, const TContainer<TObject>& Container) const;

        Person(const Person&) = delete;
        Person& operator=(const Person&) = delete;
};
#endif // PERSON_H
