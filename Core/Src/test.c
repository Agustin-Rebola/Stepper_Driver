#include "test.h"
#include "as5600.h"
#include "globals.h"
#include <string.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>


extern I2C_HandleTypeDef hi2c1;



// ---------- Print magnet status ----------

void test_status(uint8_t st)
{
    const bool md = (st & AS5600_STATUS_MAG_DET) != 0;
    const bool ml = (st & AS5600_STATUS_MAG_LP ) != 0;
    const bool mh = (st & AS5600_STATUS_MAG_HP ) != 0;
}


void test_init(void)
{

}


void test_loop(void)
{
    uint16_t ticks = 0;
    if(as5600_read_angle(&hi2c1, &ticks)){
    	angle_ticks = &ticks;
    	angle_deg = as5600_ticks_to_deg(angle_ticks);

    }
}
