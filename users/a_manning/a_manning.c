#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// TODO: Put stuff here

// moves to layer while held, otherwise sends kc2 with kc1 held down.
void td_layer_kc1_kc2_finished
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->interrupted || !state->pressed) {
        register_code(kc1);
        register_code(kc2);
    } else {
        layer_on(layer);
    }
}

void td_layer_kc1_kc2_reset
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->interrupted || !state->pressed) {
        unregister_code(kc1);
        unregister_code(kc2);
    } else {
        layer_off(layer);
    }
}
