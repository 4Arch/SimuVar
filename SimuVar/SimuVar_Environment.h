/**
    File    : SimuVar_Environment.h
    Author  : Menashe Rosemberg
    Created : 2019.02.10            Version: 20190214.4

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
