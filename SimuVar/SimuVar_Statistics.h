/**
    File    : SimuVar_Statistics.h
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
#ifndef STATISTICS_H
#define STATISTICS_H

#include "SimuVar_Person.h"
#include "SimuVar_DataBase.h"
#include "SimuVar_Statistics_Results.h"

#include <algorithm>

constexpr bool GROWTH   = true;
constexpr bool DECREASE = false;

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
