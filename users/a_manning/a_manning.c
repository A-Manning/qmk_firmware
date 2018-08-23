#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// TODO: Put stuff here

void tap_key(uint16_t kc) {
    register_code(kc);
    unregister_code(kc);
}

// kc1 + kc2
void kc1_kc2(uint16_t kc1, uint16_t kc2) {
    register_code(kc1);
    tap_key(kc2);
    unregister_code(kc1);
}

// shift + kc
void shift_kc(uint16_t kc) { kc1_kc2(KC_LSFT, kc); }

// kc1 + kc2 on tap
void t_kc1_kc2( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 )
    { if (state->count > 1) { kc1_kc2(kc1, kc2); } }

// registers kc1 + kc2
void reg_kc1_kc2( uint16_t kc1, uint16_t kc2 ) {
    register_code(kc1);
    register_code(kc2);
}

// unregisters kc2, then kc1
void unreg_kc1_kc2( uint16_t kc1, uint16_t kc2 ) {
    unregister_code(kc2);
    unregister_code(kc1);
}

// kc1 + kc2 on tap, kc3 on hold
void t_kc1_kc2_h_kc3( qk_tap_dance_state_t *state,
                      uint16_t kc1,
                      uint16_t kc2,
                      uint16_t kc3 ) {
    if (state->pressed) {
        register_code(kc3);
    } else {
        kc1_kc2(kc1, kc2);
    }
}

// kc1 on tap, kc2 + kc3 on hold
void t_kc1_h_kc2_kc3( qk_tap_dance_state_t *state,
                      uint16_t kc1,
                      uint16_t kc2,
                      uint16_t kc3 ) {
    if (state->pressed) {
        reg_kc1_kc2(kc2, kc3);
    } else {
        tap_key(kc1);
    }
}

// kc1 + kc2 on tap, kc3 + kc4 on hold
void t_kc1_kc2_h_kc3_kc4( qk_tap_dance_state_t *state,
                          uint16_t kc1,
                          uint16_t kc2,
                          uint16_t kc3,
                          uint16_t kc4 ) {
    if (state->pressed) {
        reg_kc1_kc2(kc3, kc4);
    } else {
        kc1_kc2(kc1, kc2);
    }
}

void td_layer_kc1_kc2_tap
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->count > 1) {
        register_code(kc1);
        tap_key(kc2);
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
        tap_key(kc2);
        unregister_code(kc1);
    }
}
void td_layer_kc1_kc2_reset
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    layer_off(layer);
}
