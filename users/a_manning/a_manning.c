#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// TODO: Put stuff here


void tapKey(uint16_t kc) {
    register_code(kc);
    unregister_code(kc);
}

// sends
void td_layer_kc1_kc2_tap
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->count > 1) {
        register_code(kc1);
        tapKey(kc2);
        unregister_code(kc1);
    }

}
// moves to layer while held, otherwise sends kc2 with kc1 held down.
void td_layer_kc1_kc2_finished
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->pressed) {
        layer_on(layer);
    } else {
        register_code(kc1);
        tapKey(kc2);
        unregister_code(kc1);
    }
}

void td_layer_kc1_kc2_reset
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    
    layer_off(layer);
}
