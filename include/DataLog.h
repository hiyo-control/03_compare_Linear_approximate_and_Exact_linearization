#ifndef DATA_LOG_H
#define DATA_LOG_H

#include "./config.h"
#include "./read_ini_file.h"
#include "./pendulum_system.h"
#include "./controller.h"

extern const int STATE_SIZE;

class DataLog
{
private:
    string filename;
    ofstream file;

    // Pendulum initial condition
    float angle_ini, angle_velo_ini;

    // Simulation result
    vector<float> time_data;
    vector<float> input_data;
    vector<float> x1_data, x2_data;

    void makeCSVfile();
    void LogMatrixData();

public:
    DataLog();
    void begin();
    void MakeDataMatrix(float time, array<float, STATE_SIZE> state, float input);
    void outputCSVfile();
};

#endif