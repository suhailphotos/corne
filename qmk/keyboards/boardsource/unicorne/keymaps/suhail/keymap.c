#include QMK_KEYBOARD_H

// ---------- Layers ----------
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _NUM,
    _FUNC,
    _MOUSE,
    _ART
};

// ---------- Custom keycodes for ZMK-like macros ----------
enum custom_keycodes {
    // Spotlight buckets
    SPOTLIGHT_MAIN = SAFE_RANGE,   // Cmd+Space
    SPOTLIGHT_APPS,                // Cmd+Space, then Cmd+1
    SPOTLIGHT_FILES,               // Cmd+Space, then Cmd+2
    SPOTLIGHT_ACTIONS,             // Cmd+Space, then Cmd+3
    SPOTLIGHT_CLIP,                // Cmd+Space, then Cmd+4

    // Screenshots (macOS)
    SS_FULL,       // Cmd+Shift+3
    SS_AREA,       // Cmd+Shift+4
    SS_UI,         // Cmd+Shift+5
    SS_FULL_CLIP,  // Cmd+Ctrl+Shift+3
    SS_AREA_CLIP,  // Cmd+Ctrl+Shift+4
    SS_WINDOW,     // Cmd+Shift+4 then Space

    // Photoshop helpers
    PS_HIDE_SEL,   // Cmd+H (hide selection overlay / app hide)
    PS_STAMP       // Cmd+Opt+Shift+E (Stamp Visible)
};

// ---------- Keymap ----------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_3x6_3(
    KC_ESC,              KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
    LCTL_T(KC_TAB),      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  RCTL_T(KC_QUOT),
    KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                         KC_LGUI,  MO(_LOWER), KC_SPC,    KC_ENT,  MO(_RAISE), KC_RALT
),

[_LOWER] = LAYOUT_split_3x6_3(
    KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,          KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS,
    _______, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,          KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SLSH,  KC_ASTR,
    TG(_ART),TG(_NUM),TG(_MOUSE),    SPOTLIGHT_MAIN, SPOTLIGHT_APPS, SS_AREA,
                                               KC_LGUI,     _______, KC_SPC, KC_ENT, MO(_FUNC), KC_RALT
),

[_RAISE] = LAYOUT_split_3x6_3(
    KC_TILD, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_GRV,  KC_PIPE, KC_TILD,KC_MINS, KC_DQUO, KC_PLUS,     KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO,
    KC_CAPS, KC_BSLS, KC_GRV, KC_UNDS, KC_QUOT, KC_EQL,      KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                                         KC_LGUI,  _______,  KC_SPC,  KC_ENT,  _______, KC_RALT
),

[_NUM] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,     KC_HOME, KC_7,    KC_8,    KC_9,    KC_MINS, KC_BSPC,
    _______, _______, _______, _______, _______, _______,     KC_PGUP, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_PAST,
    _______, _______, _______, _______, _______, _______,     KC_PGDN, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_PSLS,
                                         _______, _______,    _______, KC_ENT,  KC_0,    KC_DOT
),

[_FUNC] = LAYOUT_split_3x6_3(
    _______, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, KC_F11,  KC_F12, KC_F13, KC_F14, KC_F15,        KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                                         _______, _______,    _______, _______, _______, _______
),

[_MOUSE] = LAYOUT_split_3x6_3(
    TG(_MOUSE), _______, _______, _______, _______, _______,     KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
    _______,    _______, _______, _______, _______, _______,     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
    _______,    _______, _______, _______, _______, _______,     KC_BTN4, KC_BTN5, _______, _______, _______, _______,
                                            _______, _______,    _______,  KC_BTN1, KC_BTN2, KC_BTN3
),

[_ART] = LAYOUT_split_3x6_3(
    TG(_ART), KC_Q,   KC_D,   KC_E,   KC_LBRC, KC_RBRC,      _______, KC_7,    KC_8,    KC_9,    _______, _______,
    KC_LALT,  KC_J,   KC_S,   KC_BSPC,KC_LBRC, KC_RBRC,      _______, KC_4,    KC_5,    KC_6,    _______, _______,
    _______,  KC_Z,   KC_X,   KC_C,   PS_HIDE_SEL, KC_B,     _______, KC_1,    KC_2,    KC_3,    _______, _______,
                                         KC_LGUI, _______,    KC_SPC, KC_ENT,  KC_0,    KC_DOT
)
};

