#include <glug/power/power.h>

#include <iostream>

using namespace std;

int main()
{
    cout << "power supply: " << glug_power_active_supply() << endl;
    cout << "battery state: " << glug_power_battery_state() << endl;
    cout << "battery %: " << static_cast<int>(glug_power_battery_level()) << endl;

    const long long time = glug_power_battery_time();
    cout << "time left: " << time / 60 / 60 << ':' << time / 60 % 60 << ':' << time % 60 << endl;
}
