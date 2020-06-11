#include "IsingModel.hpp"

void Ising::SetArray(bool rand)
{
    arr = new int *[L];
    for(int it=0; it<L; it++)
    {
        arr[it] = new int [L];
        for(int jt=0; jt<L; jt++)
        {
            if(rand)
            {
                int a = this->generator() % 2;
                if(a == 0)
                    arr[it][jt] = 1;
                else
                    arr[it][jt] = -1;
            }
            else
                arr[it][jt] = 1;
        }
    }
}

void Ising::ShowArray()
{
    for(int it=0; it<L; it++)
    {
        for(int jt=0; jt<L; jt++)
            std::cout << arr[it][jt] << " ";
        std::cout << std::endl;
    }
}

void Ising::MersenneTwister(bool a)
{
    if(a)
    {
        std::uniform_int_distribution<int> dis(0, (this->L)-1);
        this->i = dis(generator);
        this->j = dis(generator);
    }
    else
    {
        std::uniform_real_distribution<double> dis(0, 1);
        this->x = dis(generator);
    }
}

bool Ising::EnergyDiff()
{
    this->dE = (arr[(i+1)%L][j] + arr[(i-1+L)%L][j] + arr[i][(j+1)%L] + arr[i][(j-1+L)%L]) * 2 * arr[i][j];
    return (this->dE < 0);
}

void Ising::FlipSpin()
{
    arr[i][j] *= -1;
}

bool Ising::CheckValue()
{
    return (x < exp((-dE*1.0)/T));
}

void Ising::SetMagnetization()
{
    int sum = 0;
    for(int it=0; it<L; it++)
        for(int jt=0; jt<L; jt++)
            sum += arr[it][jt];
    m = (1.0*sum)/(L*L);
}

void Ising::AddMagnetization()
{
    this->Msum += fabs(this->m);
    this->Msum_sq += (this->m) * (this->m);
}

void Ising::ClearData()
{
    i = j = 0;
    m = 1;
    step = 1;
    dE = 0;
    Msum = Msum_sq = 0;
}

void Ising::DeleteArray()
{
    for(int k=0; k<(this->L); k++)
        delete [] arr[k];
    delete [] arr;
}
