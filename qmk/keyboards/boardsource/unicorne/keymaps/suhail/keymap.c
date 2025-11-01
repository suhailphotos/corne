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

// Convenience
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Home-row mod-taps that match your intent:
// - Left thumb row first key on row 2 was "HM LEFT_CONTROL TAB" in ZMK
// - Right row-2 far right was "HM RIGHT_CONTROL SQT"
#define HM_LCTL_TAB  MT(MOD_LCTL, KC_TAB)
#define HM_RCTL_QUOT MT(MOD_RCTL, KC_QUOT)

// Layout note: UniCorne uses the Corne-style LAYOUT_split_3x6_3
// [12 keys per row] x 3 rows, plus [3 thumbs per side].

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ───────────────────────────── Base ─────────────────────────────
 * Esc  Q    W    E    R    T      Y    U    I     O     P     Bspc
 * Ct/T A    S    D    F    G      H    J    K     L     ;     Ct/'
 * LSh  Z    X    C    V    B      N    M    ,     .     /     RSh
 *             LGUI  MO1  Space    Enter  MO2  RAlt
 */
[_BASE] = LAYOUT_split_3x6_3(
  KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,         KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
  HM_LCTL_TAB, KC_A, KC_S, KC_D,   KC_F,   KC_G,         KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, HM_RCTL_QUOT,
  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,         KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                         KC_LGUI, MO(_LOWER), KC_SPC,    KC_ENT, MO(_RAISE), KC_RALT
),

/* ─────────────────────────── Lower ─────────────────────────────
 * `    1    2    3    4    5      6    7    8     9     0     -
 *      6    7    8    9    0      ←    ↓    ↑     →     KP/   KP*
 * TG A TG N ____ ____ ____ ____   MPRV VOLD  VOLU  MNXT  MUTE  MPLY
 *             LGUI  ____ Space    Enter  MO4  RAlt
 *
 * Notes:
 * - Placeholder keys (____ = KC_TRNS or KC_NO) where your ZMK macros were.
 * - We’ll wire Spotlight/Screenshot macros in a later step.
 * - TG A = toggle Art layer, TG N = toggle Num layer.
 */
[_LOWER] = LAYOUT_split_3x6_3(
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,
  _______, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,         KC_LEFT,KC_DOWN,KC_UP,   KC_RIGHT,KC_KP_SLASH, KC_KP_ASTERISK,
  TG(_ART),TG(_NUM),_______,_______,_______,_______,     KC_MPRV,KC_VOLD,KC_VOLU, KC_MNXT, KC_MUTE, KC_MPLY,
                         KC_LGUI, _______, KC_SPC,       KC_ENT, MO(_FUNC), KC_RALT
),

/* ─────────────────────────── Raise ─────────────────────────────
 * ~    !    @    #    $    %      ^    &    *     (     )     _
 * `    |    ~    -    "    +      {    }    (     )     :     "
 * Caps \    `    _    '    =      [    ]    <     >     ?     __
 *             LGUI  ____ Space    Enter  ____ RAlt
 *
 * (Using QMK punctuation keycodes; we can adjust any symbols later.)
 */
[_RAISE] = LAYOUT_split_3x6_3(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  KC_GRV,  KC_PIPE, KC_TILD, KC_MINS, KC_DQUO, KC_PLUS,     KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO,
  KC_CAPS, KC_BSLS, KC_GRV,  KC_UNDS, KC_QUOT, KC_EQL,      KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, _______,
                         KC_LGUI, _______, KC_SPC,          KC_ENT, _______, KC_RALT
),

/* ─────────────────────────── Num (numpad on right) ─────────────
 * TG N ____ ____ ____ ____ ____   Home  7     8     9     -     Bspc
 * ____ ____ ____ ____ ____ ____   PgUp  4     5     6     +     KP*
 * ____ ____ ____ ____ ____ ____   PgDn  1     2     3     =     KP/
 *                  ____ ____ ____ Enter  0     .
 */
[_NUM] = LAYOUT_split_3x6_3(
  TG(_NUM), _______, _______, _______, _______, _______,    KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_BSPC,
  _______,  _______, _______, _______, _______, _______,    KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_KP_ASTERISK,
  _______,  _______, _______, _______, _______, _______,    KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_KP_SLASH,
                         _______, _______, _______,          KC_PENT, KC_P0,   KC_PDOT
),

/* ─────────────────────────── Func (F-keys) ─────────────────────
 * ____ F1   F2   F3   F4   F5     F6   F7   F8    F9    F10   __
 * ____ F11  F12  F13  F14  F15    F16  F17  F18   F19   F20   __
 * ____ ____ ____ ____ ____ ____   ____ ____ ____  ____  ____  __
 *             ____ ____ ____      ____  ____ ____
 *
 * (We’ll add BT controls later if you really need them in QMK.)
 */
[_FUNC] = LAYOUT_split_3x6_3(
  _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,        KC_F6,  KC_F7,  KC_F8,   KC_F9,  KC_F10, _______,
  _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,       KC_F16, KC_F17, KC_F18,  KC_F19, KC_F20, _______,
  _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
                         _______, _______, _______,       _______, _______, _______
),

/* ─────────────────────────── Art (Photoshop) ───────────────────
 * TG A  Q    D    E    [    ]      ____  7     8     9     __    __
 * LAlt  J    S    Bspc [    ]      ____  4     5     6     __    __
 * ____  Z    X    C    ____  B     ____  1     2     3     __    __
 *             LGUI  __  Space      Enter  0     .
 *
 * (Placeholders kept where your ZMK macros live. We’ll add them next.)
 */
[_ART] = LAYOUT_split_3x6_3(
  TG(_ART), KC_Q,   KC_D,   KC_E,   KC_LBRC, KC_RBRC,     _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
  KC_LALT,  KC_J,   KC_S,   KC_BSPC,KC_LBRC, KC_RBRC,     _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,
  _______,  KC_Z,   KC_X,   KC_C,   _______, KC_B,        _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,
                         KC_LGUI, _______, KC_SPC,        KC_ENT,  KC_P0,   KC_PDOT
),
};
