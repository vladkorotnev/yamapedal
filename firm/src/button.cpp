#include <Arduino.h>
#include <hw.h>
#include <button.h>

#define DEBOUNCE_MS 30
#define BTN_COUNT (sizeof(BTN_PINS) / sizeof(uint8_t))

static unsigned long debounce_timers[BTN_COUNT] = { 0 };
static uint8_t read_values[BTN_COUNT] = { 1 };
static uint8_t btn_states[BTN_COUNT] = { 1 };
static uint8_t btn_states_masked[BTN_COUNT] = { 1 };

void button_begin() {
  for(size_t i = 0; i < BTN_COUNT; i++) {
    pinMode(BTN_PINS[i], INPUT_PULLUP);
    digitalWrite(BTN_PINS[i], 1);
  }
}

void button_tick() {
  for(size_t i = 0; i < BTN_COUNT; i++) {
    uint8_t sts =  digitalRead(BTN_PINS[i]);
    if(sts != read_values[i]) {
        read_values[i] = sts;
        debounce_timers[i] = millis();
    }

    if((millis() - debounce_timers[i]) >= DEBOUNCE_MS) {
        btn_states[i] = read_values[i];
    }
  }
}

bool button_read(switch_id_t button) {
    // Active Low (pushed = LOW)
    uint8_t val = btn_states[(size_t)button];
    return !val;
}

bool button_read_masked(switch_id_t button) {
    bool val = button_read(button);
    if(val == btn_states_masked[(size_t) button]) {
        return false;
    }

    btn_states_masked[(size_t) button] = val;
    return val;
}

bool button_is_changed(switch_id_t button) {
    bool val = button_read(button);
    if(val == btn_states_masked[(size_t) button]) {
        return false;
    }

    btn_states_masked[(size_t) button] = val;
    return true;
}