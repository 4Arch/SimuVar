/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190219.3

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
#include "../../C++_lib/ReadConfigurations/ReadConfigurations.h"
#include "SimuVar_Environment.h"
#include "SimuVar_Life.h"
#include "SimuVar_Statistics_Results.h"
#include "ShowData.h"

#include <iostream>

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
                case CONFFILEDOESNTEXISTS: cerr << "Configuration file doesn't exist.\n" << endl; break;
                case CONFFILENOTGOOD     : cerr << "Error reading the configuration file.\n" << endl;
            }

            runtime_error("");
    }

    return 0;
}
