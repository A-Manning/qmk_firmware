#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// TODO: Put stuff here

void reg(uint16_t kc) { register_code(kc); }
void unreg(uint16_t kc) { unregister_code(kc); }
// registers kc1 + kc2
void reg2( uint16_t kc1, uint16_t kc2 ) {
    reg(kc1);
    reg(kc2);
}
// unregisters kc2, then kc1
void unreg2( uint16_t kc1, uint16_t kc2 ) {
    unreg(kc2);
    unreg(kc1);
}

void tap(uint16_t kc) {
    reg(kc);
    unreg(kc);
}

// kc1 + kc2
void tap2(uint16_t kc1, uint16_t kc2) {
    reg(kc1);
    tap(kc2);
    unreg(kc1);
}

// shift + kc
void sh(uint16_t kc) { tap2(KC_LSFT, kc); }

// kc1 + kc2 on tap
void tk2( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 )
    { if (state->count > 1) { tap2(kc1, kc2); } }

// kc1 + kc2 on tap, kc3 on hold
void tk2_hk ( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint16_t kc3 ) {
    if (state->pressed) {
        reg(kc3);
    } else {
        tap2(kc1, kc2);
    }
}

// kc1 + kc2 on tap, l on hold
void tk2_hl ( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint8_t  l ) {
    if (state->pressed) {
        layer_on(l);
    } else {
        tap2(kc1, kc2);
    }
}

// kc1 on tap, kc2 + kc3 on hold
void tk_hk2( qk_tap_dance_state_t *state,
             uint16_t kc1,
             uint16_t kc2,
             uint16_t kc3 ) {
    if (state->pressed) {
        reg2(kc2, kc3);
    } else {
        tap(kc1);
    }
}

// kc1 + kc2 on tap, kc3 + kc4 on hold
void tk2_hk2( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint16_t kc3,
              uint16_t kc4 ) {
    if (state->pressed) {
        reg2(kc3, kc4);
    } else {
        tap2(kc1, kc2);
    }
}

// reset 1 key
void rs(uint16_t kc1){
    unreg(kc1);
}
// reset 2 keys
void rs2(uint16_t kc1, uint16_t kc2){
    unreg2(kc1, kc2);
}
// resets layer
void rsl(uint8_t l){
    layer_off(l);
}

void td_layer_kc1_kc2_tap
    (qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2) {
    if (state->count > 1) {
        tap2(kc1, kc2);
    }
}
// moves to layer while held, otherwise sends kc2 with kc1 held down.
void td_layer_kc1_kc2_finished
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2) {
    if (state->pressed) {
        layer_on(layer);
    } else {
        tap2(kc1, kc2);
    }
}
void td_layer_kc1_kc2_reset(uint8_t layer) {
    layer_off(layer);
}
