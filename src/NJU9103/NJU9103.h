#ifndef __NJU9103_H__
#define __NJU9103_H__

#include "mbed.h"

namespace NewJapanRadio {
    class NJU9103 {
        public:

            /**
             * @brief Register Address
             */
            enum Address {
                CTRL     = 0x0,
                ADCDATA0 = 0x1,
                ADCDATA1 = 0x2,
                PGACONF  = 0x3,
                CLKCONF  = 0x4,
                DACCONF  = 0x5,
                OPTION0  = 0x6,
                OPTION1  = 0x7,
                GAIN0    = 0x8,
                GAIN1    = 0x9,
                GAIN2    = 0xA,
                OFFSET0  = 0xB,
                OFFSET1  = 0xC,
                OFFSET2  = 0xD
            };

            NJU9103();
            ~NJU9103();

            /**
             * @brief Reset NJU9103 via SPI
             */
            void reset();

            /**
             * @brief Read register via SPI
             *
             * @param [in] address
             *      register address
             *
             * @param [out] data[]
             *      read data buffer
             *
             * @param [in] length
             *      read byte length
             *      - **1** 1byte
             *      - **2** 2byte
             *
             * @attention length should be 1 or 2
             */
            void read(Address address, uint8_t data[], size_t length);

            /**
             * @brief Write register via SPI
             *
             * @param [in] address
             *      register address
             *
             * @param [in] data[]
             *      write data
             *
             * @param [in] length
             *      write byte length
             *      - **1** 1byte
             *      - **2** 2byte
             *
             * @attention length should be 1 or 2
             */
            void write(Address address, uint8_t data[], size_t length);

            /**
             * @brief Get ADC conversion data
             *
             * Execute SingleConversion and read ADCDATA register.
             *
             * @param [in] *adcdata
             *      read data buffer
             *
             * @param [in] chop
             *      system chop mode
             *      - **false** System Chop is disable [default]
             *      - **true**  System Chop is enable
             */
            void get_adcdata(int16_t *adcdata, bool chop = false);

        private:
            SPI *_spi;
    };
}

/**
 * @defgroup REGISTER Register Values
 * @{
 */

/**
 * @defgroup CTRL_REG CTRL
 * @{
 */

/**
 * @name MODE[3:0]
 * @{
 */
#define CTRL_MODE_IDLE                        0x0
#define CTRL_MODE_SINGLE_CONVERSION           0x2
#define CTRL_MODE_CONTINUOUS_CONVERSION       0x3
#define CTRL_MODE_SINGLE_CHOP_CONVERSION      0x4
#define CTRL_MODE_CONTINUOUS_CHOP_CONVERSION  0x5
#define CTRL_MODE_INTERNAL_OFFSET_CALIBRATION 0x8
#define CTRL_MODE_INTERNAL_GAIN_CALIBRATION   0x9
#define CTRL_MODE_PGA_OFFSET_CALIBRATION      0xA
#define CTRL_MODE_SYSTEM_OFFSET_CALIBRATION   0xC
#define CTRL_MODE_SYSTEM_GAIN_CALIBRATION     0xD
#define CTRL_MODE_BOOT                        0xF
/* @} MODE[3:0] */

/**
 * @name CHSEL[5:4]
 * @{
 */
#define CTRL_CHSEL_INP_INN  (0x0 << 4)
#define CTRL_CHSEL_INP_GND  (0x2 << 4)
#define CTRL_CHSEL_INN_GND  (0x3 << 4)
#define CTRL_CHSEL_VREF_GND (0x4 << 4)
#define CTRL_CHSEL_GND_GND  (0x5 << 4)
#define CTRL_CHSEL_INN_INN  (0x6 << 4)
/* @} CHSEL[5:4] */

/**
 * @name OV[6]
 * @{
 */
#define CTRL_OV_NOERROR  (0x0 << 6)
#define CTRL_OV_OVERFLOW (0x1 << 6)
/* @} OV[6] */

/**
 * @name RDYB[7]
 * @{
 */
#define CTRL_RDYB_READY (0x0 << 7)
#define CTRL_RDYB_BUSY  (0x1 << 7)
/* @} RDYB[7] */

/* @} CTRL_REG */

/**
 * @defgroup PGACONF_REG PGACONF
 * @{
 */

