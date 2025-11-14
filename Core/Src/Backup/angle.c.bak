#include "test.h"
#include "as5600.h"
#include "globals.h"
#include "usart.h"
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;


// ---------- Print magnet status ----------



void uart_send_angle(void)
{
	char msg_a[32];
	int len = snprintf(msg_a, sizeof(msg_a), "Angle: %.2f\r\n", angle_deg);
	HAL_UART_Transmit(&huart1, (uint8_t*)msg_a, len, 100);
}

void uart_send_velocity(void)
{
	char msg_v[32];
	int len = snprintf(msg_v, sizeof(msg_v), "Velocity: %.2f\r\n", angular_velocity);
	HAL_UART_Transmit(&huart1, (uint8_t*)msg_v, len, 100);
}


void measure_angle(void)
{
    uint16_t ticks = 0;
    uint8_t status = 0;
    static bool first_sample = true;

    as5600_read_status(&hi2c1, &status);
    bool md = (status & AS5600_STATUS_MAG_DET) != 0;

    if(!md)
    {
    	char msg[64];
    	int len = snprintf(msg, sizeof(msg),
    						"Magnet NOT detected \n");
    	HAL_UART_Transmit(&huart1, (uint8_t *)msg, len, 100);
    	return;
    }


    if(as5600_read_angle(&hi2c1, &ticks))
    {
    	float new_angle = as5600_ticks_to_deg(ticks);

    	if (first_sample) {
    	        angle_deg_prev = new_angle;
    	        angle_deg      = new_angle;
    	        angular_velocity = 0.0f;
    	        first_sample = false;
    	        uart_send_angle();
    	        return;
    	    }

    	float dt = 0.001f; 	//CHANGE BASED ON UPDATE SPEED
    	float dtheta = new_angle - angle_deg_prev;

    	if(dtheta > 180.0f) dtheta -= 360.0f;
    	if(dtheta < -180.0f) dtheta += 360.0f;
    	angular_velocity = dtheta / dt;

    	angle_deg_prev = new_angle;
    	angle_deg = new_angle;
    	uart_send_angle();
    	uart_send_velocity();
    }



}
