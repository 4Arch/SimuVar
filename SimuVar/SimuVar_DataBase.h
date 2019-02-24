/**
    File    : SimuVar_Life.h
    Author  : Menashe Rosemberg
    Created : 2019.02.11            Version: 20190217.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
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
