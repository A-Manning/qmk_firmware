#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  LSFT = 0,
  RSFT,
  MOD
};

int cur_dance (qk_tap_dance_state_t *state);

//for the ( tap dance. Put it here so it can be used in any keymap
void l_shf_finished (qk_tap_dance_state_t *state, void *user_data);
void l_shf_reset (qk_tap_dance_state_t *state, void *user_data);
// ) tap dance.
void r_shf_finished (qk_tap_dance_state_t *state, void *user_data);
void r_shf_reset (qk_tap_dance_state_t *state, void *user_data);
// mod tap dance
void mod_finished (qk_tap_dance_state_t *state, void *user_data);
void mod_reset (qk_tap_dance_state_t *state, void *user_data);
