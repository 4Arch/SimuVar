/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.19            Version: 20190219.2

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

#include <vector>

Environment  FullfilEnvData() {

    Environment Env;
    vector<string> KeyList {"Number of generations",
                            "Initial Population",
                            "Max of Meeting Per Generation",
                            "Min Age Of Fertility",
                            "Max Life Time Male",
                            "Max Life Time Female",
                            "Child Mortality Rate",
                            "Max Fertility",
                            "Initial Willing to Marry",
                            "Max Decay Of Fertility After Child Birth Male",
                            "Max Decay Of Fertility After Child Birth Female",
                            "Max Decay Of Natural Fertility Per Generation Male",
                            "Max Decay Of Natural Fertility Per Generation Female",
                            "Max Decay of Willingness to Marry Per Generation Male",
                            "Max Decay of Willingness to Marry Per Generation Female"};

    auto Values = ReadConfigurations("SimuVar.conf", KeyList);

    Env.NumberOfGenerations                         = CastConfData(Env.NumberOfGenerations                          , Values[0]);
    Env.InitialPopulation                           = CastConfData(Env.InitialPopulation                            , Values[1]);
    Env.MeetingMaxPerGeneration                     = CastConfData(Env.MeetingMaxPerGeneration                      , Values[2]);
    Env.MinAgeOfFertility                           = CastConfData(Env.MinAgeOfFertility                            , Values[3]);
    Env.MaxLifeTime[0]                              = CastConfData(Env.MaxLifeTime[0]                               , Values[4]);
    Env.MaxLifeTime[1]                              = CastConfData(Env.MaxLifeTime[1]                               , Values[5]);
    Env.ChildMortalityRate                          = CastConfData(Env.ChildMortalityRate                           , Values[6]);
    Env.MaxFertility                                = CastConfData(Env.MaxFertility                                 , Values[7]);
    Env.InitialWilling2Marry                        = CastConfData(Env.InitialWilling2Marry                         , Values[8]);
    Env.MaxDecayOfFertilityAfterChildBirth[0]       = CastConfData(Env.MaxDecayOfFertilityAfterChildBirth[0]        , Values[9]);
    Env.MaxDecayOfFertilityAfterChildBirth[1]       = CastConfData(Env.MaxDecayOfFertilityAfterChildBirth[1]        , Values[10]);
    Env.MaxDecayOfNaturalFertilityPerGeneration[0]  = CastConfData(Env.MaxDecayOfNaturalFertilityPerGeneration[0]   , Values[11]);
    Env.MaxDecayOfNaturalFertilityPerGeneration[1]  = CastConfData(Env.MaxDecayOfNaturalFertilityPerGeneration[1]   , Values[12]);
    Env.MaxDecayofWillingness2MarryPerGeneration[0] = CastConfData(Env.MaxDecayofWillingness2MarryPerGeneration[0]  , Values[13]);
    Env.MaxDecayofWillingness2MarryPerGeneration[1] = CastConfData(Env.MaxDecayofWillingness2MarryPerGeneration[1]  , Values[14]);

    return Env;
}
