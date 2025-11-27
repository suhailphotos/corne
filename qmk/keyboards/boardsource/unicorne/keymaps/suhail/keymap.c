#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
// Provided by keyboards/boardsource/lib/oled.c
void render_layer_state(void);
#endif

// Small delay so macOS has time to show Spotlight before we send Cmd+1/2/3/4
#define SPOTLIGHT_BUCKET_DELAY 90  // ms; tweak if needed

static void spotlight_bucket(uint16_t kc_digit) {
    // Cmd+Space
    tap_code16(G(KC_SPC));
    wait_ms(SPOTLIGHT_BUCKET_DELAY);
    // Cmd+<digit>
    tap_code16(G(kc_digit));
}

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
    KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_MINS,
    _______, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,         KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_PSLS, KC_PAST,
    TG(_ART),TG(_NUM),TG(_MOUSE), SPOTLIGHT_MAIN, SPOTLIGHT_APPS, SS_AREA,
                                                           KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,KC_MUTE, KC_MPLY,
                                KC_LGUI, _______, KC_SPC,  KC_ENT, MO(_FUNC), KC_RALT
),

[_RAISE] = LAYOUT_split_3x6_3(
    KC_TILD, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_GRV,  KC_PIPE, KC_TILD,KC_MINS, KC_DQUO, KC_PLUS,     KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO,
    KC_CAPS, KC_BSLS, KC_GRV, KC_UNDS, KC_QUOT, KC_EQL,      KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                                         KC_LGUI,  _______,  KC_SPC,  KC_ENT,  _______, KC_RALT
),

[_NUM] = LAYOUT_split_3x6_3(
    TG(_NUM), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_HOME, KC_7,    KC_8,    KC_9,    KC_MINS, KC_BSPC,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PGUP, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_PAST,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PGDN, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_PSLS,
                                         _______, _______,    _______, KC_ENT,  KC_0,    KC_DOT
),

[_FUNC] = LAYOUT_split_3x6_3(
    _______, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, KC_F11,  KC_F12, KC_F13, KC_F14, KC_F15,        KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                                         _______, _______,    _______, _______, _______, _______
),

[_MOUSE] = LAYOUT_split_3x6_3(
    TG(_MOUSE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, _______,
    _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                              _______, _______, _______,      MS_BTN1, MS_BTN2, MS_BTN3
),

[_ART] = LAYOUT_split_3x6_3(
    TG(_ART), KC_Q,   KC_D,   KC_E,   KC_LBRC, KC_RBRC,      _______, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX,
    KC_LALT,  KC_J,   KC_S,   KC_BSPC,KC_LBRC, KC_RBRC,      _______, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,
    _______,  KC_Z,   KC_X,   KC_C,   PS_HIDE_SEL, KC_B,     _______, KC_1,    KC_2,    KC_3,    XXXXXXX, _______,
                                         KC_LGUI, XXXXXXX,    KC_SPC, KC_ENT,  KC_0,    KC_DOT
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return true; }

    switch (keycode) {
        // Spotlight
        case SPOTLIGHT_MAIN:
            tap_code16(G(KC_SPC));
            return false;

        case SPOTLIGHT_APPS:
            spotlight_bucket(KC_1);
            return false;

        case SPOTLIGHT_FILES:
            spotlight_bucket(KC_2);
            return false;

        case SPOTLIGHT_ACTIONS:
            spotlight_bucket(KC_3);
            return false;

        case SPOTLIGHT_CLIP:
            spotlight_bucket(KC_4);
            return false;

        // Screenshots (macOS)
        case SS_FULL:             tap_code16(G(S(KC_3)));         return false;
        case SS_AREA:             tap_code16(G(S(KC_4)));         return false;
        case SS_UI:               tap_code16(G(S(KC_5)));         return false;
        case SS_FULL_CLIP:        tap_code16(G(C(S(KC_3))));      return false;
        case SS_AREA_CLIP:        tap_code16(G(C(S(KC_4))));      return false;
        case SS_WINDOW:           tap_code16(G(S(KC_4))); tap_code(KC_SPC); return false;

        // Photoshop helpers
        case PS_HIDE_SEL:         tap_code16(G(KC_H));            return false;
        case PS_STAMP:            tap_code16(G(A(S(KC_E))));      return false;
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

// Art: Q+D+E -> PS_STAMP (Art layer remaps W -> D)
const uint16_t PROGMEM cb_ps_stamp_qde[] = { KC_Q, KC_D, KC_E, COMBO_END };


enum combo_events {
    CB_TERM_X,
    CB_TERM_V,
    CB_TERM_H,
    CB_NV_HSPLIT,
    CB_NV_VSPLIT,
    CB_NV_CLOSE,
    CB_ALT_HOLD_ZX,
    CB_PS_STAMP_QWE,
    CB_PS_STAMP_QDE,
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
    [CB_PS_STAMP_QDE]  = COMBO_ACTION(cb_ps_stamp_qde),
};

uint16_t COMBO_LEN = COMBO_EVENT_COUNT;

// What to do when a combo triggers
void process_combo_event(uint16_t index, bool pressed) {
    switch (index) {
        // Terminal (Ghostty/iTerm) splits
        case CB_TERM_X:
            if (pressed) { tap_code16(G(C(KC_X))); }
            break;
        case CB_TERM_V:
            if (pressed) { tap_code16(G(C(KC_BSLS))); }
            break;
        case CB_TERM_H:
            if (pressed) { tap_code16(G(C(KC_MINS))); }
            break;

        // Neovim windowing
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

        // PS Stamp – Base (Q+W+E) and Art (Q+D+E)
        case CB_PS_STAMP_QWE:
        case CB_PS_STAMP_QDE:
            if (pressed) {
                tap_code16(G(A(S(KC_E))));
            }
            break;
    }
}

#ifdef OLED_ENABLE

// Provided by keyboards/boardsource/lib/oled.c
void render_layer_state(void);

// Short names for layers – tweak to taste
static const char layer_name[][8] = {
    "Base",   // 0
    "Lower",  // 1
    "Raise",  // 2
    "Num",    // 3
    "Func",   // 4
    "Mouse",  // 5
    "Art",    // 6
};

bool oled_task_user(void) {
    // If the keyboard firmware already draws the left OLED in oled_task_kb,
    // we leave it alone and only touch the right side.
    if (is_keyboard_left()) {
        return false;  // let keyboard-level code do its thing
    }

    // Right half: custom status instead of the lulu logo (if this gets called)
    oled_clear();

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    if (layer >= (uint8_t)(sizeof(layer_name) / sizeof(layer_name[0]))) {
        layer = 0;
    }

    // Row 0: "Lyra desk"
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Lyra desk"), false);

    // Row 1: current layer name
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("Layer:"), false);
    oled_set_cursor(7, 1);
    oled_write(layer_name[layer], false);

    // Row 2: numeric index (1–7)
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("Idx:"), false);
    oled_write_char('0' + (layer + 1), false);

    return false;  // we handled drawing for the right half
}

