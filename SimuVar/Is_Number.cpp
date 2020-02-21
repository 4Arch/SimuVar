/**
    File    : Is_Number.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.19            Version: 20190219.1

    Check if a string is a number

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Is_Number.h"

bool is_number(const std::string& TxT) {
     bool OnePoint = true;

     for (auto Letter = TxT.cbegin() + (TxT[0] == '-'? 1 : 0); Letter != TxT.cend(); ++Letter)
        if (*Letter =='.' && OnePoint)
            OnePoint = false;
        else if (!isdigit(*Letter))
                return false;

     return true;
}
