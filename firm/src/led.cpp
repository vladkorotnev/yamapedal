#include <led.h>
#include <Arduino.h>
#include <hw.h>

void led_begin() {
    for(int i = LED_PIN_START; i < LED_PIN_START + LED_PIN_COUNT; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, 0);
    }
}

void led_set(led_id_t id, bool light) {
    digitalWrite(LED_PIN_START + (uint8_t) id, light ? 1 : 0);
}