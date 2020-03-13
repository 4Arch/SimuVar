/**
    File    : SimuVar_Life_Deep.cpp
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

void LifeGrowth::EveryOneGetOldAndDecease() {

     auto GetOldAndDecease = [&](BookOfLife::iterator Individual, const BookOfLife::iterator End) {
          for (; Individual != End; ++Individual) {
              Individual->GetsOld();
              if (Individual->MyTimeIsCome()) {
                 SoulDepProtection.lock();
                 SoulsDeparture.emplace_back(Individual->Genes());
                 SoulDepProtection.unlock();
              }
          }
     };

     uint16_t Blocks = 2;
     if (Population.size() % 4 == 0)
        Blocks = 4;
     else if (Population.size() % 3 == 0)
             Blocks = 3;

     vector<thread> GOaD;
     auto PosI = Population.begin();
     auto NOfPersons = Population.size() / Blocks;

     Blocks = 0;
     while (PosI != Population.end()) {
           auto PosF = (Population.size() > distance(PosI, Population.begin()) + NOfPersons)?
                        next(PosI, NOfPersons):
                        Population.end();

           GOaD.emplace_back(GetOldAndDecease, PosI , PosF);
           PosI = PosF;
     }

     for (auto& IIt : GOaD)
         IIt.join();
}

void LifeGrowth::FriendsTo(Person& Individual) {
     if (Population.size() > 1) {
         uniform_int_distribution<BookOfLife::size_type> TheNewFriendIs(0, Population.size()-1);

         for (Meet FriendNumber = 0; FriendNumber < LiLi.MeetingMaxPerGeneration; ++FriendNumber) {
             auto NewFriend = next(Population.begin(), TheNewFriendIs(FindOutAFriend));
             if (Individual.MeetNewFriend(NewFriend->Genes()))
                 NewFriend->MeetNewFriend(Individual.Genes());
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

     if (Individual.isFemale()) {
        if (Individual.CanIGetPregnant()) {
            if (auto Father = Individual.Partner())
            if (auto Child  = Individual.GiveBirth(Father->Sequence))
                this->GrowingDPopulation(Child.value(), Individual, Father.value());
        }
     } else if (auto Bride = Individual.MayIPropose()) {

        if (auto BrideLocation = this->FindPeople(Bride.value()); BrideLocation != Population.cend() &&
           BrideLocation->GetAPartner(Individual.Genes()))
           Individual.GetAPartner(BrideLocation->Genes());
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

     thread([&](){  Person& Front = Population.front();
                    Person& mother = Mother;
                    const FullGene& father = Father;

                    Front.MeetNewRelative(mother.Genes());
                    Front.MeetNewRelative(father);
     }).detach();

     Mother.MeetNewRelative(Population.front().Genes());
     if (auto theFather = this->FindPeople(Father); theFather != Population.cend())
        theFather->MeetNewRelative(Population.front().Genes());
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

void LifeGrowth::LastGoodbye() {
     for (auto& SayGoodbye : SoulsDeparture) {
         auto Idx = FindIdx(SayGoodbye);
         Statistics.DecreasePopulation(*Idx->Point2Person);
         Population.erase(Idx->Point2Person);
         Idx_Population.erase(Idx);
     }

     for (auto& Individual : Population)
         for (auto& ThisSoul : SoulsDeparture)
             Individual.SayGoodByeTo(ThisSoul);

     SoulsDeparture.clear();
}
