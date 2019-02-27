/**
    File    : SimuVar_Person.h
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190217.3

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef PERSON_H
#define PERSON_H

#include "SimuVar_Environment.h"

#include <set>
#include <chrono>
#include <random>
#include <climits>
#include <optional>

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
