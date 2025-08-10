#include "./controller.h"

Controller::Controller()
{
    INIReader reader;
    if (!reader.load("config.ini"))
    {
        cerr << "Failed to load INI file." << endl;
    }
    // Physical constant
    g = stof( reader.get("Parameter", "g") );

    // Pendulum parameter
    mp = stof( reader.get("Parameter", "mp") );
    lp = stof( reader.get("Parameter", "lp") );
    dp = stof( reader.get("Parameter", "dp") );

    // FB gain (Linear approximate)
    Linear_approx_FB[0] = stof( reader.get("Linear_approx_FB_gain", "FB_1") );
    Linear_approx_FB[1] = stof( reader.get("Linear_approx_FB_gain", "FB_2") );

    // FB gain (Linear approximate)
    Exact_linear_FB[0] = stof( reader.get("Exact_linearization_FB_gain", "FB_1") );
    Exact_linear_FB[1] = stof( reader.get("Exact_linearization_FB_gain", "FB_2") );
}

void Controller::begin()
{
    // calc Pendulum parameter (Inertia moment)
    Ip = (mp * pow(lp, 2) )/3.0f;

    input_Linear_approx = 0.0f;
    input_Exact_linear = 0.0f;
}

float Controller::calc_Linear_approx_input(array<float, STATE_SIZE> state)
{
    input_Linear_approx = 0.0f;

    for(int i=0; i<STATE_SIZE; i++)
    {
        input_Linear_approx -= Linear_approx_FB[i]*state[i];
    }
    

    return input_Linear_approx;
}

float Controller::calc_Exact_linear_input(array<float, STATE_SIZE> state)
{
    float input_buf1 = 0.0f;
    float input_buf2 = 0.0f;
    input_Exact_linear = 0.0f;

    input_buf1 = -dp*state[1]-0.5*mp*lp/Ip*g*sin(state[0]);

    for(int i=0; i<STATE_SIZE; i++)
    {
        input_buf2 -= Exact_linear_FB[i]*state[i];
    }

    input_Exact_linear = (-input_buf1 + input_buf2)/( 0.5*mp*lp/Ip*cos(state[0]) );

    return input_Exact_linear;
}

float Controller::get_Linear_approx_input()
{
    return input_Linear_approx;
}

float Controller::get_Exact_linear_input()
{
    return input_Exact_linear;
}