#include <log.h>
#include <midiif.h>
#include <settings.h>
#include <util.h>
#include <led.h>
#include <button.h>

extern "C" {
  void setup();
  void loop();
}

void boot_anim() {
  for(int ctr = 0; ctr < 2; ctr++) {
    for(int i = 0; i < 7; i++) {
      if(i > 0) led_set((led_id_t) (i - 1), false);
      led_set((led_id_t)i, true);
      delay(66);
    }
    for(int i = 5; i >= 0; i--) {
      led_set((led_id_t) (i + 1), false);
      led_set((led_id_t)i, true);
      delay(66);
    }
    led_set((led_id_t)0, false);
  }
}

static bool main_channel = true;
const int main_channel_number = 0;
const int sub_channel_number = 1;
const int note_data[] = {
  // Note numbers
  48, 49, 50, 51, 52, 53
};

void setup() {
  // Bootstrap
  log_begin();
  inf_log(F("Starting SAS-DOS..."));


  // Set up software
  cfg_begin();
  midi_begin();

  // Set up hardware
  button_begin();
  led_begin();

  // Let things settle
  button_tick();
  boot_anim();
  
  led_set(led_id_t::LED_PGM, main_channel);
  led_set(led_id_t::LED_EFFECT, !main_channel);
}


void loop() {
  button_tick();

  if(button_read_masked(switch_id_t::SW_PGM_EFFECT)) {
    main_channel = !main_channel;
    led_set(led_id_t::LED_PGM, main_channel);
    led_set(led_id_t::LED_EFFECT, !main_channel);
  }

  for(int i = 0; i < 5; i++) {
    bool val = button_read((switch_id_t) i);

    if(button_is_changed((switch_id_t) i)) {
      led_set((led_id_t) (LED_REV - i), val);
      midi_note(main_channel ? main_channel_number : sub_channel_number, note_data[i], val ? 64 : 0);
    }    
  }
}
