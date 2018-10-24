#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

//////////////
// tap actions
//////////////

// taps kc with mods on tap
void tmk( qk_tap_dance_state_t *state, uint8_t mods, uint16_t kc );

// toggles an osm on tap
void tos( qk_tap_dance_state_t *state, uint8_t mods );

///////////////
// hold actions
///////////////

// taps kc1 with mods1 on tap, taps kc2 with mods2 on hold
void tmk_tmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint16_t kc1,
              uint8_t mods2,
              uint16_t kc2 );

// taps kc1 with mods1 on tap, holds kc2 with mods2 on hold
void tmk_hmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint16_t kc1,
              uint8_t mods2,
              uint16_t kc2 );

// toggles one-shot mods1 on tap, taps kc with mods2 on hold
void tos_tmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint8_t mods2,
              uint16_t kc );

////////////////
// reset actions
////////////////

// reset kc and mods
void rst_mk(uint8_t mods, uint16_t kc);

////////////////////////
// declaring a tap dance
////////////////////////

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

// toggles one-shot mods1 on tap, taps kc with mods2 on hold
#define TDTOSTMK(name, mods1, mods2, kc) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tos(state, mods1);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tos_tmk(state, mods1, mods2, kc);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {};

// toggles one-shot mods on tap, taps kc on hold
#define TDTOSTK(name, mods, kc) TDTOSTMK(name, mods, 0x00, kc)

// taps kc1 with mods1 on tap, holds kc2 with mods2 on hold
#define TDTMKHMK(name, mods1, kc1, mods2, kc2) \
    void td_tap_##name (qk_tap_dance_state_t *state, void *user_data) {tmk(state, mods1, kc1);}; \
    void td_fin_##name (qk_tap_dance_state_t *state, void *user_data) {tmk_hmk(state, mods1, kc1, mods2, kc2);}; \
    void td_rst_##name (qk_tap_dance_state_t *state, void *user_data) {rst_mk(mods2, kc2)};

// taps kc1 on tap, holds kc2 with mods on hold
#define TDTKHMK(name, kc1, mods, kc2) TDTMKHMK(name, 0x00, kc1, mods, kc2)

// taps kc on tap, holds mods on hold
#define TDTKHM(name, kc, mods) TDTMKHMK(name, 0x00, kc, mods, 0x00)

// taps kc1 on tap, holds kc2 on hold
#define TDTKHK(name, kc1, kc2) TDTMKHMK(name, 0x00, kc1, 0x00, kc2)

// taps kc with mods1 on tap, holds mods2 on hold
#define TDTMKHM(name, mods1, kc, mods2) TDTMKHMK(name, mods1, kc, mods2, 0x00)

// taps kc1 with mods on tap, holds kc2 on hold
#define TDTMKHK(name, mods, kc1, kc2) TDTMKHMK(name, mods, kc1, 0x00, kc2)
