#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────────────────────
// Layers
// ─────────────────────────────────────────────────────────────────────────────
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _NUM,
    _FUNC,
    _ART,
};

// ─────────────────────────────────────────────────────────────────────────────
// Custom keycodes (if we ever want to place the macros on keys directly).
// For now, combos trigger these actions in code below.
// ─────────────────────────────────────────────────────────────────────────────
enum custom_keycodes {
    SPLIT_V = SAFE_RANGE,  // Cmd+Ctrl+Backslash (Ghostty/iTerm vertical split)
    SPLIT_H,               // Cmd+Ctrl+Minus    (horizontal split)
    SPLIT_X,               // Cmd+Ctrl+X        (close terminal surface)
    NV_VSPLIT,             // <C-w> v
    NV_HSPLIT,             // <C-w> s
    NV_CLOSE,              // <C-w> c
    PS_STAMP,              // Cmd+Opt+Shift+E   (Photoshop "Stamp Visible")
};

// ─────────────────────────────────────────────────────────────────────────────
// Keymaps
// Layout macro for Corne/UniCorne is LAYOUT_split_3x6_3.
// ─────────────────────────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: Base (QWERTY) */
    [_BASE] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,            KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC,
        LCTL_T(KC_TAB),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, RCTL_T(KC_QUOT),
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LGUI, MO(_LOWER), KC_SPC,         KC_ENT, MO(_RAISE), KC_RALT
    ),

    /* 1: Lower (numbers / arrows / media) */
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
        _______, KC_6, KC_7, KC_8, KC_9, KC_0,                     KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SLSH,KC_ASTR,
        _______, _______, _______, _______, _______, _______,       KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,KC_MUTE,KC_MPLY,
                                   KC_LGUI, _______, KC_SPC,       KC_ENT,  MO(_FUNC), KC_RALT
    ),

    /* 2: Raise (symbols) */
    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TILD, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        KC_GRV,  KC_PIPE, KC_TILD,KC_MINS, KC_DQUO, KC_PLUS,       KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO,
        KC_CAPS, KC_BSLS, KC_GRV, KC_UNDS, KC_QUOT, KC_EQL,        KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                                   KC_LGUI, _______, KC_SPC,       KC_ENT,  _______, KC_RALT
    ),

    /* 3: Num (numpad-ish + nav) */
    [_NUM] = LAYOUT_split_3x6_3(
        TG(_NUM), _______, _______, _______, _______, _______,      KC_HOME, KC_7, KC_8, KC_9, KC_MINS, KC_BSPC,
        _______,  _______, _______, _______, _______, _______,      KC_PGUP, KC_4, KC_5, KC_6, KC_PLUS, KC_PAST,
        _______,  _______, _______, _______, _______, _______,      KC_PGDN, KC_1, KC_2, KC_3, KC_EQL,  KC_PSLS,
                                   _______, _______, _______,      KC_ENT,  KC_0, KC_DOT
    ),

    /* 4: Func (F-keys; BT omitted on QMK) */
    [_FUNC] = LAYOUT_split_3x6_3(
        _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,            KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,
        _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,           KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,       _______, _______, _______
    ),

    /* 5: Art (Photoshop helpers; right-hand digits for opacity/flow) */
    [_ART] = LAYOUT_split_3x6_3(
        TG(_ART), KC_Q, KC_D, KC_E, KC_LBRC, KC_RBRC,              _______, KC_7, KC_8, KC_9, _______, _______,
        KC_LALT,  KC_J, KC_S, KC_BSPC, KC_LBRC, KC_RBRC,           _______, KC_4, KC_5, KC_6, _______, _______,
        _______,  KC_Z, KC_X, KC_C,   KC_H,   KC_B,                _______, KC_1, KC_2, KC_3, _______, _______,
                                   KC_LGUI, _______, KC_SPC,       KC_ENT, KC_0, KC_DOT
    ),
};

// ─────────────────────────────────────────────────────────────────────────────
// Tri-layer: Lower + Raise -> Num
// ─────────────────────────────────────────────────────────────────────────────
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _NUM);
}

