/**
    File    : SimuVar_Life.h
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190217.1

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
#ifndef DATABASE_H
#define DATABASE_H

#include "SimuVar_Person.h"

#include <set>
#include <list>
#include <vector>

using namespace std;

using BookOfLife    = list<Person>;
using NOTSigningUp  = vector<FullGene>;

struct IdxDBook {
       IdxDBook(const GeneType Sequence, const NOfTwins TwinNumber, BookOfLife::iterator Point2) : Genes(Sequence, TwinNumber), Point2Person(Point2) {};
       const FullGene Genes;
       const BookOfLife::iterator Point2Person;
};

namespace std {
    template<> struct less<IdxDBook> {
        using is_transparent = void;
        bool operator()(const IdxDBook& lhs, const IdxDBook& rhs) const { return lhs.Genes.Sequence < rhs.Genes.Sequence; }
        bool operator()(const GeneType lhs, const IdxDBook& rhs) const { return lhs < rhs.Genes.Sequence; }
        bool operator()(const IdxDBook& lhs, const GeneType rhs) const { return lhs.Genes.Sequence < rhs; }
    };
}

using BookOfLife_Idx    = multiset<IdxDBook>;
using BookOfLife_IdxIIt = multiset<IdxDBook>::const_iterator;

#endif // DATABASE_H
