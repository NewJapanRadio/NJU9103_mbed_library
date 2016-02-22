#include "NJU9103.h"

using namespace NewJapanRadio;

NJU9103::NJU9103() {
    this->_spi = new SPI(SPI_MOSI, SPI_MISO, SPI_SCK);
    this->_spi->format(8, 1);
    this->_spi->frequency(10E6);
}

NJU9103::~NJU9103() {
    delete this->_spi;
}

void NJU9103::reset() {
    this->_spi->write(0x7F);
    this->_spi->write(0xFF);
    this->_spi->write(0xFF);
}

void NJU9103::read(Address address, uint8_t data[], size_t length) {
    uint8_t rw = 1;
    uint8_t bc = (length - 1);
    uint8_t spicmd = uint8_t(((rw << 1) + bc) << 2);
    this->_spi->write((uint8_t)(address << 4) + spicmd);
    for (int i = 0; i < (int)length; i++) {
        data[i] = this->_spi->write(0x00);
    }
}

void NJU9103::write(Address address, uint8_t data[], size_t length) {
    uint8_t rw = 0;
    uint8_t bc = (length - 1);
    uint8_t spicmd = uint8_t(((rw << 1) + bc) << 2);

    this->_spi->write((uint8_t)(address << 4) + spicmd);
    for (int i = 0; i < (int)length; i++) {
        this->_spi->write(data[i]);
    }
}

void NJU9103::get_adcdata(int16_t *adcdata, bool chop) {
    uint8_t rd[2] = { 0x00, 0x00 };
    // wait for boot
    this->read(NJU9103::CTRL, rd, 1);
    while ((rd[0] & 0x0F) == CTRL_MODE_BOOT) {
        this->read(NJU9103::CTRL, rd, 1);
    }

    // CHSEL:INP/INN, MODE:Single Conversion
    uint8_t mode;
    if (chop) {
        mode = CTRL_MODE_SINGLE_CHOP_CONVERSION;
    }
    else
    {
        mode = CTRL_MODE_SINGLE_CONVERSION;
    }
    uint8_t wd = CTRL_CHSEL_INP_INN | mode;
    this->write(NJU9103::CTRL, &wd, 1);

    // wait for end of conversion
    this->read(NJU9103::CTRL, rd, 1);
    while ((rd[0] & 0x80) == CTRL_RDYB_BUSY) {
        this->read(NJU9103::CTRL, rd, 1);
    }

    // read ADCDATA
    this->read(NJU9103::ADCDATA0, rd, 2);
    *adcdata = int16_t((rd[0] << 8) | rd[1]);
}