// ─────────────────────────────────────────────────────────────────────────────
// Macros (used by combos below). Keep comments free of trailing '\' characters.
// ─────────────────────────────────────────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case SPLIT_V: // Cmd+Ctrl+Backslash
            tap_code16(G(C(KC_BSLS)));
            return false;

        case SPLIT_H: // Cmd+Ctrl+Minus
            tap_code16(G(C(KC_MINS)));
            return false;

        case SPLIT_X: // Cmd+Ctrl+X
            tap_code16(G(C(KC_X)));
            return false;

        case NV_VSPLIT: // <C-w> v
            tap_code16(C(KC_W));
            tap_code(KC_V);
            return false;

        case NV_HSPLIT: // <C-w> s
            tap_code16(C(KC_W));
            tap_code(KC_S);
            return false;

        case NV_CLOSE: // <C-w> c
            tap_code16(C(KC_W));
            tap_code(KC_C);
            return false;

        case PS_STAMP: // Cmd+Opt+Shift+E
            tap_code16(G(A(S(KC_E))));
            return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Combos
// We'll use COMBO_ACTION so we can restrict by layer in code reliably.
// ─────────────────────────────────────────────────────────────────────────────
enum combo_events {
    CB_TERM_CLOSE,
    CB_TERM_V,
    CB_TERM_H,
    CB_NV_HSPLIT,
    CB_NV_VSPLIT,
    CB_NV_CLOSE,
    CB_ALT_HOLD_ZX,
    CB_PS_STAMP_QWE,
    CB_COUNT
};

const uint16_t PROGMEM cm_term_close[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM cm_term_v[]     = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cm_term_h[]     = {KC_K, KC_L, COMBO_END};

const uint16_t PROGMEM cm_nv_hsplit[]  = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM cm_nv_vsplit[]  = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cm_nv_close[]   = {KC_F, KC_G, COMBO_END};

const uint16_t PROGMEM cm_alt_hold_zx[]  = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM cm_ps_stamp_qwe[] = {KC_Q, KC_W, KC_E, COMBO_END};

combo_t key_combos[] = {
    [CB_TERM_CLOSE]   = COMBO_ACTION(cm_term_close),
    [CB_TERM_V]       = COMBO_ACTION(cm_term_v),
    [CB_TERM_H]       = COMBO_ACTION(cm_term_h),

    [CB_NV_HSPLIT]    = COMBO_ACTION(cm_nv_hsplit),
    [CB_NV_VSPLIT]    = COMBO_ACTION(cm_nv_vsplit),
    [CB_NV_CLOSE]     = COMBO_ACTION(cm_nv_close),

    [CB_ALT_HOLD_ZX]  = COMBO_ACTION(cm_alt_hold_zx),
    [CB_PS_STAMP_QWE] = COMBO_ACTION(cm_ps_stamp_qwe),
};

// With COMBO_VARIABLE_LEN we don't need to define COMBO_LEN explicitly.

// Fire combos; gate the terminal / neovim ones to the Raise layer just like ZMK.
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;

    switch (combo_index) {
        // Right-hand = terminal splits (Raise only)
        case CB_TERM_CLOSE:
            if (layer_state_is(_RAISE)) process_record_user(SPLIT_X, &(keyrecord_t){.event.pressed=true});
            break;
        case CB_TERM_V:
            if (layer_state_is(_RAISE)) process_record_user(SPLIT_V, &(keyrecord_t){.event.pressed=true});
            break;
        case CB_TERM_H:
            if (layer_state_is(_RAISE)) process_record_user(SPLIT_H, &(keyrecord_t){.event.pressed=true});
            break;

        // Left-hand = Neovim splits (Raise only)
        case CB_NV_HSPLIT:
            if (layer_state_is(_RAISE)) process_record_user(NV_HSPLIT, &(keyrecord_t){.event.pressed=true});
            break;
        case CB_NV_VSPLIT:
            if (layer_state_is(_RAISE)) process_record_user(NV_VSPLIT, &(keyrecord_t){.event.pressed=true});
            break;
        case CB_NV_CLOSE:
            if (layer_state_is(_RAISE)) process_record_user(NV_CLOSE, &(keyrecord_t){.event.pressed=true});
            break;

        // Base: Z+X -> holdable Left Alt (safe for Photoshop option-drag)
        case CB_ALT_HOLD_ZX:
            tap_code(KC_LALT);
            break;

        // Base: Q+W+E -> Photoshop stamp visible
        case CB_PS_STAMP_QWE:
            process_record_user(PS_STAMP, &(keyrecord_t){.event.pressed=true});
            break;
    }
}
