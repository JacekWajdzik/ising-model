#include "IsingModel.hpp"

std::string Ising::SetTime()
{
    time_t t_data;
    time(&t_data);
    struct tm *timeTM;
    timeTM = localtime(&t_data);
    std::string day = std::to_string(timeTM->tm_mon + 1) + std::to_string(timeTM->tm_mday) + "_";
    std::string clock = std::to_string(timeTM->tm_hour) + std::to_string(timeTM->tm_min) + std::to_string(timeTM->tm_sec);
    return day+clock;
}

std::string Ising::FormatTemperature()
{
    std::stringstream ss;
    ss.setf(std::ios_base::fixed);
    ss.precision(2);
    ss << (this->T);
    return ss.str();
}

void Ising::CreateMagnFile()
{
    magn_filename = "magn_L" + std::to_string(this->L) + "_T" + this->FormatTemperature() + "_" + this->SetTime() + ".txt";
    std::ofstream (magn_filename.c_str());
}

void Ising::AppendNewMagn()
{
    magn_file.open(this->magn_filename, std::ios::app);
    if(magn_file.good())
    {
        magn_file << this->m << std::endl;
        magn_file.close();
    }
}

void Ising::CreateSpinChangeFile()
{
    spinch_filename = "spinch_L" + std::to_string(this->L) + "_T" + this->FormatTemperature() + ".txt";
    std::ofstream (spinch_filename.c_str());
}

void Ising::SaveLattice()
{
    spinch_file.open(this->spinch_filename, std::ios::app);
    if(spinch_file.good())
    {
        spinch_file << (this->step) << std::endl;
        for(int k=0; k<this->L; k++)
        {
            for(int l=0; l<this->L; l++)
                spinch_file << arr[k][l] << " ";
            spinch_file << std::endl;
        }
        spinch_file.close();
    }
}

void Ising::CreateMeanMagnFile()
{
    mean_magn_filename = "meanMagn_L" + std::to_string(this->L) + "_" + this->SetTime() + ".txt";
    std::ofstream (mean_magn_filename.c_str());
}

void Ising::AppendNewMeanMagn()
{
    mean_magn_file.open(this->mean_magn_filename, std::ios::app);
    if(mean_magn_file.good())
    {
        mean_magn_file << this->FormatTemperature() << "\t" << (this->Msum)*1.0/(this->diffK) << std::endl;
        mean_magn_file.close();
    }
}

void Ising::CreateSuscFile()
{
    susc_filename = "susceptibility_L" + std::to_string(this->L) + "_" + this->SetTime() + ".txt";
    std::ofstream (susc_filename.c_str());
}

void Ising::AppendNewSusc()
{
    susc_file.open(this->susc_filename, std::ios::app);
    if(susc_file.good())
    {
        double mean_m_sq = (this->Msum_sq)*1.0/(this->diffK);
        double sq_mean_m = ((this->Msum)*1.0/(this->diffK)) * ((this->Msum)*1.0/(this->diffK));
        double susc = ((this->L)*(this->L)/(this->T)) * (mean_m_sq - sq_mean_m);
        susc_file << this->FormatTemperature() << "\t" << susc << std::endl;
        susc_file.close();
    }
}
