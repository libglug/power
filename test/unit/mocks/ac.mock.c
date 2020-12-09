#include "ac.mock.h"

static int ac_enabled = 1;

void enable_ac()
{
    ac_enabled = 1;
}

void disable_ac()
{
    ac_enabled = 0;
}

int has_ac()
{
    return ac_enabled;
}
