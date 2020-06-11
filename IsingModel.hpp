#ifndef ISINGMODEL_HPP_INCLUDED
#define ISINGMODEL_HPP_INCLUDED

#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ctime>

#define K 1000000
#define K_0 10000

class Ising
{
    public:
        int L;
        double T;
        Ising();
        ~Ising();
        void Simulation_1(bool);
        void Simulation_2(bool);
        void Simulation_3(bool);
        void CreateMeanMagnFile();          //utworzenie pliku do zapisu sredniej magnetyzacji dla zakresu temperatur
        void CreateSuscFile();              //utworzenie pliku do zapisu podatnosci dla zakresu temperatur
    private:
        int **arr;                          //tablica wartosci spinow wezlow ukladu
        int i, j, dE, step, diffK;
        double m, x, Msum, Msum_sq;
        unsigned s;
        std::mt19937 generator;
        std::string magn_filename;
        std::fstream magn_file;
        std::string spinch_filename;
        std::fstream spinch_file;
        std::string mean_magn_filename;
        std::fstream mean_magn_file;
        std::string susc_filename;
        std::fstream susc_file;

        void MCS();                         //sekwencja pojedynczego kroku symulacji MC
        void SetArray(bool);                //inicjacja poczatkowego stanu ukladu
        void ShowArray();                   //pomocnicze wyswietlanie ukladu
        void MersenneTwister(bool);         //generator liczb losowych u¿ywany przy wyborze elementu uk³adu i losowaniu zmiennej z przedzia³u (0,1)
        bool EnergyDiff();                  //obliczanie zmiany energii i sprawdzanie czy jest mniejsza od zera
        void FlipSpin();                    //zmiana wartosci spinu i wywolanie zapisu wspolrzednych zmienionego elemnentu
        bool CheckValue();                  //sprawdzenie warunku prawdopodobienstwa obrocenia spinu
        void SetMagnetization();            //obliczenie wartosci magnetyzacji ukladu po wykonanym kroku
        void AddMagnetization();            //sumuje wartosci magnetyzacji i kwadratu magnetyzacji w kolejnych krokach MCS()
        void ClearData();                   //ustawienie poprawnych danych poczatkowych modelu
        void DeleteArray();                 //zwolnienie pamieci przed kolejna symulacja

        std::string SetTime();              //generator danych czasowych pozwalajacych na rozroznienie plikow z danymi
        std::string FormatTemperature();    //rzutuje temperature na typ string z odpowiednia precyzja

        void CreateMagnFile();              //utworzenie pliku do zapisu wartosci magnetyzacji ukladu w czasie symulacji
        void AppendNewMagn();               //zapis wartosci magnetyzacji m(t) do pliku
        void CreateSpinChangeFile();        //utworzenie pliku do zapisu wspolrzednych obracanych spinow
        void SaveLattice();                 //zapis stanu calego ukladu do pliku
        void AppendNewMeanMagn();           //zapis kolejnej wartosci sredniej magnetyzacji dla danego L
        void AppendNewSusc();               //zapis kolejnej wartosci podatnosci dla danego L
};

#endif // ISINGMODEL_HPP_INCLUDED