#endif // OLED_ENABLE

#ifdef RGB_MATRIX_ENABLE

// ───────────────── Layer and accent colors (edit here) ─────────────────

// Layer colors (0–255 hue space)
static const uint8_t H_BASE   = 0;
static const uint8_t S_BASE   = 0;
static const uint8_t V_BASE   = 90;

static const uint8_t H_LOWER  = 14;    // ~20°
static const uint8_t S_LOWER  = 180;
static const uint8_t V_LOWER  = 90;

static const uint8_t H_RAISE  = 142;   // ~200°
static const uint8_t S_RAISE  = 200;
static const uint8_t V_RAISE  = 90;

static const uint8_t H_NUM    = 99;    // ~140°
static const uint8_t S_NUM    = 200;
static const uint8_t V_NUM    = 90;

static const uint8_t H_MOUSE  = 71;    // ~100°
static const uint8_t S_MOUSE  = 200;
static const uint8_t V_MOUSE  = 90;

static const uint8_t H_ART    = 241;   // ~340°
static const uint8_t S_ART    = 180;
static const uint8_t V_ART    = 90;

// ───────────── Accent colors (tweak these to taste) ─────────────

// Home-row Ctrl mods (LCTL_T / RCTL_T)
static const uint8_t H_HOME_CTRL = 210;
static const uint8_t S_HOME_CTRL = 200;
static const uint8_t V_HOME_CTRL = 120;

// Command (GUI)
static const uint8_t H_GUI       = 190;
static const uint8_t S_GUI       = 200;
static const uint8_t V_GUI       = 120;

// Option / Alt (KC_LALT, KC_RALT, plus Z+X “Option combo” hints)
static const uint8_t H_OPTION    = 30;
static const uint8_t S_OPTION    = 200;
static const uint8_t V_OPTION    = 120;

// Shift (LSHFT / RSHFT)
static const uint8_t H_SHIFT     = 230;
static const uint8_t S_SHIFT     = 180;
static const uint8_t V_SHIFT     = 120;

// Space bar
static const uint8_t H_SPACE     = 0;
static const uint8_t S_SPACE     = 0;
static const uint8_t V_SPACE     = 130;

// Enter / Return
static const uint8_t H_ENTER     = 120;
static const uint8_t S_ENTER     = 200;
static const uint8_t V_ENTER     = 130;

// Esc + Backspace “home” keys
static const uint8_t H_ESC_BSPC  = 0;
static const uint8_t S_ESC_BSPC  = 0;
static const uint8_t V_ESC_BSPC  = 150;


