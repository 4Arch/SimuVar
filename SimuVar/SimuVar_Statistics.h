/**
    File    : SimuVar_Statistics.h
    Author  : Menashe Rosemberg
    Created : 2019.02.15            Version: 20190218.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef STATISTICS_H
#define STATISTICS_H

#include "SimuVar_Person.h"
#include "SimuVar_DataBase.h"
#include "SimuVar_Statistics_Results.h"

#include <algorithm>

constexpr bool GROWTH   = true;
constexpr bool DECREASE = false;

constexpr float Average(float CurrValue, float newUnit, float Pop) {
          return Pop ? ((CurrValue * Pop + newUnit) / Pop) : 0.0;
}

constexpr float Average(float Value, float Pop) {
          return Pop ? (Value / Pop) : 0.0;
}

struct DataStatistics {
       DataStatistics();
      ~DataStatistics();

    void GrowthPopulation(const Person& Child);
    void DecreasePopulation(const Person& Soul);
    Status Current(const YearType CurrGeneration, const BookOfLife& Population);
    FinalStatus FinalResults() const;

    private:
        Status STATUS;
        FinalStatus FINALSTATUS;

         ListOfGenes GenesAlive;

        float Av_Souls_Ages() const;

        void Update_GenesDB(const Person& Child, const bool GrowthDecrease);
        void UpdateFinalStatus();
};

#endif // STATISTICS_H
