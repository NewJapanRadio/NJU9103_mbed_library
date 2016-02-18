#include "mbed.h"

#include "NJU9103/NJU9103.h"

using namespace NewJapanRadio;

Serial serial(USBTX, USBRX);
NJU9103 nju9103;

int main() {
    nju9103.reset();

    serial.baud(9600);
    serial.format(8, Serial::None, 1);

    int16_t adcdata;
    uint8_t wd[2] = { 0x00, 0x00 };

    // CALDACEN:ON, CALDAC:-15
    wd[0] = (1 << 5) | (-16 & 0x1F);
    nju9103.write(NJU9103::DACCONF, wd, 1);
    // PGA1EN:ON, PGA1GAIN:32;
    wd[0] = (1 << 4) | 5;
    nju9103.write(NJU9103::PGACONF, wd, 1);

    serial.printf("Run NJU9103\n");
    for (;;) {
        nju9103.get_adcdata(&adcdata);
        serial.printf("%d\n", adcdata);
        wait(1);
    }
}
