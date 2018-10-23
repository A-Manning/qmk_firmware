#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

//////////////
// tap actions
//////////////

// taps kc with mods on tap
void tmk( qk_tap_dance_state_t *state, uint8_t mods, uint16_t kc );

///////////////
// hold actions
///////////////

// taps kc1 with mods1 on tap, taps kc2 with mods2 on hold.
void tmk_tmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint16_t kc1,
              uint8_t mods2,
              uint16_t kc2 );

// declaring a tap dance
#define TDFN(name) ACTION_TAP_DANCE_FN_ADVANCED(td_tap_##name, td_fin_##name, td_rst_##name)

////////////////////////////////////////////////////////////
// defining `td_tap_##name`, `td_fin_##name`, `td_rst_#name`
////////////////////////////////////////////////////////////

// taps kc1 with mods1 on tap, taps kc2 with mods2 on hold
#define TDTMKTMK(name, mods1, kc1, mods2, kc2) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tmk(state, mods1, kc1);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tmk_tmk(state, mods1, kc1, mods2, kc2);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {};

// taps kc1 with mods on tap, taps kc2 on hold
#define TDTMKTK(name, mods, kc1, kc2) TDTMKTMK(name, mods, kc1, 0x00, kc2)

// taps kc1 on tap, taps kc2 with mods on hold
#define TDTKTMK(name, kc1, mods, kc2) TDTMKTMK(name, 0x00, kc1, mods, kc2)

// kc1 on tap, taps kc2 on hold.
#define TDTKTK(name, kc1, kc2) TDTMKTMK(name, 0x00, kc1, 0x00, kc2)

// taps kc1 with shift on tap, taps kc2 with shift on hold
#define TDTSHKTSHK(name, kc1, kc2) TDTMKTMK(name, MOD_LSFT, kc1, MOD_LSFT, kc2)

// taps kc1 with shift on tap, taps kc2 on hold
#define TDTSHKTK(name, kc1, kc2) TDTMKTMK(name, MOD_LSFT, kc1, 0x00, kc2)

// taps kc1 on tap, taps kc2 with shift on hold
#define TDTKTSHK(name, kc1, kc2) TDTMKTMK(name, 0x00, kc1, MOD_LSFT, kc2)
