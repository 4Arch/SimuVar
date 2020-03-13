/**
    File    : SimuVar_Statistics.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.15            Version: 20190302.1

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
#include "SimuVar_Statistics.h"

DataStatistics::DataStatistics() = default;
DataStatistics::~DataStatistics() = default;

constexpr float Average(const float CurrValue, const float newUnit, const float Pop) {
          return (CurrValue * Pop + newUnit) / (Pop + 1.0); }

constexpr float Average(const float Value, const float Pop) {
          return Pop ? (Value / Pop) : 0.0; }

constexpr float Marginal(const float LastY, const float Actual) {
          return (Actual - LastY) / Actual; }

Status DataStatistics::Current(const YearType CurrGeneration, const BookOfLife& Population) {
       STATUS.Generation        = CurrGeneration;
       STATUS.Av_Souls_Ages     = this->Av_Souls_Ages();

       STATUS.Growth_GenVar     = Marginal(STATUS.GeneticVariation                      , GenesAlive.size());
       STATUS.Growth_Population = Marginal(STATUS.Tot_Women_Alive + STATUS.Tot_Men_Alive, Population.size());

       STATUS.GeneticVariation  = GenesAlive.size();

       STATUS.Tot_Men_Alive   = 0;
       STATUS.Tot_Women_Alive = 0;
       BookOfLife::size_type Tot_Couples = 0,
                             Tot_Living_Women_Ages = 0,
                             Tot_Living_Men_Ages  = 0;

       People Tot_Friends = 0,
              Tot_Relatives = 0;

       for (auto& Individual : Population) {
            if (Individual.isFemale()) {
                STATUS.Tot_Women_Alive++;
                Tot_Living_Women_Ages += Individual.Age();
                if (Individual.Partner())
                    Tot_Couples+=2;
            } else {
                STATUS.Tot_Men_Alive++;
                Tot_Living_Men_Ages += Individual.Age();
            }
            Tot_Friends   += Individual.Quant_Friends();
            Tot_Relatives += Individual.Quant_Relatives();
       }

       STATUS.Av_Friends            = Average(Tot_Friends,   Population.size());
       STATUS.Av_Relatives          = Average(Tot_Relatives, Population.size());

       STATUS.Av_Age_Womens_Alive   = Average(Tot_Living_Women_Ages                      , STATUS.Tot_Women_Alive);
       STATUS.Av_Age_Mens_Alive     = Average(Tot_Living_Men_Ages                        , STATUS.Tot_Men_Alive);
       STATUS.Av_Livings_Ages       = Average(Tot_Living_Women_Ages + Tot_Living_Men_Ages, Population.size());

       STATUS.Av_Women_Alive        = Average(STATUS.Tot_Women_Alive                     , Population.size());
       STATUS.Av_Men_Alive          = Average(STATUS.Tot_Men_Alive                       , Population.size());

       STATUS.Av_Couples            = Average(Tot_Couples                                , Population.size());

       STATUS.Av_Women_Souls        = Average(STATUS.Tot_Women_Souls                     , STATUS.Tot_Women_Souls + STATUS.Tot_Men_Souls);
       STATUS.Av_Men_Souls          = Average(STATUS.Tot_Men_Souls                       , STATUS.Tot_Women_Souls + STATUS.Tot_Men_Souls);

       this->UpdateFinalStatus();

    return STATUS;
}

void DataStatistics::UpdateFinalStatus() {

     if (FINALSTATUS.MaxGeneticVariation <= STATUS.GeneticVariation) {

        FINALSTATUS.LastGeneration = STATUS.Generation + 1;

        FINALSTATUS.MaxPopulation        = max(FINALSTATUS.MaxPopulation,        STATUS.Tot_Women_Alive + STATUS.Tot_Men_Alive);
        FINALSTATUS.MaxGeneticVariation  = max(FINALSTATUS.MaxGeneticVariation,  STATUS.GeneticVariation);

        FINALSTATUS.MaxAvAge             = max(FINALSTATUS.MaxAvAge,             STATUS.Av_Livings_Ages);

        FINALSTATUS.MaxAvCouples         = max(FINALSTATUS.MaxAvCouples,         STATUS.Av_Couples);
        FINALSTATUS.MaxAvFamilySize      = max(FINALSTATUS.MaxAvFamilySize,      STATUS.Av_Relatives);
        FINALSTATUS.MaxAvFriendsSize     = max(FINALSTATUS.MaxAvFriendsSize,     STATUS.Av_Friends);
     }
}

FinalStatus DataStatistics::FinalResults() const {
            return FINALSTATUS;
}

void DataStatistics::GrowthPopulation(const Person& Child) {
     this->Update_GenesDB(Child, GROWTH);
}

void DataStatistics::Update_GenesDB(const Person& Child, const bool GrowthDecrease) {
     if (GrowthDecrease) {
        auto Search = GenesAlive.try_emplace(GenesAlive.cbegin(), Child.Genes().Sequence, 0);
        Search->second++;
     } else {
        if (auto Search = GenesAlive.find(Child.Genes().Sequence); Search != GenesAlive.cend()) {
            if (Search->second == 1)
                GenesAlive.erase(Search);
            else
                Search->second--;
        }
     }
}

void DataStatistics::DecreasePopulation(const Person& Soul) {
     this->Update_GenesDB(Soul, DECREASE);

     if (Soul.isFemale()) {
        STATUS.Av_Age_Womens_Souls = Average(STATUS.Av_Age_Womens_Souls, Soul.Age(), STATUS.Tot_Women_Souls);
        STATUS.Tot_Women_Souls++;
     } else {
        STATUS.Av_Age_Mens_Souls   = Average(STATUS.Av_Age_Mens_Souls  , Soul.Age(), STATUS.Tot_Men_Souls);
        STATUS.Tot_Men_Souls++;
     }
}

float DataStatistics::Av_Souls_Ages() const {
      auto Tot_Souls_Ages = [&]() -> float {
                                        return  this->STATUS.Av_Age_Womens_Souls * this->STATUS.Tot_Women_Souls +
                                                this->STATUS.Av_Age_Mens_Souls   * this->STATUS.Tot_Men_Souls;
      };

      return Tot_Souls_Ages() / (STATUS.Tot_Women_Souls + STATUS.Tot_Men_Souls);
}
