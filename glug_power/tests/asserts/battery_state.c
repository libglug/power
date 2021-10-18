#include "battery_state.h"
#include <CUnit/Assert.h>

void assert_battery_state_equal(const struct battery_state *b1, const struct battery_state *b2)
{
    CU_ASSERT_EQUAL(b1->count, b2->count);
    CU_ASSERT_EQUAL(b1->ncharged, b2->ncharged);
    CU_ASSERT_EQUAL(b1->ncharging, b2->ncharging);
}
