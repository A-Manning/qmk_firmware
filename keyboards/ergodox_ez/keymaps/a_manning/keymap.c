#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "a_manning.h"

#define BASE 0 // default layer
#define SBASE 1 // shifted base layer
#define FN1 2 // function layer

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// Tap Dance Declarations
enum {
    LSFT = 0, // Left space-cadet shift
    LBRC,
    RBRC,
    QUOT,
    COMM,
    DOT,
    SLSH,
    RSFT,
};

// left space-cadet
TDTKHL(lsft, KC_BSLS, SBASE)
// right space-cadet
TDTKHL(rsft, KC_SLSH, SBASE)
// { [
TDTK2TK(lbrc, KC_LSFT, KC_LBRC, KC_LBRC)
// } ]
TDTK2TK(rbrc, KC_LSFT, KC_RBRC, KC_RBRC)
// ' "
TDTKTK2(quot, KC_QUOT, KC_LSFT, KC_QUOT)
// , ;
TDTKTK(comm, KC_COMM, KC_SCLN)
// . :
TDTKTK2(dot, KC_DOT, KC_LSFT, KC_SCLN)
// / ?
TDTKTK2(slsh, KC_SLSH, KC_LSFT, KC_SLSH)



// Tap Dance Definitions
// Can be used as // TD(TD_IDENT)
qk_tap_dance_action_t tap_dance_actions[] = {
    [LSFT] = TDFN(lsft),
    [LBRC] = TDFN(lbrc),
    [RBRC] = TDFN(rbrc),
    [QUOT] = TDFN(quot),
    [COMM] = TDFN(comm),
    [DOT]  = TDFN(dot),
    [SLSH] = TDFN(slsh),
    [RSFT] = TDFN(rsft)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    `   |   q  |   w  |   e  |   r  |   t  |  {   |           |   }  |   y  |   u  |   i  |   o  |   p  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | tab FN |   a  |   s  |   d  |   f  |   g  |------|           |------|   h  |   j  |   k  |   l  |   '  |   =    |
 * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
 * |   UP   |   z  |   x  |   c  |   v  |   b  |      |           |      |   n  |   m  |   ,  |   .  |   /  |   UP   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | FN   |      |      | win  | alt  |                                       |      |      |      |      | ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space| bspc |------|       |------|  bspc  |  ent |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,          KC_1,  KC_2,  KC_3,    KC_4,    KC_5,    KC_NO,
        KC_GRV,          KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,    TD(LBRC),
        LT(FN1, KC_TAB), KC_A,  KC_S,  KC_D,    KC_F,    KC_G,
        TD(LSFT),        KC_Z,  KC_X,  KC_C,    KC_V,    KC_B,    S(KC_9),
        OSM(MOD_LCTL),   KC_NO, KC_NO, KC_LWIN, KC_LALT,
                                                         KC_NO,   KC_NO,
                                                                  KC_NO,
                                                KC_SPC,  KC_BSPC, KC_LALT,
        // right hand
        KC_NO,    KC_6,    KC_7,  KC_8,     KC_9,    KC_0,     KC_NO,
        TD(RBRC), KC_Y,    KC_U,  KC_I,     KC_O,    KC_P,     KC_MINS,
                  KC_H,    KC_J,  KC_K,     KC_L,    TD(QUOT), KC_EQL,
        S(KC_0),  KC_N,    KC_M,  TD(COMM), TD(DOT), TD(SLSH), TD(RSFT),
                           KC_NO, KC_NO,    KC_NO,   KC_NO,    KC_RCTL,

        KC_NO,    KC_NO,
        KC_NO,
        KC_RALT,  KC_BSPC, KC_ENT

    ),

/* Keymap 1: Shifted base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ls+ESC |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |  <   |   >  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    ~   |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   |    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ls+Tab |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   "  |   _    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ;  |   :  |   ?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | ls+  | Del  |      |       |      |  Del   | ls+  |
 *                                 | spc  |      |------|       |------|        | end  |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// Shifted base layer
[SBASE] = LAYOUT_ergodox(
       // left hand
       S(KC_ESC), S(KC_1), S(KC_2), S(KC_3), S(KC_4),   S(KC_5), KC_NO,
       S(KC_GRV), S(KC_Q), S(KC_W), S(KC_E), S(KC_R),   S(KC_T), KC_LBRC,
       S(KC_TAB), S(KC_A), S(KC_S), S(KC_D), S(KC_F),   S(KC_G),
       KC_TRNS,   S(KC_Z), S(KC_X), S(KC_C), S(KC_V),   S(KC_B), KC_NO,
       KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                        KC_NO,   KC_NO,
                                                                 KC_NO,
                                             S(KC_SPC), KC_DEL,  KC_NO,
       // right hand
       KC_NO,   S(KC_6), S(KC_7), S(KC_8), S(KC_COMM), S(KC_DOT),  KC_NO,
       KC_RBRC, S(KC_Y), S(KC_U), S(KC_I), S(KC_O),    S(KC_P),    S(KC_BSLS),
                S(KC_H), S(KC_J), S(KC_K), S(KC_L),    S(KC_QUOT), S(KC_MINS),
       KC_NO,   S(KC_N), S(KC_M), KC_SCLN, S(KC_SCLN), S(KC_SLSH), KC_NO,
                           KC_NO, KC_NO,   KC_NO,      KC_NO,      KC_NO,

       KC_NO,   KC_NO,
       KC_NO,
       KC_NO,   KC_DEL,  S(KC_ENT)
),
/* Keymap 2: Function keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  | F2   |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | pgup | home |  up  | end  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| pgdn | left | down | rght |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   LSH  |      |      |      |      |      |      |           |      |      |  [   |  ]   |  {   |  }   |  RSH   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|  del |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Function layer 1
[FN1] = LAYOUT_ergodox(
       KC_NO,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO,
                                                   KC_NO,
                                     KC_NO, KC_NO, KC_NO,
    // right hand
       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,     KC_NO,
       KC_NO,  KC_PGUP, KC_HOME, KC_UP,   KC_END,     KC_NO,      KC_NO,
               KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,    KC_NO,      KC_NO,
       KC_NO,  KC_NO,   KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), KC_RSFT,
                        KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,
       KC_NO,  KC_NO,
       KC_NO,
       KC_NO,  KC_DEL,  KC_NO
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(FN1)                // FN1 - Momentary Layer 1 (Upper)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
