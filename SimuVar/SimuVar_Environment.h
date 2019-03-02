/**
    File    : SimuVar_Environment.h
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190214.4

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <cinttypes>

using Meet     = uint8_t;
using LifeTime = uint8_t;
using YearType = uint32_t;
using GeneType = uint64_t;
using NOfTwins = uint16_t;

constexpr uint8_t GeneSubSegmentSize = sizeof(GeneType)*2;      //Every segment has 4bits doesn't matter the size of gene

struct Environment {
       uint32_t NumberOfGenerations = 1'000;
       Meet InitialPopulation = 23;                                         //Minimum 2 Maximum 255
       Meet MeetingMaxPerGeneration = 5;                                    //Minimum 1 Maximum 255
       LifeTime MinAgeOfFertility = 18;
       LifeTime MaxLifeTime[2] = {110, 120};                                //Male-Female
       float ChildMortalityRate = 0.05;
       float MaxFertility = 0.25;
       float MaxDecayOfNaturalFertilityPerGeneration[2] = {0.001, 0.015};   //Male-Female
       float MaxDecayOfFertilityAfterChildBirth[2] = {0.01, 0.05};          //Male-Female
       float InitialWilling2Marry = 0.9;
       float MaxDecayofWillingness2MarryPerGeneration[2] = {0.001, 0.005};  //Male-Female
};

Environment  FullfilEnvData();

#endif // ENVIRONMENT_H
