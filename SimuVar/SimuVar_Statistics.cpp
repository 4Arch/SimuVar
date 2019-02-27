/**
    File    : SimuVar_Statistics.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.15            Version: 20190227.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "SimuVar_Statistics.h"

DataStatistics::DataStatistics() = default;
DataStatistics::~DataStatistics() = default;

Status DataStatistics::Current(const YearType CurrGeneration, const BookOfLife& Population) {
       STATUS.Generation        = CurrGeneration;
       STATUS.Av_Souls_Ages     = this->Av_Souls_Ages();

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

       STATUS.Av_Women_Alive        = Average(STATUS.Tot_Women_Alive                     , STATUS.Tot_Women_Alive + STATUS.Tot_Men_Alive);
       STATUS.Av_Men_Alive          = Average(STATUS.Tot_Men_Alive                       , STATUS.Tot_Women_Alive + STATUS.Tot_Men_Alive);

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
        if (auto Search = GenesAlive.try_emplace(GenesAlive.cbegin(), Child.Genes().Sequence, 1); Search != GenesAlive.cend())
            Search->second++;
     } else
        if (auto Search = GenesAlive.find(Child.Genes().Sequence); Search != GenesAlive.cend()) {
            if (Search->second > 2)
                Search->second--;
            else
                GenesAlive.erase(Search);
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
