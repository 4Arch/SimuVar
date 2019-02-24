/**
    File    : SimuVar_Life.h
    Author  : Menashe Rosemberg
    Created : 2019.02.15            Version: 20190215.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/

template<typename TBase>
constexpr bool IsInRange(const TBase Number, const decltype(Number) Ini, const decltype(Number) Fin) {
               return Number >= Ini && Number <= Fin; }
