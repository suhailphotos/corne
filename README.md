# Corne (nice!nano v2) — ZMK Keymap

QWERTY base with **Lower** (numbers/BT/arrows), **Raise** (symbols), **Num** (right-hand numpad + nav), **Func** (F-keys), and a **Mouse** layer you can toggle for one-hand pointer control. Optimized for macOS media keys and a near‑stock QWERTY feel.

test
---

## Hardware

- Split: **Corne / CRKBD (42 keys)**
- Controllers: **nice!nano v2**
- Displays: **nice!view** (via `nice_view_adapter`)
- Firmware: **ZMK v0.3**

## Repo layout

```
/config
  ├── corne.keymap   # keymap & behaviors
  ├── corne.conf     # board/app config (pointing, studio, debounce)
  └── west.yml       # ZMK manifest pin
build.yaml            # GitHub Actions matrix (left/right + nice!view)
```

## Features

- **Base**: plain QWERTY; left `TAB` is a hold‑tap (`hold=Shift`, `tap=Tab`) for easy chording.
- **Lower**: `1–0`, H/J/K/L arrows, Bluetooth select/clear, and **media** controls (Prev/Play/Next/Mute/Vol±).
- **Raise**: symbols arranged for coding comfort (open/close bracket columns; `\ |` next to `= +`).
- **Num**: right‑hand numpad plus Home/End/Page cluster.
- **Func**: F1–F12.
- **Mouse**: toggle a one‑hand mouse layer; pointer move/scroll on right keys; clicks on right thumbs.

## Layer access

- **Lower**: hold **`&mo 1`** (left thumb)
- **Raise**: hold **`&mo 2`** (right thumb)
- **Num**: from Lower, **tap `&tog 3`** to latch/unlatch
- **Func**: from Lower, **hold `&mo 4`**
- **Mouse**: from Lower, **tap `&tog 5`** to latch; exit with `&tog 5` on Mouse layer

---

## Layer diagrams (ASCII)

> These match `config/corne.keymap` exactly.

### Base
```
|  ESC |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U  |  I  |  O  |  P  | BKSP |
| TAB* |  A  |  S  |  D  |  F  |  G  |   |  H  |  J  |  K  |  L  |  ;  |  '   |
| CTRL |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M  |  ,  |  .  |  /  | RSHF |
               | GUI | LWR | SPC |   | ENT | RSE | ALT |
(* hold = Shift)
```

### Lower (1)
```
| MOUSE|  1  |  2  |  3  |  4  |  5  |   |  6  |  7  |  8  |  9  |  0  | BKSP |
|  NUM | BT1 | BT2 | BT3 | BT4 | BT5 |   | LFT | DWN |  UP | RGT |     |      |
| SHFT | BCLR|     |     |     |     |   | PREV| P/P | NEXT| MUTE| VOL-| VOL+ |
               | GUI |     | SPC |   | ENT | FUNC| ALT |
```

### Raise (2)
```
|  OPT |  !  |  @  |  #  |  $  |  %  |   |  ^  |  &  |  *  |  (  |  )  | BKSP |
| SHFT |     |     |     |     |     |   |  -  |  =  |  \  |  {  |  }  |  `   |
|      |     |     |     |     |     |   |  _  |  +  |  |  |  [  |  ]  |  ~   |
               | GUI |     | SPC |   | ENT |     | ALT |
```

### Num (3)
```
|      |     |     |     |     |     |   |  7  |  8  |  9  |  /  | HOME| PG↑  |
|      |     |     |     |     |     |   |  4  |  5  |  6  |  *  | DEL | PG↓  |
|      |     |     |     |     |     |   |  1  |  2  |  3  |  -  | END | RET  |
               |     |     |     |   |  0  |  .  |  +  |
```

### Func (4)
```
|      | F1  | F2  | F3  | F4  | F5  |   | F6  | F7  | F8  | F9  | F10 |      |
|      | F11 | F12 |     |     |     |   |     |     |     |     |     |      |
|      |     |     |     |     |     |   |     |     |     |     |     |      |
               |     |     |     |   |     |     |     |
```

### Mouse (5)
```
|      |     |     |     |     |     |   |     | S-L | M-UP| S-R |     |      |
|      |     |     |     |     |     |   |     | M-L | M-DN| M-R |     |      |
|      |     |     |     |     |     |   | MB4 | MB5 | S-UP| S-DN|     | TOG5 |
               |     |     |     |   | LCLK| RCLK| MCLK|
```

---

## Build & flash

### GitHub Actions (recommended)
This repo includes a matrix in `build.yaml` that builds:
- Left half: `nice_nano_v2 + corne_left + nice_view_adapter + nice_view`
- Right half: `nice_nano_v2 + corne_right + nice_view_adapter + nice_view`

Push to your repo; download the split UF2s from the Actions run.

### Local build (optional)
Use the ZMK west workflow if you prefer building locally.

### Pairing tip
When you first enable pointing (`CONFIG_ZMK_POINTING=y`), remove the old BLE device entry from macOS and re‑pair so the new HID report is recognized.

---

## ZMK Studio
Studio live updates are enabled:
```ini
CONFIG_ZMK_STUDIO=y
CONFIG_ZMK_STUDIO_LOCKING=n
```

---

## Notes & tokens
- If the Keymap Editor complains about long names, use ZMK short tokens: `SEMI`, `BSLH`, `LBRC/RBRC`, `LBKT/RBKT`, `C_VOL_DN/UP`, `C_PREV`.
- Media keys use Consumer controls (work well on macOS).
- Mouse layer uses ZMK pointing (`&mmv`, `&msc`, `&mkp`).

---

## Troubleshooting
- **Pointing not working**: confirm `CONFIG_ZMK_POINTING=y`, re‑pair BLE, then test over USB.
- **Weird tap/hold**: adjust `tapping-term-ms` or `quick-tap-ms` in `HM` behavior.
- **Missed arrows/symbols**: remember Lower/Raise are **momentary holds**, while Num/Mouse are **toggles** from Lower.

---

*License: MIT (matches ZMK examples; adjust if needed).*
