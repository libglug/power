set(
    OSX_SOURCE
    src/power_bridge_osx.c
    src/iops/iops.h
    src/iops/iops.c

    src/macos/power.c
    src/macos/battery_node.c
)

set(
    OSX_LIBS
    CoreFoundation
    IOKit
)
