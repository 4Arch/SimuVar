/**
    File    : SimuVar_Person_Relationships.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190302.1

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
#include "SimuVar_Template_IsInRange.h"

template<template<typename...> typename TContainer, typename TObject>
auto Person::FindKnownPerson(const FullGene& Genes2Search, const TContainer<TObject>& Container) const {

     auto AllTwins = Container.equal_range(Genes2Search);

     if (distance(AllTwins.first, AllTwins.second))
        for (auto TwinTwin = AllTwins.first; TwinTwin != AllTwins.second; ++TwinTwin)
            if (TwinTwin->TwinNumber == Genes2Search.TwinNumber)
                return TwinTwin;

     return Container.cend();
}

bool Person::GetAPartner(FullGene newPartner) {
     if (this->PartnerGenes.has_value() ||
         FindKnownPerson(newPartner, this->Relatives) != this->Relatives.cend())
        return false;


     this->PartnerGenes.emplace(newPartner);

     return true;
}

optional<FullGene> Person::Partner() const {
     return this->PartnerGenes;
}

bool Person::MeetNewFriend(const FullGene& newFriend) {
     if (newFriend != this->pGenes &&
         FindKnownPerson(newFriend, this->FriendsList) == this->FriendsList.cend() &&
         FindKnownPerson(newFriend, this->Relatives) == this->Relatives.cend()) {
        this->FriendsList.emplace(newFriend);
        return true;
     }

    return false;
}

void Person::MeetNewRelative(const FullGene& newRelative) {
     if (newRelative != this->pGenes && FindKnownPerson(newRelative, this->Relatives) == this->Relatives.cend()) {
        this->Relatives.emplace(newRelative);
        if (auto NotaFriend = FindKnownPerson(newRelative, this->FriendsList); NotaFriend != this->FriendsList.cend())
            this->FriendsList.erase(NotaFriend);
     }
}

void Person::SayGoodByeTo(const FullGene& ThisSoul) {
     if (this->PartnerGenes.has_value() && ThisSoul == this->PartnerGenes)
        this->PartnerGenes.reset();
     else {
          auto DelRelative = [&]() {
               if (auto IMissU = this->FindKnownPerson(ThisSoul, Relatives); IMissU != Relatives.cend())
               this->Relatives.erase(IMissU); };

          thread(DelRelative).detach();

          if (auto IMissU = this->FindKnownPerson(ThisSoul, FriendsList); IMissU != FriendsList.cend())
             this->FriendsList.erase(IMissU);
     }
}

bool Person::Willingness2Marry() {
     if (PartnerGenes.has_value()) return false;

     bernoulli_distribution Want2Marry(WillNess2Marry);

     return Want2Marry(RandBase);
}

optional<FullGene> Person::MayIPropose() {
        if (!this->isFemale()                       &&
            this->Ages >= LiLi.MinAgeOfFertility    &&
            !FriendsList.empty()                    &&
            Willingness2Marry()) {
            vector<reference_wrapper<const FullGene>> GirlsList;
            GirlsList.reserve(FriendsList.size());

            for (auto& Friends : FriendsList)
                if (this->isFemale(Friends.Sequence))
                    GirlsList.emplace_back(Friends);

            if (GirlsList.size())
                return cref(GirlsList[uniform_int_distribution<vector<reference_wrapper<const FullGene>>::size_type>(0,
                                                                                    GirlsList.size()-1)(RandBase)]).get();
        }

        return nullopt;
}

GeneType Person::AnOffspringWasBorn(GeneType Father) {
         auto SegExtractor = [](GeneType Gene, GeneType IniPos) -> GeneType {
                               return (((1 << GeneSubSegmentSize) - 1) & (Gene >> IniPos));
         };

         GeneType ChildGenes = 0;

         for (GeneType SubSegment = 0; SubSegment < sizeof(GeneType)*CHAR_BIT; SubSegment += GeneSubSegmentSize)
             ChildGenes += SegExtractor((GeneticVariation(RandBase)?this->pGenes.Sequence:Father), SubSegment)   //Choose which Segment
                          << SubSegment;                                                                        //Move the segment to its position

         return ChildGenes;
}

KnownPeople::size_type Person::Quant_Friends() const { return this->FriendsList.size(); }
KnownPeople::size_type Person::Quant_Relatives() const { return Relatives.size(); }
