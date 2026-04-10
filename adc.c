#include <avr/io.h>

void ADC_Init() {
    // Set reference voltage to AVCC (5V) and select Channel 0
    ADMUX = (1 << REFS0);
    // Enable ADC and set prescaler to 128 (16MHz/128 = 125kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select channel
    ADCSRA |= (1 << ADSC);                     // Start conversion
    while (ADCSRA & (1 << ADSC));              // Wait for completion
    return ADC;                                // Return 10-bit result
}

int main() {
    ADC_Init();
    while(1) {
        uint16_t value = ADC_Read(0);
    }
}
