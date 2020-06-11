#include "IsingModel.hpp"
using namespace std;

int main()
{
    Ising model;
    bool rs = false; //zmienna ustawiajaca tryb poczatkowego ukladu (false - uporzadkowany, true - rozburzony)

    int arr_size[3] = {10,50,100};
    double temp_sym1[3] = {1.0, 2.26, 4.0};
    double temp_sym2[3] = {1.7, 2.26, 3.5};

    //pierwszy rodzaj symulacji - wizualizacja zmian stanu ukladu
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            model.L = arr_size[i];
            model.T = temp_sym1[j];
            model.Simulation_1(rs);
        }

    //drugi rodzaj symulacji - trajektorie magnetyzacji
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            model.L = arr_size[i];
            model.T = temp_sym2[j];
            model.Simulation_2(rs);
        }

    //trzeci rodzaj symulacji - zaleznosc sredniej magnetyzacji i podatnosci magnetycznej od temperatury
    for(int i=0; i<3; i++)
    {
        double temp_sym3 = 1;
        model.L = arr_size[i];
        model.CreateMeanMagnFile();
        model.CreateSuscFile();
        do
        {
            model.T = temp_sym3;
            model.Simulation_3(rs);
            temp_sym3 += 0.25;
        }
        while(temp_sym3 < 1.75);
        do
        {
            model.T = temp_sym3;
            model.Simulation_3(rs);
            temp_sym3 += 0.1;
        }
         while(temp_sym3 < 2);
        do
        {
            model.T = temp_sym3;
            model.Simulation_3(rs);
            temp_sym3 += 0.05;
        }
        while(temp_sym3 < 2.65);
        do
        {
            model.T = temp_sym3;
            model.Simulation_3(rs);
            temp_sym3 += 0.15;
        }
        while(temp_sym3 < 3.1);
        do
        {
            model.T = temp_sym3;
            model.Simulation_3(rs);
            temp_sym3 += 0.25;
        }
        while(temp_sym3 <= 3.85);
    }

    return 0;
}
