/**
    File    : ReadConfigurations.cpp
    Author  : Menashe Rosemberg
    Created : 2016.10.14            Version: 20190219.2

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
/*  Update
        1. need to keep string too
*/
#include "ReadConfigurations.h"
#include "Is_Number.h"

static string PatterningTxT(string TxT2Format) {
              TxT2Format.erase(remove(TxT2Format.begin(), TxT2Format.end(), ' '), TxT2Format.end());
              transform(TxT2Format.begin(), TxT2Format.end(), TxT2Format.begin(), ::tolower);

              return TxT2Format;
}

vector<any> ReadConfigurations(const string ConfFile, const vector<string>& KeyList) {
    try {
        if (!fs::exists(ConfFile)) throw CONFFILEDOESNTEXISTS;

        ifstream fFile(ConfFile);

        if (!fFile.good()) throw CONFFILENOTGOOD;

        vector<any> Values(KeyList.size(), 0.0L);
        string Val;
        string RawLine;

        while (!fFile.eof()) {
            getline(fFile, RawLine);

            RawLine = PatterningTxT(RawLine);

            if (string::size_type Pos = RawLine.find('='); Pos != string::npos && RawLine.back() != '=') {
                string_view ViewRawLine = string_view(RawLine).substr(0, Pos);

                for (vector<string>::size_type IIt = 0; IIt < KeyList.size(); ++ IIt)
                    if (ViewRawLine == PatterningTxT(KeyList[IIt])) {
                        RawLine.erase(0, Pos + 1);

                        if (is_number(RawLine))
                            Values[IIt] = stold(RawLine);

                        break;
                    }
            }
        }

        return Values;

    } catch (const short Exc) {
            throw Exc;
    } catch (const exception& Exc) {
            throw Exc;
    }
}
