#include QMK_KEYBOARD_H

// ------------ Layers ------------
enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _NUM,
  _FUNC,
  _MOUSE,
  _ART,
};

// ------------ Custom keycodes ------------
enum custom_keycodes {
  SPLIT_V = SAFE_RANGE,   // Cmd+Ctrl+Backslash
  SPLIT_H,                // Cmd+Ctrl+Minus
  SPLIT_X,                // Cmd+Ctrl+X
  NV_VSPLIT,              // <C-w> v
  NV_HSPLIT,              // <C-w> s
  NV_CLOSE,               // <C-w> c
  SS_FULL,                // Cmd+Shift+3
  SS_AREA,                // Cmd+Shift+4
  SS_UI,                  // Cmd+Shift+5
  SS_FULL_CLIP,           // Cmd+Ctrl+Shift+3
  SS_AREA_CLIP,           // Cmd+Ctrl+Shift+4
  SS_WINDOW,              // Cmd+Shift+4 then Space
  SPOT_MAIN,              // Cmd+Space
  SPOT_APPS,              // Cmd+Space then Cmd+1
  SPOT_FILES,             // Cmd+Space then Cmd+2
  SPOT_ACTIONS,           // Cmd+Space then Cmd+3
  SPOT_CLIP,              // Cmd+Space then Cmd+4
  PS_STAMP,               // Cmd+Opt+Shift+E
};

// ------------ Helpers for chorded modifiers ------------
static void gui_ctrl_tap(uint16_t kc) {
  register_mods(MOD_LGUI | MOD_LCTL);
  tap_code(kc);
  unregister_mods(MOD_LGUI | MOD_LCTL);
}
static void cmd_shift_tap(uint16_t kc) {
  register_mods(MOD_LGUI | MOD_LSFT);
  tap_code(kc);
  unregister_mods(MOD_LGUI | MOD_LSFT);
}
static void cmd_ctrl_shift_tap(uint16_t kc) {
  register_mods(MOD_LGUI | MOD_LCTL | MOD_LSFT);
  tap_code(kc);
  unregister_mods(MOD_LGUI | MOD_LCTL | MOD_LSFT);
}
static void cmd_opt_shift_tap(uint16_t kc) {
  register_mods(MOD_LGUI | MOD_LALT | MOD_LSFT);
  tap_code(kc);
  unregister_mods(MOD_LGUI | MOD_LALT | MOD_LSFT);
}
static void hold_cmd_then(uint16_t kc) {
  register_code(KC_LGUI);
  tap_code(kc);
  unregister_code(KC_LGUI);
}
static void spotlight_then_num(uint16_t numkc) {
  register_code(KC_LGUI);
  tap_code(KC_SPACE);
  tap_code(numkc);
  unregister_code(KC_LGUI);
}

// ------------ Macros ------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  switch (keycode) {
    case SPLIT_V:      gui_ctrl_tap(KC_BSLS); return false;   // Cmd+Ctrl+\
    case SPLIT_H:      gui_ctrl_tap(KC_MINS); return false;   // Cmd+Ctrl+-
    case SPLIT_X:      gui_ctrl_tap(KC_X);    return false;   // Cmd+Ctrl+X

    case NV_VSPLIT:    tap_code16(LCTL(KC_W)); tap_code(KC_V); return false;
    case NV_HSPLIT:    tap_code16(LCTL(KC_W)); tap_code(KC_S); return false;
    case NV_CLOSE:     tap_code16(LCTL(KC_W)); tap_code(KC_C); return false;

    case SS_FULL:      cmd_shift_tap(KC_3);  return false;
    case SS_AREA:      cmd_shift_tap(KC_4);  return false;
    case SS_UI:        cmd_shift_tap(KC_5);  return false;
    case SS_FULL_CLIP: cmd_ctrl_shift_tap(KC_3); return false;
    case SS_AREA_CLIP: cmd_ctrl_shift_tap(KC_4); return false;
    case SS_WINDOW:    cmd_shift_tap(KC_4); tap_code(KC_SPC); return false;

    case SPOT_MAIN:    hold_cmd_then(KC_SPC); return false;
    case SPOT_APPS:    spotlight_then_num(KC_1); return false;
    case SPOT_FILES:   spotlight_then_num(KC_2); return false;
    case SPOT_ACTIONS: spotlight_then_num(KC_3); return false;
    case SPOT_CLIP:    spotlight_then_num(KC_4); return false;

    case PS_STAMP:     cmd_opt_shift_tap(KC_E); return false;
  }
  return true;
}

// ------------ Keymap ------------
#define HM_RCTL_QUOT MT(MOD_RCTL, KC_QUOT)  // tap ' ; hold Right Ctrl

// UniCorne typically uses LAYOUT_split_3x6_3.
// If you see a compile error, check info.json for the exact macro.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_3x6_3(
  KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
  LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K, KC_L, KC_SCLN, HM_RCTL_QUOT,
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_RALT
),

