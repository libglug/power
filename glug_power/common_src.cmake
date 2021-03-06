set(
    COMMON_SOURCE
    common_headers/include/glug/allocator_t.h
    common_headers/include/glug/std_allocator.inl
    common_headers/include/glug/bool.h
    common_headers/include/glug/extern.h
    common_headers/include/glug/import.h
    common_headers/include/glug/os.h
    common_headers/include/glug/params.h

    include/glug/power.h
    include/glug/power/power.h
    include/glug/power/battery_status.h
    include/glug/power/power_supply.h
    include/glug/power/version.h.in

    src/power.c
    src/power_bridge.h
    src/battery_state_t.h
)

set(
    BINDINGS
)
