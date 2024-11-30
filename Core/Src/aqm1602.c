/*
 * aqm1602.c
 *
 *  Created on: Nov 30, 2024
 *      Author: sata
 */


#include "aqm1602.h"



static void aqm1602_command(uint8_t cmd);
static void aqm1602_data(uint8_t dat);


/**
 * @brief AQM1602にコマンドを送信する
 *
 * @param cmd コマンド
 */
void aqm1602_command(uint8_t cmd)
{
    uint8_t buf[2] = {0x00, cmd};

    while (HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDR_AQM1602, (uint8_t*)buf, 2, 1000) != HAL_OK) {
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
            Error_Handler();
        }
    }
}

/**
 * @brief AQM1602にデータを送信する
 *
 * @param dat データ
 */
void aqm1602_data(uint8_t dat)
{
    uint8_t buf[2] = {0x40, dat};

    while (HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDR_AQM1602, (uint8_t*)buf, 2, 1000) != HAL_OK) {
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
            Error_Handler();
        }
    }
}

/**
 * @brief LCDのカーソル位置に文字列を表示する
 *
 * @param str
 */
void aqm1602_print(const char *str)
{
    while (*str) {
        aqm1602_data(*str++);
    }
}

/**
 * @brief LCDを初期化する
 *
 * @param c コントラスト (0~63)
 */
void aqm1602_init(uint8_t c)
{
    aqm1602_command(0x38);                      // function set
    aqm1602_command(0x39);                      // function set
    aqm1602_command(0x14);                      // interval osc
    aqm1602_command(0x70 | (c & 0x0f));         // contrast low
    aqm1602_command(0x5c | (c >> 4 & 0x03));    // contrast high / icon / power
    aqm1602_command(0x6c);                      // follower control
    HAL_Delay(300);
    aqm1602_command(0x38);                      // function set
    aqm1602_command(0x0c);                      // display on
    aqm1602_command(0x01);                      // clear display
    HAL_Delay(2);
}

// 基本aqm1602_posを使う
#if 0
/**
 * @brief LCDのカーソルを移動する
 *
 * @param pos 位置
 */
void aqm1602_move(uint8_t pos)
{
    aqm1602_command(0x80 | pos);
}
#endif

/**
 * @brief LCDのカーソルを移動する
 *
 * @param raw 行 (0-1)
 * @param col 列 (0-15)
 */
void aqm1602_pos(uint8_t raw, uint8_t col)
{
    aqm1602_command(0x80 | ((raw & 0x01) << 6) | col);
}

/**
 * @brief LCDの表示をクリアする
 *
 */
void aqm1602_clear(void)
{
    aqm1602_command(0x01);
}


