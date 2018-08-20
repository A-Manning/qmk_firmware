#include "a_manning.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

/*
//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};
​
void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_X); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}
​
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}
​
qk_tap_dance_action_t tap_dance_actions[] = {
  [X_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
*/

//instanalize an instance of 'tap' for the '(' tap dance.
static tap l_shf_tap_state = {
  .is_press_action = true,
  .state = 0
};

void l_shf_finished (qk_tap_dance_state_t *state, void *user_data) {
  l_shf_tap_state.state = cur_dance(state);
  switch (l_shf_tap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_COMM); break;
    case DOUBLE_HOLD: register_code(KC_CAPS); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); unregister_code(KC_9); register_code(KC_9);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void l_shf_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (l_shf_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_9); unregister_code(KC_LSFT); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_COMM); unregister_code(KC_LSFT); break;
    case DOUBLE_HOLD: unregister_code(KC_CAPS);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_9); unregister_code(KC_LSFT);
  }
  l_shf_tap_state.state = 0;
}

//instanalize an instance of 'tap' for the ')' tap dance.
static tap r_shf_tap_state = {
  .is_press_action = true,
  .state = 0
};

void r_shf_finished (qk_tap_dance_state_t *state, void *user_data) {
  r_shf_tap_state.state = cur_dance(state);
  switch (r_shf_tap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_DOT); break;
    case DOUBLE_HOLD: register_code(KC_CAPS); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); unregister_code(KC_0); register_code(KC_0);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void r_shf_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (r_shf_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_0); unregister_code(KC_LSFT); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_DOT); unregister_code(KC_LSFT); break;
    case DOUBLE_HOLD: unregister_code(KC_CAPS);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_0); unregister_code(KC_LSFT);
  }
  r_shf_tap_state.state = 0;
}

//instanalize an instance of 'tap' for the mod tap dance.
static tap mod_tap_state = {
  .is_press_action = true,
  .state = 0
};

void mod_finished (qk_tap_dance_state_t *state, void *user_data) {
  mod_tap_state.state = cur_dance(state);
  switch (mod_tap_state.state) {
    case SINGLE_TAP: set_oneshot_mods(MOD_LALT); break;
    case SINGLE_HOLD: break;
    case DOUBLE_TAP: set_oneshot_mods(MOD_LGUI);
  }
}

void mod_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mod_tap_state.state) {
    case SINGLE_TAP: clear_oneshot_mods();
                     set_oneshot_locked_mods(MOD_LALT);
                     register_mods(MOD_LALT);
                     break;
    case SINGLE_HOLD: break;
    case DOUBLE_TAP: clear_oneshot_mods();
                     set_oneshot_locked_mods(MOD_LGUI);
                     register_mods(MOD_LGUI);
  }
  mod_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LSFT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,l_shf_finished, l_shf_reset),
  [RSFT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,r_shf_finished, r_shf_reset),
  [MOD ]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,mod_finished, mod_reset)
};