// Get per-layer base HSV
static void get_layer_hsv(uint8_t layer, uint8_t *h, uint8_t *s, uint8_t *v) {
    switch (layer) {
        case _LOWER:
            *h = H_LOWER; *s = S_LOWER; *v = V_LOWER;
            break;
        case _RAISE:
            *h = H_RAISE; *s = S_RAISE; *v = V_RAISE;
            break;
        case _NUM:
            *h = H_NUM; *s = S_NUM; *v = V_NUM;
            break;
        case _MOUSE:
            *h = H_MOUSE; *s = S_MOUSE; *v = V_MOUSE;
            break;
        case _ART:
            *h = H_ART; *s = S_ART; *v = V_ART;
            break;
        default:
            // _BASE and anything else
            *h = H_BASE; *s = S_BASE; *v = V_BASE;
            break;
    }
}

// Resolve what this key *actually* does based on active layers
static uint16_t get_effective_keycode(keypos_t key) {
    uint32_t state   = layer_state | default_layer_state;
    uint8_t  highest = get_highest_layer(state);

    // Walk from highest active layer down to 0,
    // but *only* through layers whose bit is set.
    for (int8_t l = (int8_t)highest; l >= 0; l--) {
        if (!(state & (1UL << l))) {
            continue; // layer not active
        }
        uint16_t kc = keymap_key_to_keycode((uint8_t)l, key);
        if (kc != KC_TRNS) {
            return kc;
        }
    }
    return KC_NO;
}

// Run once after init
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

// Per-frame LED logic
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint32_t state        = layer_state | default_layer_state;
    uint8_t  active_layer = get_highest_layer(state);

    uint8_t h_layer, s_layer, v_layer;
    get_layer_hsv(active_layer, &h_layer, &s_layer, &v_layer);

    HSV hsv_layer = (HSV){ h_layer, s_layer, v_layer };
    RGB rgb_layer = hsv_to_rgb(hsv_layer);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index == NO_LED) {
                continue;
            }
            if (led_index < led_min || led_index > led_max) {
                continue;
            }

            keypos_t key = (keypos_t){ .row = row, .col = col };

            // 1) Effective keycode from *active* layers (with transparency)
            uint16_t keycode = get_effective_keycode(key);

            // 2) Base-layer role for this physical key
            uint16_t base_kc = keymap_key_to_keycode(_BASE, key);

            // 3) Did the role actually change?
            bool same_role = (keycode == base_kc);

            // Dead key (KC_NO / XXXXXXX after resolution) → LED off
            if (keycode == KC_NO) {
                rgb_matrix_set_color(led_index, 0, 0, 0);
                continue;
            }

            // Start from the layer color
            RGB rgb_final = rgb_layer;

            // ───────────── Stable accents (only if same_role) ─────────────
            if (same_role) {
                // Home-row Ctrl mods (both sides)
                if (base_kc == LCTL_T(KC_TAB) || base_kc == RCTL_T(KC_QUOT)) {
                    HSV hsv = (HSV){ H_HOME_CTRL, S_HOME_CTRL, V_HOME_CTRL };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Command (GUI)
                else if (base_kc == KC_LGUI || base_kc == KC_RGUI) {
                    HSV hsv = (HSV){ H_GUI, S_GUI, V_GUI };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Option / Alt:
                //   - Physical Option keys
                //   - Z/X as “Option combo” hint positions
                else if (base_kc == KC_LALT || base_kc == KC_RALT ||
                         base_kc == KC_Z    || base_kc == KC_X) {
                    HSV hsv = (HSV){ H_OPTION, S_OPTION, V_OPTION };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Shift keys
                else if (base_kc == KC_LSFT || base_kc == KC_RSFT) {
                    HSV hsv = (HSV){ H_SHIFT, S_SHIFT, V_SHIFT };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Space bar
                else if (base_kc == KC_SPC) {
                    HSV hsv = (HSV){ H_SPACE, S_SPACE, V_SPACE };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Enter / Return
                else if (base_kc == KC_ENT) {
                    HSV hsv = (HSV){ H_ENTER, S_ENTER, V_ENTER };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Esc + Backspace “home” keys
                else if (base_kc == KC_ESC || base_kc == KC_BSPC) {
                    HSV hsv = (HSV){ H_ESC_BSPC, S_ESC_BSPC, V_ESC_BSPC };
                    rgb_final = hsv_to_rgb(hsv);
                }
                // Layer keys on base: “key that takes you there”
                else if (base_kc == MO(_LOWER)) {
                    HSV hsv = (HSV){ H_LOWER, S_LOWER, V_LOWER };
                    rgb_final = hsv_to_rgb(hsv);
                } else if (base_kc == MO(_RAISE)) {
                    HSV hsv = (HSV){ H_RAISE, S_RAISE, V_RAISE };
                    rgb_final = hsv_to_rgb(hsv);
                }
            }

            rgb_matrix_set_color(led_index, rgb_final.r, rgb_final.g, rgb_final.b);
        }
    }

    return false;
}

#endif // RGB_MATRIX_ENABLE
