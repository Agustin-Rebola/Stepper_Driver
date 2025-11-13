#include "as5600.h"
#include "stm32f1xx_hal.h"

static bool i2c_mem_read(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *buf, uint16_t len, uint32_t to) {
    return HAL_I2C_Mem_Read(hi2c, AS5600_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, buf, len, to) == HAL_OK;
}
static bool i2c_mem_write(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *buf, uint16_t len, uint32_t to) {
    return HAL_I2C_Mem_Write(hi2c, AS5600_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, buf, len, to) == HAL_OK;
}

bool as5600_read_u8(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *val) {
    return i2c_mem_read(hi2c, reg, val, 1, 20);
}
bool as5600_write_u8(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t val) {
    return i2c_mem_write(hi2c, reg, &val, 1, 20);
}

bool as5600_read_raw_angle(I2C_HandleTypeDef *hi2c, uint16_t *ticks4096) {
    uint8_t hi, lo;
    if (!as5600_read_u8(hi2c, AS5600_RAW_ANGLE_H, &hi)) return false;
    if (!as5600_read_u8(hi2c, AS5600_RAW_ANGLE_L, &lo)) return false;
    *ticks4096 = ((uint16_t)hi << 8) | lo;
    return true;
}
bool as5600_read_angle(I2C_HandleTypeDef *hi2c, uint16_t *ticks4096) {
    uint8_t hi, lo;
    if (!as5600_read_u8(hi2c, AS5600_ANGLE_H, &hi)) return false;
    if (!as5600_read_u8(hi2c, AS5600_ANGLE_L, &lo)) return false;
    *ticks4096 = ((uint16_t)hi << 8) | lo;
    return true;
}
bool as5600_read_status(I2C_HandleTypeDef *hi2c, uint8_t *status) {
    return as5600_read_u8(hi2c, AS5600_STATUS, status);
}

// --- Optional: I2C1 bus recovery for Blue Pill (if SDA stuck low)
void i2c1_bus_recover(void)
{
    // Temporarily take over PB6=SCL, PB7=SDA as open-drain GPIO
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef g = {0};
    g.Mode = GPIO_MODE_OUTPUT_OD; g.Pull = GPIO_NOPULL; g.Speed = GPIO_SPEED_FREQ_LOW;

    g.Pin = GPIO_PIN_7; HAL_GPIO_Init(GPIOB, &g); // SDA
    g.Pin = GPIO_PIN_6; HAL_GPIO_Init(GPIOB, &g); // SCL

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); // SDA high
    for (int i=0; i<9; ++i) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_Delay(1);
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(1);

    // After this, call MX_I2C1_Init() again.
}
