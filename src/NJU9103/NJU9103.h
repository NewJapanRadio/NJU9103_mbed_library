#ifndef __NJU9103_H__
#define __NJU9103_H__

#include <mbed.h>

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

#endif // __NJU9103_H__
