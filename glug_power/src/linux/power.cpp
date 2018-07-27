#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

namespace glug
{

static const std::string power_root("/sys/class/power_supply");
static const std::string ac_prefix("ACAD");
static const std::string ac_online_file("online");
static const std::string batt_prefix("BAT");
static const std::string batt_status_key("status");
static const std::string batt_percent_key("capacity");
static const std::string batt_whour_key("energy_now");
static const std::string batt_watt_key("power_now");
static const std::string batt_charging_val("Charging");
static const std::string batt_charged_val("Full");

static long pow_src_stat(const std::string &pow_src, const std::string &key)
{
    std::ifstream stat(power_root + '/' + pow_src + '/' + key);

    long val = 0;
    stat >> val;
    if (stat.rdstate()) return -1;

    return val;
}

static std::string pow_src_string(const std::string &pow_src, const std::string &key)
{
    std::ifstream stat(power_root + '/' + pow_src + '/' + key);

    std::string val;
    std::getline(stat, val);

    return std::move(val);
}

static size_t battery_count()
{
    size_t count = 0;
    DIR *power_dir = opendir(power_root.c_str());
    if (!power_dir) return count;

    dirent *ent;
    for (; ent = readdir(power_dir);)
    {
        std::string battery_name(ent->d_name);
        if (battery_name.find(batt_prefix) == 0)
            ++count;
    }

    return count;
}

static std::vector<std::string> battery_names()
{
    std::vector<std::string> batteries;

    DIR *power_dir = opendir(power_root.c_str());
    if (!power_dir) return std::move(batteries);

    dirent *ent;
    for (; ent = readdir(power_dir);)
    {
        std::string battery_name(ent->d_name);
        if (battery_name.find(batt_prefix) != std::string::npos)
            batteries.push_back(std::move(battery_name));
    }
    closedir(power_dir);

    return std::move(batteries);
}

static bool any_charging(const std::vector<std::string> batteries)
{
    bool is_charging = false;
    for (const std::string &battery_name: batteries)
        is_charging = is_charging || pow_src_string(battery_name, batt_status_key) == batt_charging_val;

    return is_charging;
}

static bool all_charged(const std::vector<std::string> batteries)
{
    bool is_charged = true;
    for (const std::string &battery_name: batteries)
        is_charged = is_charged && pow_src_string(battery_name, batt_status_key) == batt_charged_val;

    return is_charged;
}

power_supply power_state()
{
    if (pow_src_stat(ac_prefix, ac_online_file) > 0) return ps_ac;
    if (battery_count() > 0)                         return ps_battery;
    return ps_unknown;
}

battery_status battery_state()
{
    std::vector<std::string> batteries = battery_names();
    const bool has_ac = pow_src_stat(ac_prefix, ac_online_file) > 0;
    const bool has_battery = batteries.size() > 0;

    if (!has_battery && has_ac)  return bs_none;
    if (has_battery && !has_ac)  return bs_discharging;
    if (any_charging(batteries)) return bs_charging;
    if (all_charged(batteries))  return bs_charged;
    return bs_unknown;
}

char battery_pct()
{
    std::vector<std::string> batteries = battery_names();
    if (!batteries.size()) return -1;

    int avg_capacity = 0;
    for (std::string battery_name: batteries)
    {
        long capacity = pow_src_stat(battery_name, batt_percent_key);

        if (capacity > -1)
            avg_capacity += capacity;
    }

    return avg_capacity / batteries.size();
}

long long battery_time()
{
    if (pow_src_stat(ac_prefix, ac_online_file) > 0) return -1;

    std::vector<std::string> batteries = battery_names();
    if (!batteries.size()) return -1;

    long long remaining_time = -1;
    for (std::string battery_name: batteries)
    {
        long watts = pow_src_stat(battery_name, batt_watt_key);
        long watthours = pow_src_stat(battery_name, batt_whour_key);

        if (watts > -1 && watthours > 0)
            remaining_time = std::max(watthours * 60ll * 60 / watts, remaining_time);
    }

    return remaining_time;
}

} // namespace glug
