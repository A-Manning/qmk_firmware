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

// registers an osm
void add_osm(uint8_t mods) {
    set_oneshot_mods(get_oneshot_mods() | mods);
}

// unregisters an osm
void del_osm(uint8_t mods) {
    /* we want the bits set in p, that are not set in q.
       p q (~q) (p|q) ((p|q)^q) (p&(~q))
       0 0   1    0       0        0
       0 1   0    1       0        0
       1 0   1    1       1        1
       1 1   0    1       0        0
    */
    set_oneshot_mods( get_oneshot_mods()&(~mods) );
}

// checks if an osm is set
bool osm_is_set(uint8_t mods) {
    /* if a bit is set in q, then it is also set in p.
       we take the inverse, such that a 0 bit is correct.
       p q  (p|(~q)) ((~p)&q)
       0 0     1         0
       0 1     0         1
       1 0     1         0
       1 1     1         0
    */
    return(( ( ~(get_oneshot_mods()) ) & mods ) == 0x00);
}

// toggles an osm
void tog_osm(uint8_t mods) {
    if ( osm_is_set(mods) ) {
        del_osm(mods);
    } else {
        add_osm(mods);
    }
}

//////////////
// tap actions
//////////////

// taps kc with mods on tap
void tmk( qk_tap_dance_state_t *state, uint8_t mods, uint16_t kc ) {
    if (state->count > 1) {
        tapm(mods, kc);
    }
}

// taps kc on tap
void tk( qk_tap_dance_state_t *state, uint16_t kc ) { tmk(state, 0x00, kc); }

// toggles an osm on tap
void tos( qk_tap_dance_state_t *state, uint8_t mods ) {
    if (state->count > 1) {
        tog_osm(mods);
    }
}

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

// taps kc1 with mods1 on tap, holds kc2 with mods2 on hold.
void tmk_hmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint16_t kc1,
              uint8_t mods2,
              uint16_t kc2 ) {
    if (state->pressed && !state->interrupted) {
        add_mods(mods2);
        if (kc2 != 0x00) {
            register_code(kc2);
        };
    } else {
        tapm(mods1, kc1);
    }
}

// toggles one-shot mods1 on tap, taps kc with mods2 on hold
void tos_tmk( qk_tap_dance_state_t *state,
              uint8_t mods1,
              uint8_t mods2,
              uint16_t kc ) {
    if (state->pressed && !state->interrupted) {
        tapm(mods2, kc);
    } else {
        tog_osm(mods1);
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

////////////////
// reset actions
////////////////

// reset kc and mods
void rst_mk(uint8_t mods, uint16_t kc) {
    if (kc != 0x00) {
        unregister_code(kc);
    };
    del_mods(mods);
}
