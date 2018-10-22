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

//////////////
// tap actions
//////////////

// kc on tap
void tk( qk_tap_dance_state_t *state, uint16_t kc );
// kc1 + kc2 on tap
void tk2( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 );

///////////////
// hold actions
///////////////

// kc1 on tap, kc2 on hold
void tk_hk ( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 );

// kc on tap, l on hold
void tk_hl ( qk_tap_dance_state_t *state, uint16_t kc, uint8_t l );

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

////////////////
// reset actions
////////////////

// reset 1 key
void rs(uint16_t kc1);
// reset 2 keys
void rs2(uint16_t kc1, uint16_t kc2);
// resets layer
void rsl(uint8_t l);

// declaring a tap dance
#define TDFN(name) ACTION_TAP_DANCE_FN_ADVANCED(td_tap_##name, td_fin_##name, td_rst_##name)

////////////////////////////////////////////////////////////
// defining `td_tap_##name`, `td_fin_##name`, `td_rst_#name`
////////////////////////////////////////////////////////////


// kc1 on tap, kc2 on hold.
#define TDTKHK(name, kc1, kc2) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tk(state, kc1);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tk_hk(state, kc1, kc2);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {rs(kc2);};

// kc on tap, l on hold.
#define TDTKHL(name, kc, l) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tk(state, kc);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tk_hl(state, kc, l);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {rsl(l);};

// kc1 + kc2 on tap, kc3 on hold.
#define TDTK2HK(name, kc1, kc2, kc3) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tk2(state, kc1, kc2);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tk2_hk(state, kc1, kc2, kc3);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {rs(kc3);};

// kc1 + kc2 on tap, l on hold.
#define TDTK2HL(name, kc1, kc2, l) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tk2(state, kc1, kc2);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tk2_hl(state, kc1, kc2, l);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {rsl(l);};
