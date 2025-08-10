#include "./pendulum_system.h"

Controller FB;

Pendulum_system::Pendulum_system()
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

    // Pendulum initial condition
    angle_ini      = deg2rad * stof( reader.get("Initial", "angle_ini"     ) );
    angle_velo_ini = deg2rad * stof( reader.get("Initial", "angle_velo_ini") );

    // type of controller
    controller_type = stof( reader.get("Type_of_controller", "type") );

    // Simulation condition
    time_sample = stof( reader.get("simu_condition", "time_sample") );
    time_end    = stof( reader.get("simu_condition", "time_end"   ) );
}

void Pendulum_system::begin()
{
    FB.begin();

    // calc Pendulum parameter (Inertia moment)
    Ip = (mp * pow(lp, 2) )/3.0f;

    // setting Initial state
    time = 0.0f;
    input = 0.0f;
    state[0] = angle_ini;
    state[1] = angle_velo_ini;
}

array<float, STATE_SIZE> Pendulum_system::pendulum_model(array<float, STATE_SIZE> data)
{
    array<float, STATE_SIZE> dot_state;
    
    float fx2 = -dp*data[1] - 0.5*mp*lp*g/Ip*sin(data[0]);
    float gx2 = 0.5*mp*lp/Ip*cos(data[0]);

    if (controller_type == 1)
    {
        input = FB.calc_Linear_approx_input(data);
    }
    else if (controller_type == 2)
    {
        input = FB.calc_Exact_linear_input(data);
    }
    else
    {
        input = 0.0f;
    }
    
    dot_state[0] = data[1];
    dot_state[1] = fx2 + gx2*input;

    return dot_state;
}

array<float, STATE_SIZE> Pendulum_system::calc_RungeKutta_method(array<float, STATE_SIZE> data)
{
    array<float, STATE_SIZE> k1, k2, k3, k4;
    array<float, STATE_SIZE> result, dot_state;

    // Calculate k1 vector
    dot_state = pendulum_model(data);
    for (int i=0; i<STATE_SIZE; i++)
    {
        k1[i] = time_sample*dot_state[i];
    }

    // Calculate k2 vector
    dot_state = pendulum_model({data[0]+k1[0]/2.0f, data[1]+k1[1]/2.0f});
    for (int i=0; i<STATE_SIZE; i++)
    {
        k2[i] = time_sample*dot_state[i];
    }

    // Calculate k3 vector
    dot_state = pendulum_model({data[0]+k2[0]/2.0f, data[1]+k2[1]/2.0f});
    for (int i=0; i<STATE_SIZE; i++)
    {
        k3[i] = time_sample*dot_state[i];
    }

    // Calculate k4 vector
    dot_state = pendulum_model({data[0]+k3[0], data[1]+k3[1]});
    for (int i=0; i<STATE_SIZE; i++)
    {
        k4[i] = time_sample*dot_state[i];
    }

    // Calculate Next state
    for (int i=0; i<STATE_SIZE; i++)
    {
        result[i] = data[i] + (k1[i] + 2.0f*k2[i] + 2.0f*k3[i] + k4[i])/6.0f;
    }

    return result;
}

bool Pendulum_system::simu_end_flag()
{
    return time > time_end;
}

void Pendulum_system::simulation_execution()
{
    auto state_next = calc_RungeKutta_method(state);
    time = time + time_sample;

    state = state_next;
}

float Pendulum_system::get_time()
{
    return time;
}

float Pendulum_system::get_input()
{
    return input;
}

array<float, STATE_SIZE> Pendulum_system::get_state()
{
    array<float, STATE_SIZE> state_deg;

    for(int i=0; i<STATE_SIZE; i++)
    {
        state_deg[i] = rad2deg*state[i];
    }

    return state_deg;
}
