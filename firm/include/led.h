#ifndef LED_H_
#define LED_H_

typedef enum led_id {
    LED_PGM,
    LED_EFFECT,

    LED_COMP,
    LED_DIST,
    LED_EQ,
    LED_MOD,
    LED_REV
} led_id_t;

void led_begin();
void led_set(led_id_t id, bool light);

#endif