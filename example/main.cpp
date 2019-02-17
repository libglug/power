#include <glug/power/power.h>

#include <iostream>

using namespace std;

int main()
{
    cout << "power supply: " << glug_power_state() << endl;
    cout << "battery state: " << glug_battery_state() << endl;
    cout << "battery %: " << static_cast<int>(glug_battery_pct()) << endl;

    const long long time = glug_battery_time();
    cout << "time left: " << time / 60 / 60 << ':' << time / 60 % 60 << ':' << time % 60 << endl;
}
