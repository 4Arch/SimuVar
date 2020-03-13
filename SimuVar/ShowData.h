/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.18            Version: 20190302.1

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
#ifndef SHORDATA_H
#define SHORDATA_H

#include <iostream>
#include <iomanip>

class ShowTime {

    bool HasCivilization = true;
    bool CivilizationWillLive = true;

    template <typename TN>
    void ShowVar(uint8_t Width, TN Value) const {
         cout << setw(Width) << Value << ' '; }
    void ShowAverage(uint16_t Width, float Value) {
         cout << fixed << setprecision(1) << setw(Width) << Value << ' '; }
    void ShowPercent(float Value) {
         cout << fixed << setprecision(1) << setw(5) << (Value*100) << ' '; }

    public:
       ShowTime() { cout << "\n\n\nSimulation of Population Growth and Genetic Variation\n"
                         << "תיטנגה תונושהו הייסולכואה לודיג לש היצלומיס"
                         << "\n\nMenashe Rosemberg Israel +972-52-323-0538\nCopyright (c) 2019   All rights reserved.\n\n\n"; }
      ~ShowTime() = default;

        void Header(const uint16_t ShowHeader, const uint16_t Pause, const YearType Generation) const {
             if (Generation % Pause == 0) {
                cout << "Press <enter> to Continue...";
                cin.get();
             }
             if (Generation % ShowHeader == 0)
                cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------------------|"
                     << "\n     |      |          Population              |   Women Alive    |     Men Alive    |        |  Women Deceased   |    Men Deceased   |  Growth   |"
                     << "\nYear |VarGen| Alive |AvAge|Coup%|Relat| Mates  | Tot. |Aver%|AvAge| Tot. |Aver%|AvAge|Deceased| Total |Aver%|AvAge| Total |Aver%|AvAge|G.V.%|Pop.%|"
                     << "\n--------------------------------------------------------------------------------------------------------------------------------------------------|"
                     << flush;

             cout << '\n';
        }

        void Show(const Status& STATUS, const uint16_t ShowHeader = 40, const uint16_t Pause = 1'000) {

             if (HasCivilization) {
                 this->Header(ShowHeader, Pause, STATUS.Generation);
                 ShowVar(5,  STATUS.Generation);
                 ShowVar(6,  STATUS.GeneticVariation);
                 ShowVar(7,  STATUS.Tot_Men_Alive + STATUS.Tot_Women_Alive);    //Total Population Alive
                 ShowAverage(5, STATUS.Av_Livings_Ages);                        //Average of Population Age
                 ShowPercent (STATUS.Av_Couples);
                 ShowAverage(5, STATUS.Av_Relatives);
                 ShowAverage(8, STATUS.Av_Friends);
                 ShowVar(6,  STATUS.Tot_Women_Alive);
                 ShowPercent( STATUS.Av_Women_Alive);
                 ShowAverage(5, STATUS.Av_Age_Womens_Alive);
                 ShowVar(6,  STATUS.Tot_Men_Alive);
                 ShowPercent( STATUS.Av_Men_Alive);
                 ShowAverage(5, STATUS.Av_Age_Mens_Alive);
                 ShowVar(8,  STATUS.Tot_Women_Souls + STATUS.Tot_Men_Souls);    //Deceased
                 ShowVar(7,  STATUS.Tot_Women_Souls);                           //Total Women Deceased
                 ShowPercent( STATUS.Av_Women_Souls);                            //Average Women Deceased
                 ShowAverage(5, STATUS.Av_Age_Womens_Souls);                    //Average Age of Women Deceased
                 ShowVar(7,  STATUS.Tot_Men_Souls);                             //Total Men Deceased
                 ShowPercent( STATUS.Av_Men_Souls);                              //Average Men Decease
                 ShowAverage(5, STATUS.Av_Age_Mens_Souls);                      //Average Age of Men Deceased
                 ShowPercent(STATUS.Growth_GenVar);
                 ShowPercent(STATUS.Growth_Population);
                 cout << flush;

                 if ((STATUS.Tot_Men_Alive + STATUS.Tot_Women_Alive) == 0)
                    HasCivilization = false;

                 if ((STATUS.Tot_Men_Alive == 0 || STATUS.Tot_Women_Alive == 0) && CivilizationWillLive) {
                    CivilizationWillLive = false;
                    cout << "\n\nCivilization will die. Press <enter> to continue..."; cin.get();
                 }
             }
        }

        void Show(const FinalStatus& FINAL) {
             cout << "\n\n--------------------------------------------------|"
                  << "\n    Best Results to Biggest Genetic Variation     |"
                  << "\n--------------------------------------------------|"
                  << "\nYear |VarGen| Alive |AvAge|Coup%| Relat. | Friends|"
                  << "\n---------------------------------------------------\n"
                  << endl;

             ShowVar(5,  FINAL.LastGeneration);
             ShowVar(6,  FINAL.MaxGeneticVariation);
             ShowVar(7,  FINAL.MaxPopulation);
             ShowAverage(5, FINAL.MaxAvAge);
             ShowPercent (FINAL.MaxAvCouples);
             ShowAverage(8, FINAL.MaxAvFamilySize);
             ShowAverage(8, FINAL.MaxAvFriendsSize);

             cout << "\n\n";
        }
};

#endif // SHORDATA_H
