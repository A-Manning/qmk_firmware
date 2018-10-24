#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "a_manning.h"

#define BASE 0 // default layer
#define FN1 1 // function layer

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// Tap Dance Declarations
enum {
    ONE = 0,
    TWO,
    THREE,
    FOUR,
    FIVE,
    TILD,
    LT,
    TAB,
    LPRN,
    CTRL,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    ZERO,
    GT,
    PLUS,
    QUOT,
    EQ,
    RPRN,
    COMM,
    DOT,
    MINS,
    RET
};

// 1 !
TDTKTSHK(one, KC_1, KC_1)
// 2 @
TDTKTSHK(two, KC_2, KC_2)
// 3 #
TDTKTSHK(three, KC_3, KC_3)
// 4 $
TDTKTSHK(four, KC_4, KC_4)
// 5 %
TDTKTSHK(five, KC_5, KC_5)
// ~ `
TDTKTSHK(tild, KC_GRV, KC_GRV)
// < [
TDTSHKTK(lt, KC_COMM, KC_LBRC)
// Tab (Shift + Tab)
TDTKTSHK(tab, KC_TAB, KC_TAB)
// ( {
TDTSHKTSHK(lprn, KC_9, KC_LBRC)
// \ Ctrl
TDTOSTK(ctrl, MOD_LCTL, KC_BSLS)
// 6 ^
TDTKTSHK(six, KC_6, KC_6)
// 7 &
TDTKTSHK(seven, KC_7, KC_7)
// 8 *
TDTKTSHK(eight, KC_8, KC_8)
// 9
TDTKTSHK(nine, KC_9, KC_COPY)
// 0
TDTKTSHK(zero, KC_0, KC_PASTE)
// > ]
TDTSHKTK(gt, KC_DOT, KC_RBRC)
// + |
TDTSHKTSHK(plus, KC_EQL, KC_BSLS)
// ' "
TDTKTSHK(quot, KC_QUOT, KC_QUOT)
// = _
TDTKTSHK(eq, KC_EQL, KC_MINS)
// ) }
TDTSHKTSHK(rprn, KC_0, KC_RBRC)
// , ;
TDTKTK(comm, KC_COMM, KC_SCLN)
// . :
TDTKTSHK(dot, KC_DOT, KC_SCLN)
// - ?
TDTKTSHK(mins, KC_MINS, KC_SLSH)
// Return (Shift + Return)
TDTKTSHK(ret, KC_ENT, KC_ENT)

// Tap Dance Definitions
// Can be used as // TD(TD_IDENT)
qk_tap_dance_action_t tap_dance_actions[] = {
    [ONE]   = TDFN(one),
    [TWO]   = TDFN(two),
    [THREE] = TDFN(three),
    [FOUR]  = TDFN(four),
    [FIVE]  = TDFN(five),
    [TILD]  = TDFN(tild),
    [LT]    = TDFN(lt),
    [TAB]   = TDFN(tab),
    [MINS]  = TDFN(mins),
    [LPRN]  = TDFN(lprn),
    [CTRL]  = TDFN(ctrl),
    [SIX]   = TDFN(six),
    [SEVEN] = TDFN(seven),
    [EIGHT] = TDFN(eight),
    [NINE]  = TDFN(nine),
    [ZERO]  = TDFN(zero),
    [GT]    = TDFN(gt),
    [PLUS]  = TDFN(plus),
    [QUOT]  = TDFN(quot),
    [EQ]    = TDFN(eq),
    [RPRN]  = TDFN(rprn),
    [COMM]  = TDFN(comm),
    [DOT]   = TDFN(dot),
    [RET]   = TDFN(ret)
};

#define BTC UC(0x20BF) // ₿
#define ILS UC(0x20AA) // ₪
#define TAB_FN LT(FN1, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |  CUT   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    ~   |   q  |   w  |   e  |   r  |   t  |  <   |           |   >  |   y  |   u  |   i  |   o  |   p  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   FN   |   a  |   s  |   d  |   f  |   g  |------|           |------|   h  |   j  |   k  |   l  |   '  |   =    |
 * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
 * |        |      |   z  |   x  |   c  |   v  |      |           |      |   b  |   n  |   m  |   ,  |   .  |   -    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  \   |      |      |      |  Mod |                                       |      |      |      |      |   /  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ₪   |  ₿   |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      | Tab  |  Sup |       |      |        |      |
 *                                 | Space|      |------|       |------|  BSPC  |  Ret |
 *                                 |      | FN   |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,    TD(ONE), TD(TWO), TD(THREE), TD(FOUR), TD(FIVE), KC_CUT,
        TD(TILD),  KC_Q,    KC_W,    KC_E,      KC_R,     KC_T,     TD(LT),
        MO(FN1),   KC_A,    KC_S,    KC_D,      KC_F,     KC_G,
        KC_NO,     KC_NO,   KC_Z,    KC_X,      KC_C,     KC_V,     TD(LPRN),
        TD(CTRL),  KC_NO,   KC_NO,   KC_NO,     KC_LALT,
                                                      ILS,          BTC,
                                                                    KC_LWIN,
                                                KC_SPC,   TD(TAB),  KC_NO,
        // right hand
        KC_NO,    TD(SIX), TD(SEVEN), TD(EIGHT), TD(NINE), TD(ZERO), KC_NO,
        TD(GT),   KC_Y,    KC_U,      KC_I,      KC_O,     KC_P,     TD(PLUS),
                  KC_H,    KC_J,      KC_K,      KC_L,     TD(QUOT), TD(EQ),
        TD(RPRN), KC_B,    KC_N,      KC_M,      TD(COMM), TD(DOT),  TD(MINS),
                           KC_NO,     KC_NO,     KC_NO,    KC_NO,    KC_SLSH,

        KC_NO,    KC_NO,
        KC_NO,
        KC_RALT,  KC_BSPC, TD(RET)

    ),

/* Keymap 1: Function keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  | F2   |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
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
 *                                 |      |shift |      |       |      |      | shift|
 *                                 |      |  +   |------|       |------|  del |   +  |
 *                                 |      | tab  |      |       |      |      | enter|
 *                                 `--------------------'       `--------------------'
 */
// Function layer 1
[FN1] = LAYOUT_ergodox(
       KC_NO,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,     KC_F6,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO,     KC_NO,
                                                       KC_NO,
                                     KC_NO, S(KC_TAB), KC_NO,
    // right hand
       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,     KC_NO,
       KC_NO,  KC_PGUP, KC_HOME, KC_UP,   KC_END,     KC_NO,      KC_NO,
               KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,    KC_NO,      KC_NO,
       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,
                        KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,
       KC_NO,  KC_NO,
       KC_NO,
       KC_NO,  KC_DEL,  S(KC_ENT)
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
