#pragma once

// Tap/hold feel (tuned to your ZMK-ish numbers)
#define TAPPING_TERM 280
#define QUICK_TAP_TERM 175

// Bias toward "hold" when you chord, similar to ZMK hold-preferred
#define HOLD_ON_OTHER_KEY_PRESS
#define IGNORE_MOD_TAP_INTERRUPT
// If you want even stronger bias, uncomment next line later:
// #define TAPPING_FORCE_HOLD
