#include <atomic>
#include "./include/pendulum_system.h"
#include "./include/controller.h"
#include "./include/DataLog.h"

Pendulum_system simu;
DataLog CSV_output;

atomic<bool> stop_flag(false);

int main()
{
    simu.begin();
    CSV_output.begin();

    cout << "Start simulation" << endl;

    while(!stop_flag)
    {
        // Data logging
        auto time  = simu.get_time();
        auto state = simu.get_state();
        auto input = simu.get_input();

        CSV_output.MakeDataMatrix(time, state, input);

        // Calculate dynamics
        simu.simulation_execution();
        stop_flag = simu.simu_end_flag();
    }

    cout << "End simulation" << endl;
    cout << "Make CSV file" << endl;

    CSV_output.outputCSVfile();

    cout << "End making CSV file" << endl;

    return 0;
}
