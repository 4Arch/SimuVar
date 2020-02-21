/**
    File    : ReadConfigurations.cpp
    Author  : Menashe Rosemberg
    Created : 2016.10.14            Version: 20190219.2

    Read Configuration File

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
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