// ---------- Process custom keycodes ----------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return true; }

    switch (keycode) {
        // Spotlight
        case SPOTLIGHT_MAIN:      tap_code16(G(KC_SPC)); return false;
        case SPOTLIGHT_APPS:      tap_code16(G(KC_SPC)); tap_code16(G(KC_1)); return false;
        case SPOTLIGHT_FILES:     tap_code16(G(KC_SPC)); tap_code16(G(KC_2)); return false;
        case SPOTLIGHT_ACTIONS:   tap_code16(G(KC_SPC)); tap_code16(G(KC_3)); return false;
        case SPOTLIGHT_CLIP:      tap_code16(G(KC_SPC)); tap_code16(G(KC_4)); return false;

        // Screenshots
        case SS_FULL:             tap_code16(G(S(KC_3))); return false;
        case SS_AREA:             tap_code16(G(S(KC_4))); return false;
        case SS_UI:               tap_code16(G(S(KC_5))); return false;
        case SS_FULL_CLIP:        tap_code16(G(C(S(KC_3)))); return false;
        case SS_AREA_CLIP:        tap_code16(G(C(S(KC_4)))); return false;
        case SS_WINDOW:           tap_code16(G(S(KC_4))); tap_code(KC_SPC); return false;

        // Photoshop helpers
        case PS_HIDE_SEL:         tap_code16(G(KC_H)); return false;
        case PS_STAMP:            tap_code16(G(A(S(KC_E)))); return false;
    }
    return true;
}

// ---------- Combos (to mirror your ZMK combos) ----------
// Right hand (RAISE): H+J, J+K, K+L -> terminal splits
// On RAISE layer those physical keys output: {, }, (, )
const uint16_t PROGMEM cb_term_x[]   = { KC_LCBR, KC_RCBR, COMBO_END }; // H+J -> Cmd+Ctrl+X
const uint16_t PROGMEM cb_term_v[]   = { KC_RCBR, KC_LPRN, COMBO_END }; // J+K -> Cmd+Ctrl+Backslash
const uint16_t PROGMEM cb_term_h[]   = { KC_LPRN, KC_RPRN, COMBO_END }; // K+L -> Cmd+Ctrl+Minus

// Left hand (RAISE): S+D, D+F, F+G -> Neovim window commands
// On RAISE layer those physical keys output: |, ~, -
const uint16_t PROGMEM cb_nv_hsplit[] = { KC_PIPE, KC_TILD, COMBO_END }; // S+D -> <C-w> s
const uint16_t PROGMEM cb_nv_vsplit[] = { KC_TILD, KC_MINS, COMBO_END }; // D+F -> <C-w> v
const uint16_t PROGMEM cb_nv_close[]  = { KC_MINS, KC_DQUO, COMBO_END }; // F+G -> <C-w> c

// Base/Art: Z+X = hold Left Alt while held (for ⌥-drag)
const uint16_t PROGMEM cb_alt_hold_zx[] = { KC_Z, KC_X, COMBO_END };

// Base: Q+W+E -> PS_STAMP
const uint16_t PROGMEM cb_ps_stamp_qwe[] = { KC_Q, KC_W, KC_E, COMBO_END };

enum combo_events {
    CB_TERM_X,
    CB_TERM_V,
    CB_TERM_H,
    CB_NV_HSPLIT,
    CB_NV_VSPLIT,
    CB_NV_CLOSE,
    CB_ALT_HOLD_ZX,
    CB_PS_STAMP_QWE,
    COMBO_EVENT_COUNT
};

combo_t key_combos[COMBO_EVENT_COUNT] = {
    [CB_TERM_X]        = COMBO_ACTION(cb_term_x),
    [CB_TERM_V]        = COMBO_ACTION(cb_term_v),
    [CB_TERM_H]        = COMBO_ACTION(cb_term_h),
    [CB_NV_HSPLIT]     = COMBO_ACTION(cb_nv_hsplit),
    [CB_NV_VSPLIT]     = COMBO_ACTION(cb_nv_vsplit),
    [CB_NV_CLOSE]      = COMBO_ACTION(cb_nv_close),
    [CB_ALT_HOLD_ZX]   = COMBO_ACTION(cb_alt_hold_zx),
    [CB_PS_STAMP_QWE]  = COMBO_ACTION(cb_ps_stamp_qwe),
};

uint16_t COMBO_LEN = COMBO_EVENT_COUNT;

// What to do when a combo triggers
void process_combo_event(uint16_t index, bool pressed) {
    switch (index) {
        // Terminal (Ghostty/iTerm) splits
        case CB_TERM_X:
            if (pressed) { tap_code16(G(C(KC_X))); } // Cmd+Ctrl+X (close)
            break;
        case CB_TERM_V:
            if (pressed) { tap_code16(G(C(KC_BSLS))); } // Cmd+Ctrl+Backslash (vertical split)
            break;
        case CB_TERM_H:
            if (pressed) { tap_code16(G(C(KC_MINS))); } // Cmd+Ctrl+Minus (horizontal split)
            break;

        // Neovim windowing: <C-w> v / s / c
        case CB_NV_HSPLIT:
            if (pressed) { tap_code16(C(KC_W)); tap_code(KC_S); }
            break;
        case CB_NV_VSPLIT:
            if (pressed) { tap_code16(C(KC_W)); tap_code(KC_V); }
            break;
        case CB_NV_CLOSE:
            if (pressed) { tap_code16(C(KC_W)); tap_code(KC_C); }
            break;

        // Holdable Left Alt via Z+X
        case CB_ALT_HOLD_ZX:
            if (pressed) {
                register_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
            }
            break;

        // Q+W+E -> Stamp Visible
        case CB_PS_STAMP_QWE:
            if (pressed) { tap_code16(G(A(S(KC_E)))); }
            break;
    }
}
