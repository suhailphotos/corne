# Corne + Unicorne firmware — Lyra (ZMK) & Kite (QMK)

This repo hosts two tightly-related keyboard firmwares that share the same mental model:

- **Lyra** — Wireless **Corne / CRKBD** running **ZMK**, with nice!nano v2 + nice!view.
- **Kite** — Wired **Boardsource Unicorne** running **QMK**, mirroring Lyra’s layers and macros.

Both are tuned for a macOS workflow: Spotlight buckets, Neovim splits, Photoshop helpers, screenshot macros, media keys, and a one‑hand mouse layer.

---

## Firmware targets

### Lyra — Corne (ZMK)

- Split: **Corne / CRKBD (42 keys)**
- Controllers: **nice!nano v2** (left + right)
- Displays: **nice!view** (via `nice_view_adapter` on both halves)
- Firmware: **ZMK v0.3**
- Extras:
  - ZMK Studio enabled for live keymap updates
  - ZMK pointing enabled (mouse layer)
  - Bluetooth multi‑device selection
  - Hold‑tap behavior tuned for chording

### Kite — Boardsource Unicorne (QMK)

- Board: **Boardsource Unicorne**
- Firmware: **QMK**
- Extras:
  - Per‑key **RGB matrix** with per‑layer colors and role‑based accents
  - Combos for terminal splits, Neovim window management, Photoshop “Stamp Visible”, and a holdable Option combo
  - Mouse keys for basic pointer control
  - Tap/hold tuning chosen to feel close to Lyra (ZMK)

Kite is effectively the “desk‑bound sibling” of Lyra: same layers, same mental model, different physical board and firmware stack.

---

## Downloading firmware

The easiest way to get both firmwares is via the **combined bundle** built by GitHub Actions.

1. Go to the repo’s **Releases** page.
2. Download the latest **`corne-firmware-*.zip`**.
3. Inside the zip you’ll find:

   ```text
   corne-firmware/
     qmk/   # Firmware for Boardsource Unicorne (Kite, QMK)
     zmk/   # Firmware for Corne / Lyra (ZMK build output)
   ```

Each folder contains the relevant UF2/HEX/ZIP files produced by CI for that version.

> The README inside the repo is version‑agnostic; the Releases page is the source of truth for “current” firmware.

---

## Repo layout

```text
.
├── build.yaml                   # ZMK build matrix (Corne left/right + nice!view)
├── config/
│   ├── corne.keymap             # Lyra (ZMK) keymap, behaviors, combos, layers
│   ├── corne.conf               # ZMK settings (pointing, Studio, debounce, BT name)
│   └── west.yml                 # ZMK manifest pin (v0.3)
├── qmk/
│   └── keyboards/
│       └── boardsource/
│           └── unicorne/
│               └── keymaps/
│                   └── suhail/
│                       ├── config.h   # Tap/hold, combo term, mouse tuning, RGB timeout
│                       ├── keymap.c   # Kite (QMK) layers, macros, combos, RGB logic
│                       └── rules.mk   # QMK feature flags (combos, mousekeys, RGB matrix)
└── .github/
    └── workflows/
        ├── build-lyra.yml            # CI build for Lyra (ZMK, Corne)
        ├── build-kite.yml            # CI build for Kite (QMK, Unicorne)
        └── build-corne-bundle.yml    # Builds both and zips them into corne-firmware/*.zip
```

- The **Lyra** pipeline uses the official `zmkfirmware/zmk` reusable workflow.
- The **Kite** pipeline uses the official QMK CLI container to build firmware from `qmk/`.
- The **bundle** workflow runs both and packages their artifacts into one zip for releases.

---

## Lyra (ZMK Corne) — layout & features

Lyra is the original layout this repo was built around: a stock‑ish QWERTY base with extended layers for numbers, symbols, numpad, function keys, and a one‑hand mouse layer.

### High‑level layers

- **Base**: plain **QWERTY**; home‑row mods planned; left `TAB` is a hold‑tap with a Shift‑hold flavor for easy chording.
- **Lower**: numbers `1–0`, H/J/K/L arrows, Bluetooth select/clear, and media controls.
- **Raise**: coding symbols (`()[]{}` and friends) arranged in visually‑paired columns.
- **Num**: right‑hand numpad + Home/End/Page cluster.
- **Func**: F1–F20 + Bluetooth management.
- **Mouse**: one‑hand mouse layer on the right half: pointer move, scroll, and clicks.
- **Art**: Photoshop‑centric layer (brush size, selection hide, opacity/flow via number row).

