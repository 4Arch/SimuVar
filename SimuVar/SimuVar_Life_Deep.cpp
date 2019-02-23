/**
    File    : SimuVar_Life_Deep.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190217.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Redistribution and use of source or/and binary forms, with or without modification are not permitted,
    unless with an express Author's permission.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/

#include "SimuVar_Life.h"

void LifeGrowth::FriendsTo(Person& Individual) {
     if (Population.size() > 1) {
         uniform_int_distribution<BookOfLife::size_type> TheNewFriendIs(0, Population.size()-1);

         for (Meet FriendNumber = 0; FriendNumber < LiLi.MeetingMaxPerGeneration; ++FriendNumber) {
             auto NewFriend = next(Population.begin(), TheNewFriendIs(FindOutAFriend));
             if (Individual.MeetNewFriend(NewFriend->Genes))
                 NewFriend->MeetNewFriend(Individual.Genes);
         }
     }
}

BookOfLife::iterator LifeGrowth::FindPeople(const FullGene& Genes2Search) {
    auto AllTwins = Idx_Population.equal_range(Genes2Search.Sequence);

    if (distance(AllTwins.first, AllTwins.second))
        for (auto TwinTwin = AllTwins.first; TwinTwin != AllTwins.second; ++TwinTwin)
            if (TwinTwin->Genes.TwinNumber == Genes2Search.TwinNumber)
                return TwinTwin->Point2Person;

    return Population.end();
}

void LifeGrowth::FamilyTo(Person& Individual) {

     if (Individual.CanIGetPregnant()) {
        if (auto Father = Individual.Partner())
        if (auto Child  = Individual.GiveBirth(Father->Sequence))
            this->GrowingDPopulation(Child.value(), Individual, Father.value());

     } else if (auto Bride = Individual.MayIPropose()) {

        if (auto BrideLocation = this->FindPeople(Bride.value()); BrideLocation != Population.cend() &&
           BrideLocation->GetAPartner(Individual.Genes))
           Individual.GetAPartner(BrideLocation->Genes);
     }
}

void LifeGrowth::AdamVeHavah(const GeneType ChildGenesSeq) {
     NOfTwins IamDTwin = this->IamDTwinNumber(ChildGenesSeq);

     Population.emplace_front(ChildGenesSeq, IamDTwin, LiLi);
     Idx_Population.emplace(ChildGenesSeq, IamDTwin, Population.begin());

     Statistics.GrowthPopulation(Population.front());
}

void LifeGrowth::GrowingDPopulation(const GeneType ChildGenesSeq, Person& Mother, const FullGene& Father) {

     this->AdamVeHavah(ChildGenesSeq);

     Population.front().MeetNewRelative(Mother.Genes);
     Population.front().MeetNewRelative(Father);

     Mother.MeetNewRelative(Population.front().Genes);
     if (auto theFather = this->FindPeople(Father); theFather != Population.cend())
        theFather->MeetNewRelative(Population.front().Genes);
}

inline NOfTwins LifeGrowth::IamDTwinNumber(const GeneType ChildGenesSeq) const {
       NOfTwins IamDTwin = 0;

        auto AllTwins = Idx_Population.equal_range(ChildGenesSeq);
        for (auto TwinTwin = AllTwins.first; TwinTwin != AllTwins.second; ++TwinTwin)
            if (TwinTwin->Genes.TwinNumber > IamDTwin)
               IamDTwin = TwinTwin->Genes.TwinNumber + 1;

       return IamDTwin;
}

inline BookOfLife_IdxIIt LifeGrowth::FindIdx(const FullGene& Genes2Search) const {
    auto AllTwins = Idx_Population.equal_range(Genes2Search.Sequence);

    if (distance(AllTwins.first, AllTwins.second))
        for (auto TwinTwin = AllTwins.first; TwinTwin != AllTwins.second; ++TwinTwin)
            if (TwinTwin->Genes.TwinNumber == Genes2Search.TwinNumber)
                return TwinTwin;   //Population

    return Idx_Population.cend();
}

void LifeGrowth::DeceaseTo(Person& Individual) {
     if (Individual.MyTimeIsCome())
        SoulsDeparture.emplace_back(Individual.Genes);
}

void LifeGrowth::LastGoodbye() {
     for (auto& SayGoodbye : SoulsDeparture) {
         auto Idx = FindIdx(SayGoodbye);
         Statistics.DecreasePopulation((*Idx->Point2Person));
         Population.erase(Idx->Point2Person);
         Idx_Population.erase(Idx);
     }

     for (auto& Individual : Population)
         for (auto& ThisSoul : SoulsDeparture) {
//            DEBUG("Say Goodbye to", ThisSoul.Sequence);
             Individual.SayGoodByeTo(ThisSoul);
         }

//      DEBUG("SayGoodBye", "Is done");

     SoulsDeparture.clear();
}