/**
    File    : Main.cpp
    Author  : Menashe Rosemberg
    Created : 2019.02.18            Version: 20190218.1

    Simulation of Population Growth and Genetic Variation (סימולציה של גידול האוכלוסייה והשונות הגנטית)

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright (c) 2019     All rights reserved.

    Redistribution and use of source or/and binary forms, with or without modification are not permitted,
    unless with an express Author's permission.

    Software distributed under the License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
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
    void ShowAvePer(float Value) {
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
                cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------|"
                     << "\n     |      |          Population              |   Women Alive    |     Men Alive    |        |  Women Deceased   |    Men Deceased   |"
                     << "\nYear |VarGen| Alive |AvAge|Coup%|Relat| Mates  | Tot. |Aver%|AvAge| Tot. |Aver%|AvAge|Deceased| Total |Aver%|AvAge| Total |Aver%|AvAge|"
                     << "\n--------------------------------------------------------------------------------------------------------------------------------------|"
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
                 ShowAvePer (STATUS.Av_Couples);
                 ShowAverage(5, STATUS.Av_Relatives);
                 ShowAverage(8, STATUS.Av_Friends);
                 ShowVar(6,  STATUS.Tot_Women_Alive);
                 ShowAvePer( STATUS.Av_Women_Alive);
                 ShowAverage(5, STATUS.Av_Age_Womens_Alive);
                 ShowVar(6,  STATUS.Tot_Men_Alive);
                 ShowAvePer( STATUS.Av_Men_Alive);
                 ShowAverage(5, STATUS.Av_Age_Mens_Alive);
                 ShowVar(8,  STATUS.Tot_Women_Souls + STATUS.Tot_Men_Souls);    //Deceased
                 ShowVar(7,  STATUS.Tot_Women_Souls);                           //Total Women Deceased
                 ShowAvePer( STATUS.Av_Women_Souls);                            //Average Women Deceased
                 ShowAverage(5, STATUS.Av_Age_Womens_Souls);                    //Average Age of Women Deceased
                 ShowVar(7,  STATUS.Tot_Men_Souls);                             //Total Men Deceased
                 ShowAvePer( STATUS.Av_Men_Souls);                              //Average Men Decease
                 ShowAverage(5, STATUS.Av_Age_Mens_Souls);                      //Average Age of Men Deceased
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
             ShowAvePer (FINAL.MaxAvCouples);
             ShowAverage(8, FINAL.MaxAvFamilySize);
             ShowAverage(8, FINAL.MaxAvFriendsSize);

             cout << "\n\n";
        }
};

#endif // SHORDATA_H
