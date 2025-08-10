#include "DataLog.h"

DataLog::DataLog()
{
}

void DataLog::begin()
{
    // Initialize data vector
    time_data.clear();
    input_data.clear();
    x1_data.clear();
    x2_data.clear();
}

void DataLog::makeCSVfile()
{
    filename = "simu_result.csv";
    file.open(filename);

    if(!file.is_open())
    {
        cerr << "file can not open" << endl;
    }
    char csv_label[] = "time [sec], angle [deg], angle velocity [deg/sec]";
    file << csv_label << endl;
}

void DataLog::MakeDataMatrix(float time, array<float, STATE_SIZE> state, float input)
{
    time_data.push_back(time);
    x1_data.push_back(state[0]);
    x2_data.push_back(state[1]);
    input_data.push_back(input);
}

void DataLog::outputCSVfile()
{
    makeCSVfile();
    LogMatrixData();
    file.close();
}

void DataLog::LogMatrixData()
{
    int data_num = time_data.size();
    for(int i=0; i<data_num; i++)
    {
        file << time_data[i] << "," << x1_data[i] << "," << x2_data[i] << "," << input_data[i] << endl;
    }
}

