#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

// moves to layer while held, otherwise sends kc2 with kc1 held down.
void td_layer_kc1_kc2_finished
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2);
// unsets layer if held, otherwise releases kc2 and then kc1.
void td_layer_kc1_kc2_reset
    (qk_tap_dance_state_t *state, uint8_t layer, uint16_t kc1, uint16_t kc2);