All of these are described in `config/corne.keymap`. The following diagrams are an approximate view of the keymap; for exact details, always refer to the keymap file.

### Base
```text
|  ESC |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U  |  I  |  O  |  P  | BKSP |
| TAB* |  A  |  S  |  D  |  F  |  G  |   |  H  |  J  |  K  |  L  |  ;  |  '   |
| CTRL |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M  |  ,  |  .  |  /  | RSHF |
               | GUI | LWR | SPC |   | ENT | RSE | ALT |
(* TAB key is a hold‑tap; hold = Shift, tap = Tab)
```

### Lower (1)
```text
| GRV  |  1  |  2  |  3  |  4  |  5  |   |  6  |  7  |  8  |  9  |  0  | MINUS |
| TRNS |  6  |  7  |  8  |  9  |  0  |   | LFT | DWN |  UP | RGT |  /  |  *    |
| ART* | NUM*| MSE*| SPOT| APP | SS  |   | PREV| VOL-| VOL+| NEXT| MUTE| PLAY  |
               | GUI | TRN | SPC |   | ENT | FUNC| ALT |
(* numeric layers + mouse toggles live here)
```

### Raise (2)
```text
|  ~   |  !  |  @  |  #  |  $  |  %  |   |  ^  |  &  |  *  |  (  |  )  |  _   |
|  `   |  |  |  ~  |  -  |  "  |  +  |   |  {  |  }  |  (  |  )  |  :  |  "   |
| CAPS |  \  |  `  |  _  |  '  |  =  |   |  [  |  ]  |  <  |  >  |  ?  | TRNS |
               | GUI | TRN | SPC |   | ENT | TRN | ALT |
```

### Num (3)
```text
| TOG3 |     |     |     |     |     |   | HOME|  7  |  8  |  9  |  -  | BKSP |
| TRNS |     |     |     |     |     |   | PGUP|  4  |  5  |  6  |  +  |  *   |
| TRNS |     |     |     |     |     |   | PGDN|  1  |  2  |  3  |  =  |  /   |
               | TRN | TRN | TRN |   | ENT |  0  |  .  |
```

### Func (4)
```text
| TRNS | F1  | F2  | F3  | F4  | F5  |   | F6  | F7  | F8  | F9  | F10 | TRNS |
| TRNS | F11 | F12 | F13 | F14 | F15 |   | F16 | F17 | F18 | F19 | F20 | TRNS |
| BTCLR| BT0 | BT1 | BT2 | BT3 | BT4 |   | BTA | BTB | BTC | BTD | BTE | BT*  |
               | TRN | TRN | TRN |   | TRN | TRN | TRN |
```

### Mouse (5)
```text
| TOG5 |     |     |     |     |     |   | WHL-L | WHL-D | WHL-U | WHL-R |     | TRNS |
| TRNS |     |     |     |     |     |   | M-L   | M-DN  | M-UP  | M-R   |     |     |
| TRNS |     |     |     |     |     |   | MB4   | MB5   |       |       |     | TRNS|
               | TRN | TRN | TRN |   | LCLK | RCLK | MCLK |
```

(The **Art** layer mirrors these ideas but is tuned for Photoshop: brush size on brackets, hide selection, and numeric opacity/flow on the right.)

---

## Kite (QMK Unicorne) — layout & features

Kite is configured in `qmk/keyboards/boardsource/unicorne/keymaps/suhail/`.

### Highlights

- Layers: `_BASE`, `_LOWER`, `_RAISE`, `_NUM`, `_FUNC`, `_MOUSE`, `_ART`
- Macros:
  - Spotlight buckets (Cmd+Space + Cmd+1/2/3/4)
  - Screenshot helpers (full, region, window, clipboard variants)
  - Photoshop helpers (hide selection, Stamp Visible)
