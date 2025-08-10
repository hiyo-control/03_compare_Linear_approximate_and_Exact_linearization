#ifndef PENDULUM_SYSTEM
#define PENDULUM_SYSTEM

#include "./config.h"
#include "./read_ini_file.h"
#include "./controller.h"

//constexpr int STATE_SIZE = 2;
extern const int STATE_SIZE;

class Pendulum_system
{
private:
    // Physical constant
    float g;

    // Pendulum parameter
    float mp, lp, dp, Ip;

    // Pendulum initial condition
    float angle_ini, angle_velo_ini;

    // Simulation condition
    float time_sample, time_end;

    // Type of controller
    int controller_type;

    // Simulation variable
    float input, time;
    array<float, STATE_SIZE> state;

    // funciton
    array<float, STATE_SIZE> pendulum_model(array<float, STATE_SIZE> data);
    array<float, STATE_SIZE> calc_RungeKutta_method(array<float, STATE_SIZE> data);

public:
    Pendulum_system();
    void begin();
    bool simu_end_flag();
    void simulation_execution();
    float get_time();
    float get_input();
    array<float, STATE_SIZE> get_state();
};

#endif