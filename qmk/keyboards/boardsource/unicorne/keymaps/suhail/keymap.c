#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Layers
// ─────────────────────────────────────────────────────────────
enum layer_names {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _NUM,
    _FUNC,
    _ART,
};

// ─────────────────────────────────────────────────────────────
// Custom keycodes (ZMK behaviors -> QMK macros)
// ─────────────────────────────────────────────────────────────
enum custom_keycodes {
    PS_STAMP = SAFE_RANGE,  // Cmd+Opt+Shift+E
    PS_HIDE_SEL,            // Cmd+H (hide app)

    // macOS screenshots
    SS_FULL, SS_AREA, SS_UI, SS_FULL_CLIP, SS_AREA_CLIP, SS_WINDOW,

    // Spotlight
    SPOTLIGHT_MAIN, SPOTLIGHT_APPS, SPOTLIGHT_FILES, SPOTLIGHT_ACTIONS, SPOTLIGHT_CLIPBOARD,

    // Ghostty / iTerm splits
    SPLIT_V, SPLIT_H, SPLIT_X,

    // Neovim window ops
    NV_VSPLIT, NV_HSPLIT, NV_CLOSE,
};

// Convenience
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Home-row mod-taps
#define HM_LCTL_TAB  MT(MOD_LCTL, KC_TAB)
#define HM_RCTL_QUOT MT(MOD_RCTL, KC_QUOT)

// ─────────────────────────────────────────────────────────────
// Macro implementation
// ─────────────────────────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        /* Photoshop */
        case PS_STAMP:        tap_code16(G(A(S(KC_E)))); return false; // Cmd+Opt+Shift+E
        case PS_HIDE_SEL:     tap_code16(G(KC_H));       return false; // Cmd+H

        /* macOS screenshots */
        case SS_FULL:         tap_code16(G(S(KC_3)));    return false; // Full → file
        case SS_AREA:         tap_code16(G(S(KC_4)));    return false; // Area → file
        case SS_UI:           tap_code16(G(S(KC_5)));    return false; // Toolbar
        case SS_FULL_CLIP:    tap_code16(G(C(S(KC_3)))); return false; // Full → clipboard
        case SS_AREA_CLIP:    tap_code16(G(C(S(KC_4)))); return false; // Area → clipboard
        case SS_WINDOW:
            tap_code16(G(S(KC_4))); wait_ms(60); tap_code(KC_SPC);     // 4 then Space
            return false;

        /* Spotlight (Cmd+Space then Cmd+1/2/3/4) */
        case SPOTLIGHT_MAIN:      tap_code16(G(KC_SPC));                 return false;
        case SPOTLIGHT_APPS:      tap_code16(G(KC_SPC)); wait_ms(60); tap_code16(G(KC_1)); return false;
        case SPOTLIGHT_FILES:     tap_code16(G(KC_SPC)); wait_ms(60); tap_code16(G(KC_2)); return false;
        case SPOTLIGHT_ACTIONS:   tap_code16(G(KC_SPC)); wait_ms(60); tap_code16(G(KC_3)); return false;
        case SPOTLIGHT_CLIPBOARD: tap_code16(G(KC_SPC)); wait_ms(60); tap_code16(G(KC_4)); return false;

        /* Ghostty / iTerm terminal splits */
        case SPLIT_V:         tap_code16(G(C(KC_BSLS))); return false;  // Cmd+Ctrl+\
        case SPLIT_H:         tap_code16(G(C(KC_MINS))); return false;  // Cmd+Ctrl+-
        case SPLIT_X:         tap_code16(G(C(KC_X)));    return false;  // Cmd+Ctrl+X

        /* Neovim window ops: <C-w> v/s/c */
        case NV_VSPLIT:       tap_code16(C(KC_W)); tap_code(KC_V); return false;
        case NV_HSPLIT:       tap_code16(C(KC_W)); tap_code(KC_S); return false;
        case NV_CLOSE:        tap_code16(C(KC_W)); tap_code(KC_C); return false;
    }
    return true;
}

// UniCorne / Corne layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base */
[_BASE] = LAYOUT_split_3x6_3(
  KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,         KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
  HM_LCTL_TAB, KC_A, KC_S, KC_D,   KC_F,   KC_G,         KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, HM_RCTL_QUOT,
  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,         KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                         KC_LGUI, MO(_LOWER), KC_SPC,    KC_ENT, MO(_RAISE), KC_RALT
),

/* Lower (Numbers / Arrows + Mac actions) */
[_LOWER] = LAYOUT_split_3x6_3(
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,
  _______, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,         KC_LEFT,KC_DOWN,KC_UP,   KC_RIGHT,KC_KP_SLASH, KC_KP_ASTERISK,
  TG(_ART),TG(_NUM),_______,SPOTLIGHT_MAIN,SPOTLIGHT_APPS,SS_AREA, KC_MPRV,KC_VOLD,KC_VOLU, KC_MNXT, KC_MUTE, KC_MPLY,
                         KC_LGUI, _______, KC_SPC,       KC_ENT, MO(_FUNC), KC_RALT
),

/* Raise (Symbols) */
[_RAISE] = LAYOUT_split_3x6_3(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  KC_GRV,  KC_PIPE, KC_TILD, KC_MINS, KC_DQUO, KC_PLUS,     KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO,
  KC_CAPS, KC_BSLS, KC_GRV,  KC_UNDS, KC_QUOT, KC_EQL,      KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                         KC_LGUI, _______, KC_SPC,          KC_ENT, _______, KC_RALT
),

/* Num (right-hand numpad + nav) */
[_NUM] = LAYOUT_split_3x6_3(
  TG(_NUM), _______, _______, _______, _______, _______,    KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_BSPC,
  _______,  _______, _______, _______, _______, _______,    KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_KP_ASTERISK,
  _______,  _______, _______, _______, _______, _______,    KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_KP_SLASH,
                         _______, _______, _______,          KC_PENT, KC_P0,   KC_PDOT
),

/* Func (F-keys) — BT selectors were ZMK-only (BLE); we can add OS hotkeys later if needed */
[_FUNC] = LAYOUT_split_3x6_3(
  _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,        KC_F6,  KC_F7,  KC_F8,   KC_F9,  KC_F10, _______,
  _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,       KC_F16, KC_F17, KC_F18,  KC_F19, KC_F20, _______,
  _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
                         _______, _______, _______,       _______, _______, _______
),

/* Art (Photoshop) */
[_ART] = LAYOUT_split_3x6_3(
  TG(_ART), KC_Q,   KC_D,   KC_E,   KC_LBRC, KC_RBRC,     _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
  KC_LALT,  KC_J,   KC_S,   KC_BSPC,KC_LBRC, KC_RBRC,     _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,
  _______,  KC_Z,   KC_X,   KC_C,   PS_HIDE_SEL, KC_B,    _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,
                         KC_LGUI, _______, KC_SPC,        KC_ENT,  KC_P0,   KC_PDOT
),
};
