#include <glug/power/bindings/c++/power.hpp>

#include <iostream>

using namespace std;
using namespace glug;

int main()
{
    cout << boolalpha << "A/C power connected: " << power::has_ac() << endl;
    cout << "power supply: " << power::active_supply() << endl;
    cout << "battery state: " << power::battery_state() << endl;
    cout << "battery %: " << static_cast<int>(power::battery_level()) << endl;

    const long long time = power::battery_time();
    cout << "time left: " << time / 60 / 60 << ':' << time / 60 % 60 << ':' << time % 60 << endl;
}