/**
 * @name PGA1GAIN[2:0]
 * @{
 */
#define PGACONF_PGA1GAIN_X1   0x0
#define PGACONF_PGA1GAIN_X2   0x1
#define PGACONF_PGA1GAIN_X4   0x2
#define PGACONF_PGA1GAIN_X8   0x3
#define PGACONF_PGA1GAIN_X16  0x4
#define PGACONF_PGA1GAIN_X32  0x5
#define PGACONF_PGA1GAIN_X64  0x6
#define PGACONF_PGA1GAIN_X128 0x7
/* @} PGA1GAIN[2:0] */

/**
 * @name PGA1EN[3]
 * @{
 */
#define PGACONF_PGA1EN_DISABLE (0x0 << 3)
#define PGACONF_PGA1EN_ENABLE  (0x1 << 3)
/* @} PGA1EN[3] */

/**
 * @name PGA2GAIN[5:4]
 * @{
 */
#define PGACONF_PGA2GAIN_X1   (0x0 << 4)
#define PGACONF_PGA2GAIN_X2   (0x1 << 4)
#define PGACONF_PGA2GAIN_X4   (0x2 << 4)
/* @} PGA2GAIN[5:4] */

/* @} PGACONF_REG */

/**
 * @defgroup CLKCONF_REG CLKCONF
 * @{
 */

/**
 * @name OSR[2:0]
 * @{
 */
#define CLKCONF_OSR_64  0x0
#define CLKCONF_OSR_128 0x1
#define CLKCONF_OSR_256 0x2
#define CLKCONF_OSR_512 0x3
/* @} OSR[2:0] */

/**
 * @name CLKDIV[5:4]
 * @{
 */
#define CLKCONF_CLKDIV_FOSC_2  (0x0 << 4)
#define CLKCONF_CLKDIV_FOSC_4  (0x1 << 4)
#define CLKCONF_CLKDIV_FOSC_8  (0x2 << 4)
#define CLKCONF_CLKDIV_FOSC_16 (0x3 << 4)
/* @} CLKDIV[5:4] */

/* @} CLKCONF_REG */

/**
 * @defgroup DACCONF_REG DACCONF
 * @{
 */

/**
 * @name CALDAC[4:0]
 * @{
 */
#define DACCONF_CALDAC_M16 0x10
#define DACCONF_CALDAC_M15 0x11
#define DACCONF_CALDAC_M14 0x12
#define DACCONF_CALDAC_M13 0x13
#define DACCONF_CALDAC_M12 0x14
#define DACCONF_CALDAC_M11 0x15
#define DACCONF_CALDAC_M10 0x16
#define DACCONF_CALDAC_M9  0x17
#define DACCONF_CALDAC_M8  0x18
#define DACCONF_CALDAC_M7  0x19
#define DACCONF_CALDAC_M6  0x1A
#define DACCONF_CALDAC_M5  0x1B
#define DACCONF_CALDAC_M4  0x1C
#define DACCONF_CALDAC_M3  0x1D
#define DACCONF_CALDAC_M2  0x1E
#define DACCONF_CALDAC_M1  0x1F
#define DACCONF_CALDAC_0   0x00
#define DACCONF_CALDAC_1   0x01
#define DACCONF_CALDAC_2   0x02
#define DACCONF_CALDAC_3   0x03
#define DACCONF_CALDAC_4   0x04
#define DACCONF_CALDAC_5   0x05
#define DACCONF_CALDAC_6   0x06
#define DACCONF_CALDAC_7   0x07
#define DACCONF_CALDAC_8   0x08
#define DACCONF_CALDAC_9   0x09
#define DACCONF_CALDAC_10  0x0A
#define DACCONF_CALDAC_11  0x0B
#define DACCONF_CALDAC_12  0x0C
#define DACCONF_CALDAC_13  0x0D
#define DACCONF_CALDAC_14  0x0E
#define DACCONF_CALDAC_15  0x0F
/* @} CALDAC[4:0] */

/**
 * @name CALDACEN[5]
 * @{
 */
#define DACCONF_CALDACEN_DISABLE (0x0 << 5)
#define DACCONF_CALDACEN_ENABLE  (0x1 << 5)
/* @} CALDACEN[5] */

/* @} DACCONF_REG */

/* @} REGISTER */

#endif // __NJU9103_H__
