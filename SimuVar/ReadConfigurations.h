/**
    File    : ReadConfigurations.h
    Author  : Menashe Rosemberg
    Created : 2016.10.14            Version: 20190219.1

    Read Configuration File

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
/*  Important!
        File Conf:
            a. All spaces will be ignored
            b. Keywords are not case-sensitive
            c. the carcter '=' comes after every keywords
        In Code:
            a. the vector values returned follows the same order of KeyList
            b. The default value to the keywords is 0;
*/
#ifndef READCONFIGURATIONS_H
#define READCONFIGURATIONS_H

#include <any>
#include <cctype>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <filesystem>
#include <string_view>

using namespace std;
namespace fs = std::filesystem;

constexpr short CONFFILEDOESNTEXISTS = 0;
constexpr short CONFFILENOTGOOD      = 1;

vector<any> ReadConfigurations(const string ConfFile, const vector<string>& KeyList);

///Use this function to cast the values read
template<typename Variable>
constexpr Variable CastConfData(const Variable VarDestiny, const any& AnyValue) {
                   return static_cast<decltype(VarDestiny)>(any_cast<long double>(AnyValue));
}

#endif // READCONFIGURATIONS_H