[_LOWER] = LAYOUT_split_3x6_3(
  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,       KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
  _______, KC_6, KC_7, KC_8, KC_9, KC_0,      KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_PSLS, KC_PAST,
  TG(_ART), TG(_NUM), TG(_MOUSE), SPOT_MAIN, SPOT_APPS, SS_AREA, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE, KC_MPLY,
                               KC_LGUI, _______, KC_SPC, KC_ENT, MO(_FUNC), KC_RALT
),

[_RAISE] = LAYOUT_split_3x6_3(
  KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  KC_GRV,  KC_PIPE, KC_TILD, KC_MINS, S(KC_QUOT), KC_PLUS, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, S(KC_QUOT),
  KC_CAPS, KC_BSLS, KC_GRV, KC_UNDS, KC_QUOT, KC_EQL,   KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                               KC_LGUI, _______, KC_SPC, KC_ENT, _______, KC_RALT
),

[_NUM] = LAYOUT_split_3x6_3(
  TG(_NUM), _______, _______, _______, _______, _______,    KC_HOME, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_BSPC,
  _______,  _______, _______, _______, _______, _______,    KC_PGUP, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PAST,
  _______,  _______, _______, _______, _______, _______,    KC_PGDN, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_PSLS,
                                _______, _______, _______,  KC_PENT, KC_P0, KC_PDOT
),

[_FUNC] = LAYOUT_split_3x6_3(
  _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,   KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
  _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                              _______, _______, _______, _______, _______, _______
),

[_MOUSE] = LAYOUT_split_3x6_3(
  TG(_MOUSE), _______, _______, _______, _______, _______,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
  _______, _______, _______, _______, _______, _______,      KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
  _______, _______, _______, _______, _______, _______,      KC_BTN4, KC_BTN5, _______, _______, _______, _______,
                               _______, _______, _______,    KC_BTN1, KC_BTN2, KC_BTN3
),

[_ART] = LAYOUT_split_3x6_3(
  TG(_ART), KC_Q, KC_D, KC_E, KC_LCBR, KC_RCBR,   _______, KC_7, KC_8, KC_9, _______, _______,
  KC_LALT,  KC_J, KC_S, KC_BSPC, KC_LBRC, KC_RBRC, _______, KC_4, KC_5, KC_6, _______, _______,
  _______,  KC_Z, KC_X, KC_C, KC_LGUI, KC_B,      _______, KC_1, KC_2, KC_3, _______, _______,
                           KC_LGUI, _______, KC_SPC, KC_ENT, KC_0, KC_DOT
),
};

// ------------ Combos ------------
// Right hand (Raise): J+K -> SPLIT_V, K+L -> SPLIT_H, H+J -> SPLIT_X
const uint16_t PROGMEM split_x_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM split_v_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM split_h_combo[] = {KC_K, KC_L, COMBO_END};

// Left hand (Raise): S+D -> NV_HSPLIT, D+F -> NV_VSPLIT, F+G -> NV_CLOSE
const uint16_t PROGMEM nv_hs_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM nv_vs_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM nv_cl_combo[] = {KC_F, KC_G, COMBO_END};

// ZX holdable Alt on Base or Art layers
const uint16_t PROGMEM alt_hold_combo[] = {KC_Z, KC_X, COMBO_END};

enum combo_names {
  CB_SPLIT_X,
  CB_SPLIT_V,
  CB_SPLIT_H,
  CB_NV_HS,
  CB_NV_VS,
  CB_NV_CL,
  CB_ALT_HOLD,
};

combo_t key_combos[] = {
  [CB_SPLIT_X] = COMBO(split_x_combo, SPLIT_X),
  [CB_SPLIT_V] = COMBO(split_v_combo, SPLIT_V),
  [CB_SPLIT_H] = COMBO(split_h_combo, SPLIT_H),
  [CB_NV_HS]   = COMBO(nv_hs_combo, NV_HSPLIT),
  [CB_NV_VS]   = COMBO(nv_vs_combo, NV_VSPLIT),
  [CB_NV_CL]   = COMBO(nv_cl_combo, NV_CLOSE),
  [CB_ALT_HOLD]= COMBO_ACTION(alt_hold_combo),
};

// Limit combos to intended layers
bool combo_should_trigger(uint16_t combo_index, combo_t *combo) {
  switch (combo_index) {
    case CB_SPLIT_X:
    case CB_SPLIT_V:
    case CB_SPLIT_H:
    case CB_NV_HS:
    case CB_NV_VS:
    case CB_NV_CL:
      return layer_state_is(_RAISE);
    case CB_ALT_HOLD:
      return layer_state_is(_BASE) || layer_state_is(_ART);
  }
  return true;
}

// Alt hold combo press/release
void process_combo_event(uint16_t combo_index, bool pressed) {
  if (combo_index == CB_ALT_HOLD) {
    if (pressed) {
      register_mods(MOD_LALT);
    } else {
      unregister_mods(MOD_LALT);
    }
  }
}
