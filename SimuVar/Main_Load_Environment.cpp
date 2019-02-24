/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.19            Version: 20190219.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "../ReadConfigurations/ReadConfigurations.h"
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
