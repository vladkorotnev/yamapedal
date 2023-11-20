#ifndef BUTTON_H_
#define BUTTON_H_

typedef enum switch_id {
    SW_REV,
    SW_MOD,
    SW_EQ,
    SW_DIST,
    SW_COMP,
    SW_PGM_EFFECT
} switch_id_t;

void button_begin();
void button_tick();

bool button_read(switch_id_t button);
bool button_read_masked(switch_id_t button);
bool button_is_changed(switch_id_t button);


#endif // BUTTON_H_