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

// ---- RGB behavior ----
// Turn off RGB after 3 minutes of no keypress.
// (0 = never time out; here we pick 180000 ms = 3 minutes.)
#ifdef RGB_MATRIX_TIMEOUT
#    undef RGB_MATRIX_TIMEOUT
#endif
#define RGB_MATRIX_TIMEOUT 180000

// Turn off RGB when the host sleeps / USB suspended
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
