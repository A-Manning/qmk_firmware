#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

void reg(uint16_t kc);
void unreg(uint16_t kc);
// registers kc1 + kc2
void reg2( uint16_t kc1, uint16_t kc2 );
// unregisters kc2, then kc1
void unreg2( uint16_t kc1, uint16_t kc2 );
void tap(uint16_t kc);
// kc1 + kc2
void tap2(uint16_t kc1, uint16_t kc2);
// shift + kc
void sh(uint16_t kc);
// kc1 + kc2 on tap
void tk2( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 );

// kc1 + kc2 on tap, kc3 on hold
void tk2_hk ( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint16_t kc3 );

// kc1 + kc2 on tap, l on hold
void tk2_hl ( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint8_t  l );

// kc1 on tap, kc2 + kc3 on hold
void tk_hk2( qk_tap_dance_state_t *state,
             uint16_t kc1,
             uint16_t kc2,
             uint16_t kc3 );

// kc1 + kc2 on tap, kc3 + kc4 on hold
void tk2_hk2( qk_tap_dance_state_t *state,
              uint16_t kc1,
              uint16_t kc2,
              uint16_t kc3,
              uint16_t kc4 );

// reset 1 key
void rs(uint16_t kc1);
// reset 2 keys
void rs2(uint16_t kc1, uint16_t kc2);
// resets layer
void rsl(uint8_t l);
