/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190219.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "../ReadConfigurations/ReadConfigurations.h"
#include "SimuVar_Life.h"
#include "SimuVar_Statistics_Results.h"
#include "ShowData.h"

#include <iostream>

Environment  FullfilEnvData();

int main() {
    try {

        ShowTime Live;
        LifeGrowth Life;

        Environment Env(FullfilEnvData());

        Status STATUS = Life.Begin(Env);
        Live.Show(STATUS);

        for (uint32_t nGenerations = 0; nGenerations < Env.NumberOfGenerations; ++nGenerations) {
            STATUS = Life.NextGeneration();
            Live.Show(STATUS);
        }

        FinalStatus FINAL = Life.FinalResults();
        Live.Show(FINAL);

    } catch (const short Exc) {
            switch(Exc) {
                case CONFFILEDOESNTEXISTS: cerr << "Configuration file doesn't exists.\n" << endl; break;
                case CONFFILENOTGOOD     : cerr << "Error reading the configuration file.\n" << endl;
            }

            runtime_error("");
    }

    return 0;
}
