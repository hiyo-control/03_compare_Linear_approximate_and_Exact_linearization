#ifndef CONTROLLER
#define CONTROLLER

#include "./config.h"
#include "./pendulum_system.h"
#include "./read_ini_file.h"

extern const int STATE_SIZE;

class Controller
{
private:
    // Physical constant
    float g;

    // Pendulum parameter
    float mp, lp, dp, Ip;

    // FB gain (linear approximate)
    array<float, STATE_SIZE> Linear_approx_FB, Exact_linear_FB;

    // Control input
    float input_Linear_approx, input_Exact_linear;

public:
    Controller();
    void begin();
    float get_Linear_approx_input();
    float get_Exact_linear_input();
    float calc_Linear_approx_input(array<float, STATE_SIZE> state);
    float calc_Exact_linear_input(array<float, STATE_SIZE> state);
};

#endif