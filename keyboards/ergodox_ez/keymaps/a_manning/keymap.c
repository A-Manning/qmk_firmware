#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define UPPR 1 // upper layer
#define MOD 2 // modified keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | [/MOD  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | (/up   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |{/ctrl|      |      | win  | alt  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|      |------|       |------|  tab   |Enter |
 *                                 |      |      | win  |       | alt  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_NO,                    KC_1,  KC_2,  KC_3,    KC_4,    KC_5, KC_NO,
        KC_NO,                    KC_Q,  KC_W,  KC_E,    KC_R,    KC_T, KC_NO,
        LT(MOD, KC_LBRC),         KC_A,  KC_S,  KC_D,    KC_F,    KC_G,
        LT(UPPR, KC_9),        KC_Z,  KC_X,  KC_C,    KC_V,    KC_B, KC_NO,
        MT(MOD_LCTL, KC_LCBR),    KC_NO, KC_NO, KC_LWIN, KC_LALT,
                                                                  KC_NO, KC_NO,
                                                                         KC_NO,
                                                         KC_SPC,  KC_NO, KC_LWIN,
        // right hand
        KC_NO,   KC_6,  KC_7,  KC_8,  KC_9,  KC_0,    KC_NO,
        KC_NO,   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,    KC_NO,
                 KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_RBRC,
        KC_NO,   KC_N,  KC_M,  KC_NO, KC_NO, KC_NO,   KC_NO,
                        KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,

        KC_NO,   KC_NO,
        KC_NO,
        KC_RALT, KC_TAB, KC_ENT

    ),
/* Keymap 1: Upper layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   q  |   w  |   e  |   r  |   t  |      |           |      |   y  |   u  |   i  |   o  |   p  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | [/MOD  |   a  |   s  |   d  |   f  |   g  |------|           |------|   h  |   j  |   k  |   l  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | (/up   |   z  |   x  |   c  |   v  |   b  |      |           |      |   n  |   m  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |{/ctrl|      |      | win  | alt  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |  ls+   | ls+  |
 *                                 | bSpc |      |------|       |------|  tab   |Enter |
 *                                 |      |      | win  |       | alt  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// Upper Layer
[UPPR] = LAYOUT_ergodox(
       // left hand
       KC_NO, S(KC_1), S(KC_2),  S(KC_3), S(KC_4), S(KC_5), KC_NO,
       KC_NO, S(KC_Q), S(KC_W),  S(KC_E), S(KC_R), S(KC_T), KC_NO,
       KC_NO, S(KC_A), S(KC_S),  S(KC_D), S(KC_F), S(KC_G),
       KC_NO, S(KC_Z), S(KC_X),  S(KC_C), S(KC_V), S(KC_B), KC_NO,
       KC_NO, KC_NO,   KC_NO,    KC_NO,   KC_NO,
                                                   KC_NO,   KC_NO,
                                                            KC_NO,
                                          KC_BSPC, KC_NO,   KC_NO,
       // right hand
       KC_NO, S(KC_6),   S(KC_7),  S(KC_8), S(KC_9), S(KC_0),    KC_NO,
       KC_NO, S(KC_Y),   S(KC_U),  S(KC_I), S(KC_O), S(KC_P),    KC_NO,
              S(KC_H),   S(KC_J),  S(KC_K), S(KC_L), S(KC_SCLN), KC_NO,
       KC_NO, S(KC_N),   S(KC_M),  KC_NO,   KC_NO,   KC_NO,      KC_NO,
                         KC_NO,    KC_NO,   KC_NO,   KC_NO,      KC_NO,

       KC_NO, KC_NO,
       KC_NO,
       KC_NO, S(KC_TAB), S(KC_ENT)
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | pgup | home |  up  | end  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| pgdn | left | down | rght |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Modifier layer
[MOD] = LAYOUT_ergodox(
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                          KC_NO, KC_NO,
                                                 KC_NO,
                                   KC_NO, KC_NO, KC_NO,
    // right hand
       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
       KC_NO,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO, KC_NO,
               KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                        KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
       KC_NO,  KC_NO,
       KC_NO,
       KC_NO,  KC_NO,  KC_NO
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(UPPR)                // FN1 - Momentary Layer 1 (Upper)
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
