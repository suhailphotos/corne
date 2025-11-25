#pragma once

// Tap-hold feel to roughly match your ZMK timings
#define TAPPING_TERM 280
#define QUICK_TAP_TERM 175
#define PERMISSIVE_HOLD

// Make combo array length flexible so we don't have to keep a hard count.
#define COMBO_VARIABLE_LEN

// --- Combos ---
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 40

// ---- Mouse ----
// Mouse key tuning (tweak later if you like)
#define MOUSEKEY_INTERVAL         16   // ms between cursor steps
#define MOUSEKEY_DELAY            0
#define MOUSEKEY_TIME_TO_MAX      200  // ramp time to max speed
#define MOUSEKEY_MAX_SPEED        7
#define MOUSEKEY_WHEEL_DELAY      0
#define MOUSEKEY_WHEEL_INTERVAL   20
#define MOUSEKEY_WHEEL_TIME_TO_MAX 200
#define MOUSEKEY_WHEEL_MAX_SPEED  8


// ---- RGB Matrix (per-key lighting) ----
#ifdef RGB_MATRIX_ENABLE
    // Cap overall brightness so it stays subdued
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120

    // Start in a single-color breathing effect
    #define ENABLE_RGB_MATRIX_BREATHING

    // Default (no-EEPROM) settings – soft white, slow breathing
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BREATHING
    #define RGB_MATRIX_DEFAULT_HUE 0    // white when saturation = 0
    #define RGB_MATRIX_DEFAULT_SAT 0
    #define RGB_MATRIX_DEFAULT_VAL 80   // brightness (0–255)
    #define RGB_MATRIX_DEFAULT_SPD 16   // breathing speed
#endif
