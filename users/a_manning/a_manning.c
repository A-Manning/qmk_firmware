#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// taps kc with mods
void tapm(uint8_t mods, uint16_t kc) {
    add_mods(mods);
    register_code(kc);
    unregister_code(kc);
    del_mods(mods);
}

// taps kc
void tap(uint16_t kc) { tapm(0x00, kc); }

//////////////
// tap actions
//////////////

// taps kc with mods on tap
void tmk( qk_tap_dance_state_t *state, uint8_t mods, uint16_t kc )
    { if (state->count > 1) { tapm(mods, kc); } }

// taps kc on tap
void tk( qk_tap_dance_state_t *state, uint16_t kc )
    { tmk(state, 0x00, kc); }

///////////////
// hold actions
///////////////

// taps kc1 with mods1 on tap, taps kc2 with mods2 on hold.
void tmk_tmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint16_t kc1,
              uint8_t mods2,
              uint16_t kc2 ) {
    if (state->pressed && !state->interrupted) {
        tapm(mods2, kc2);
    } else {
        tapm(mods1, kc1);
    }
}

// taps kc1 on tap, taps kc2 on hold
void tk_tk( qk_tap_dance_state_t *state, uint16_t kc1, uint16_t kc2 ) {
    tmk_tmk(state, 0x00, kc1, 0x00, kc2);
}

// taps kc1 with mods on tap, taps kc2 on hold
void tmk_tk( qk_tap_dance_state_t *state,
             uint8_t mods,
             uint16_t kc1,
             uint16_t kc2 ) {
    tmk_tmk(state, mods, kc1, 0x00, kc2);
}

// taps kc1 on tap, taps kc2 with mods on hold
void tk_tmk( qk_tap_dance_state_t *state,
             uint16_t kc1,
             uint8_t mods,
             uint16_t kc2 ) {
    tmk_tmk(state, 0x00, kc1, mods, kc2);
}
