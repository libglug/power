set(
    OSX_SOURCE
    src/power_bridge_osx.c
    src/iops/iops.h
    src/iops/ac.c
    src/iops/battery.c
)

set(
    OSX_LIBS
    CoreFoundation
    IOKit
)