- Combos:
  - Right‑hand combos on Raise for terminal splits (Ghostty/iTerm):
    - H+J → Cmd+Ctrl+X (close surface)
    - J+K → Cmd+Ctrl+Backslash (vertical split)
    - K+L → Cmd+Ctrl+Minus (horizontal split)
  - Left‑hand combos on Raise for Neovim:
    - S+D → `<C-w> s`
    - D+F → `<C-w> v`
    - F+G → `<C-w> c`
  - Base/Art combos:
    - Z+X → holdable Left Option (for ⌥‑drag)
    - Q+W+E / Q+D+E → Photoshop Stamp Visible

### RGB matrix behavior

`keymap.c` contains a custom `rgb_matrix_indicators_advanced_user` implementation that:

- Chooses a **base color per layer** (Base/Lower/Raise/Num/Mouse/Art).
- Adds **role‑based accents**:
  - Ctrl, GUI, Alt/Option, Shift
  - Space, Enter, Esc, Backspace
  - Layer‑tap keys that lead to Lower/Raise
- Resolves **effective keycode** per physical key, so colors follow transparent keys correctly across layers.

This makes the Unicorne visually mirror the logical model of Lyra: you can glance at the board to see the active layer and where important modifiers live.

---

## Build & flash

### CI (recommended for firmware)

This repo uses three GitHub Actions workflows:

- `build-lyra.yml` — builds **Lyra** (ZMK Corne) using the official ZMK reusable workflow.
- `build-kite.yml` — builds **Kite** (QMK Unicorne) using the official QMK CLI container.
- `build-corne-bundle.yml` — runs both builds and packages artifacts as `corne-firmware-*.zip`.

For typical use:

1. Update the keymaps/configs on `main`.
2. From the Actions tab, run **“Build Corne Firmware Bundle (Lyra + Kite)”** against the ref you care about (usually `main` or a version tag).
3. Download the `corne-firmware-bundle` artifact (the combined zip).
4. Attach that zip to a GitHub Release for long‑term use.

### Flashing Lyra (ZMK Corne)

High‑level steps (actual filenames depend on the build):

1. Put each **nice!nano v2** half into UF2 bootloader mode.
2. Copy the corresponding UF2 from `corne-firmware/zmk/` to each half.
3. Re‑pair Bluetooth on macOS if you changed HID configuration (e.g., enabling pointing).

### Flashing Kite (QMK Unicorne)

1. Put the Unicorne into its bootloader (per Boardsource docs; typically a reset button or key combo).
2. Use QMK Toolbox or your OS UF2/HEX flashing method to flash the file in `corne-firmware/qmk/`.
3. Unplug/replug if needed, verify layers and macros are working as expected.

---

## Local builds (optional)

You can also build locally if you want to iterate without pushing:

- **ZMK**: use the `west.yml` manifest in `config/` and follow the ZMK docs for building a user config.
- **QMK**: clone `qmk/qmk_firmware`, copy `qmk/keyboards` into its `keyboards/`, and run `qmk compile -kb boardsource/unicorne -km suhail`.

The CI workflows are essentially scripted versions of those steps.

---

## ZMK Studio

Lyra enables ZMK Studio live updates in `corne.conf`:

```ini
CONFIG_ZMK_STUDIO=y
CONFIG_ZMK_STUDIO_LOCKING=n
```

You can use Studio to experiment with key positions, then fold stable changes back into `config/corne.keymap`.

---

## Troubleshooting notes

- **Pointing not working (Lyra)**:
  - Confirm `CONFIG_ZMK_POINTING=y` in `corne.conf`.
  - Re‑pair the keyboard on macOS after changing HID configuration.
  - Test over USB to rule out BLE quirks.

- **Tap/hold feel mismatch (Lyra vs Kite)**:
  - ZMK: adjust `tapping-term-ms` and `quick-tap-ms` in the `HM` behavior in `corne.keymap`.
  - QMK: adjust `TAPPING_TERM`, `QUICK_TAP_TERM`, and related settings in `config.h`.

- **Combos not firing (Kite)**:
  - Check `COMBO_ENABLE = yes` in `rules.mk`.
  - Verify `COMBO_TERM` in `config.h` is short enough for how you chord.

---

## License

- Layouts, configs, and code in this repo are provided under the MIT license unless noted otherwise.
- ZMK and QMK themselves are licensed under their respective upstream terms.

