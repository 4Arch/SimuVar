/**
    File    : ReadConfigurations.h
    Author  : Menashe Rosemberg
    Created : 2016.10.14            Version: 20190219.1

    Read Configuration File

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
