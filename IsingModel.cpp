#include "IsingModel.hpp"

Ising::Ising()
{
    i = j = 0;
    m = 1;
    step = 1;
    dE = 0;
    Msum = Msum_sq = 0;
    s = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed (s);
}

Ising::~Ising()
{
    std::cout << "\n~DESTRUKTOR";
}

void Ising::Simulation_1(bool r)
{
    std::cout << "symulacja (1) dla L = " << this->L << " i T = " << this->T << std::endl;
    this->ClearData();
    this->SetArray(r);
    this->CreateSpinChangeFile();
    this->SaveLattice();
    for(; step <= K; step++)
    {
        this->MCS();
        if(step%1000 == 0)
            this->SaveLattice();
    }
    this->DeleteArray();
}

void Ising::Simulation_2(bool r)
{
    std::cout << "symulacja (2) dla L = " << this->L << " i T = " << this->T << std::endl;
    this->ClearData();
    this->SetArray(r);
    this->CreateMagnFile();
    this->SetMagnetization();
    this->AppendNewMagn();
    for(; step <= K; step++)
    {
        this->MCS();
        this->SetMagnetization();
        this->AppendNewMagn();
    }
    this->DeleteArray();
}

void Ising::Simulation_3(bool r)
{
    std::cout << "symulacja (3) dla L = " << this->L << " i T = " << this->T << std::endl;
    this->ClearData();
    this->SetArray(r);
    this->SetMagnetization();
    this->diffK = (K - K_0);
    for(; step <= K; step++)
    {
        this->MCS();
        if(step > K_0)
        {
            this->SetMagnetization();
            this->AddMagnetization();
        }
    }
    this->AppendNewMeanMagn();
    this->AppendNewSusc();
    this->DeleteArray();
}

void Ising::MCS()
{
    for(int k=0; k<(this->L)*(this->L); k++)
    {
        MersenneTwister(true);
        if(EnergyDiff())
            FlipSpin();
        else
        {
            MersenneTwister(false);
            if(CheckValue())
                FlipSpin();
        }
    }
}
