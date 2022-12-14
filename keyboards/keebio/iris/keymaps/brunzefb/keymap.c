#include QMK_KEYBOARD_H
#include "secrets.h"
#include "keymap_combo.h"

enum iris_layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define KC_ESCLK TD(TD_SHFT_CAPS)              // tap ESC  twice in a row to toggle CAPS LOCK, press and hold to get Esc
#define KC_SPLO LT(_LOWER, KC_SPACE)           // tap to get space, hold for switch to LOWER layer
#define KC_ADJU MO(_ADJUST)                    // hold to go to ADJUST layer
#define KC_COPY LGUI(KC_C)                     // cmd + c, copy
#define KC_PASTE LGUI(KC_V)                    // cmd + v, paste
#define KC_CUT LGUI(KC_X)                      // cmd + x, cut
#define KC_UNDO LGUI(KC_Z)                     // cmd + z, undo
#define KC_SALL LGUI(KC_A)                     // cmd + a, select all
#define KC_REDO LSG(KC_Z)                      // cmd + shift + Z, redo
#define KC_DUPL LSA(KC_DOWN)                   // shift+alt+down is duplicate line in VSCode
#define KC_EXPL LSG(KC_E)                      // shift+cmd+e is view explorer file tree in VScode
#define KC_CLOS LGUI(KC_W)                     // cmd+w close window
#define KC_TERM LCTL(KC_GRAVE)                 // ctrl+` is Terminal focus or toggle
#define KC_CYCLE LCTL(KC_TAB)                  // ctrl+tab is cycle editor windows in VSCode
#define KC_RASE MO(_RAISE)                     // RAISE momentary layer change
#define KC_LOWR MO(_LOWER)                     // LOWER momentary layer change
#define KC_BL LCA(KC_J)                        // Rectangle Window manager for mac (WM) Bottom left
#define KC_BH LCA(KC_DOWN)                     // WM Bottom half
#define KC_BOR LCA(KC_K)                       // WM Bottom right
#define KC_LH LCA(KC_LEFT)                     // WM Left half
#define KC_FS LCA(KC_ENTER)                    // WM Full screen
#define KC_RH LCA(KC_RIGHT)                    // WM Right half
#define KC_TL LCA(KC_U)                        // WM Top left
#define KC_TH LCA(KC_UP)                       // WM Top half
#define KC_TR LCA(KC_I)                        // WM Top right
#define KC_RTRM LAG(KC_RIGHT)                  // Focus next terminal in Group VSCode
#define KC_LTRM LAG(KC_LEFT)                   // Focus previous terminal in Group
#define KC_TRMR LGUI(LCTL(KC_RIGHT))           // Resize Terminal ->
#define KC_TRML LGUI(LCTL(KC_LEFT))            // Resize Terminal <-


#define TAPPING_TERM 200

// https://andywarburton.co.uk/fix-mac-osx-volume-keys-not-working-with-via-qmk/
#define MAC_VOLUME_UP 0x80
#define MAC_VOLUME_DOWN 0x81
#define MAC_MUTE 0x7f

#define K_VOLUP A(G(MAC_VOLUME_UP))   // any key macro
#define K_VOLDN A(G(MAC_VOLUME_DOWN))
#define K_MUTE A(G(MAC_MUTE))


enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  FIND_G, // VSCode Replace in files Shift+Cmd+H
  FIND_L, // VSCode Replace in this file Option+Cmd+F
  SIG,
  KC_OCPRN,
  KC_OCBRC,
  KC_OCCBR,
  KC_OCDQUO,
  KC_OCQUOT,
  LEFT,
  RIGHT,
  TOP,
  BOTTOM,
  PATH
};

enum custom_tapdances {
   TD_SHFT_CAPS = 0,
};

// Shift vs. capslock function. From bbaserdem's Planck keymap (since deprecated).
// Tapping left shift twice in a row enables caps lock. Doing it again disables Caps lock mode.
// Holding shift works just like normal.
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_ESC);
    } else if (state->count == 2) {
        unregister_code (KC_ESC);
        register_code (KC_CAPS);
    }
}

void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock, this is an on off toggle.
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DHm
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  ` ~   │   1!   │   2@   │   3#   │   4$   │   5%   │                     │   6^   │   7&   │   8*   │   9(   │   0)   │ Bksp   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  Tab   │   Q    │   W    │   F    │   P    │   B    │                     │   J    │   L    │   U    │   Y    │   ;:   │  -_    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  ESC   │   A    │   R    │   S    │   T    │   G    │                     │   M    │   N    │   E    │   I    │   O    │ Enter  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  Shift │   Z    │   X    │   C    │   D    │   V    │  RAlt  │   │ RAISE  │   K    │   H    │   ,<   │   .>   │   /?   │  ' "   │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ Ctrl   │ LAlt   │ Cmd/Gui│            │ LOWER  │ SPACE  │ ADJUST │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESCLK, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                          KC_M,   KC_N,     KC_E,    KC_I,     KC_O,    KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_RALT,     KC_RASE,   KC_K,   KC_H,   KC_COMM, KC_DOT,  KC_SLASH,KC_QUOT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_LALT, KC_LGUI,              KC_LOWR,   KC_SPACE,KC_ADJU
                                // └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

/* Qwerty
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  ` .   │   1!   │   2@   │   3#   │   4$   │   5%   │                     │   6^   │   7&   │   8*   │   9(   │   0)   │  Bksp  │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  Tab   │   Q    │   W    │   E    │   R    │   T    │                     │   Y    │   U    │   I    │   O    │   P    │  -_    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  Esc   │   A    │   S    │   D    │   F    │   G    │                     │   H    │   J    │   K    │   L    │  : ;   │ ENTER  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  SHIFT │   Z    │   X    │   C    │   V    │   B    │  Alt   │   │RAISE   │   N    │   M    │   ,<   │   .>   │   /?   │ " '    │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ Ctrl   │ Lalt   │ Cmd/Gui│            │ LOWER  │ Space  │ Adjust │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESCLK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RALT,     KC_RASE,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLASH,KC_OCDQUO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_LALT, KC_LGUI,              KC_LOWR, KC_SPACE,KC_ADJU
                                // └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

/* Raise
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │        │        │   F10  │   F11  │  F12   │        │                     │ PRT    │ NUMLK  │   /    │   *    │   -    │ Back   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │RGB_TOG │ RGB_MOD│   F7   │   F8   │  F9    │  Hue   │                     │ SCRLCK │   7    │   8    │   9    │   +    │   -    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │ Reset  │  Mute  │   F4   │   F5   │  F6    │  Sat   │                     │ PAUSE  │   4    │   5    │   6    │   .    │Alt+Ent │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │ VolUp  │  VolDn │   F1   │   F2   │  F3    │  Inten │        │   │        │   0    │   1    │   2    │   3    │   =    │   "    │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │            │        │        │        │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                   ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, KC_F10,  KC_F11,  KC_F12,  _______,                     KC_PSCR, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                   ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_MOD, KC_F7,   KC_F8,   KC_F9,   RGB_HUI,                      KC_SCRL, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                   ├────────┼────────┼────────┼────────┼────────┼────────┤
     QK_BOOT, K_MUTE,  KC_F4,   KC_F5,   KC_F6,   RGB_SAI,                      KC_PAUS, KC_P4,   KC_P5,   KC_P6,   KC_PDOT, LALT_T(KC_PENT),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     K_VOLUP, K_VOLDN, KC_F1,   KC_F2,   KC_F3,   RGB_VAI, _______,  , _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_DQT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘ └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,            _______, _______, _______
                                // └────────┴────────┴────────┘          └────────┴────────┴────────┘
  ),


/* Lower, Note: { ( [ " ' have hold to insert closing item after 200 mhold
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │ Explor │   !    │   @    │   #    │    $   │   %    │                    │        │ Copy   │ DupLn  │  Paste │ RepGlo   RepLoc │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
    │Terminal│   `    │   {    │   *    │    }   │   +    │                    │        │ Home   │   ↑    │  End   │ PgUp   │ Redo   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
    │   "    │   _    │   (    │   =    │    )   │   -    │                    │        │   ←    │   ↓    │   →    │PageDown│        │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │   '    │   |    │   [    │   &    │    ]   │   /?   │   \    │  │        │        │ SelAll │  Cut   │  Undo  │        │        │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
    Ctrl+tab switches editors      │        │        │        │           │        │        │        │
                                   └────────┴────────┴────────┘           └────────┴────────┴────────┘
*/
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_EXPL, KC_EXLM, KC_AMPR, KC_HASH, KC_DLR,  KC_PERC,                         _______, KC_COPY, KC_DUPL, KC_PASTE,LSG(KC_H),LAG(KC_F),
 // ├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TERM, KC_GRAVE,KC_OCCBR, KC_ASTR, KC_RCBR, KC_PLUS,                        _______, KC_HOME ,KC_UP,   KC_END,  KC_PGUP, KC_REDO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_OCDQUO,KC_UNDS,KC_OCPRN, KC_EQL,  KC_RPRN, KC_MINS,                        _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_OCQUOT,KC_PIPE, KC_OCBRC,KC_AMPR, KC_RBRC, KC_SLASH,KC_BACKSLASH,  _______, _______, KC_SALL, KC_CUT,  KC_UNDO, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘     └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                _______, _______, _______
                                   └────────┴────────┴────────┘              └────────┴────────┴────────┘
  ),

/* Adjust / WindowMgr
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │QUERTY  │ Term → │ Term ← │        │        │        │                          │<-Displ │        │        │        │        │Displ>  │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │COLEMAK │SizeTrm→│SizeTrm←│  Ed ↑  │        │        │                          │        │WTopLeft│WTopHalf│WTopHalf│        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │ Ed ←   │        │  Ed →  │        │                          │        │WLftHalf│ WMaxim │WRtHalf │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │  Ed ↓  │        │        │        │        │        │        │WBotLeft│WBotHalf│WBotRigt│        │        │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │                 │        │        │        │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QWERTY,  _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     COLEMAK, _______, _______,  TOP,    _______, _______,                       _______, KC_TL,   KC_TH,   KC_TR,   _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  LEFT,   _______,  RIGHT,  _______,                       _______, KC_LH,   KC_FS,   KC_RH,   _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     PATH,    _______, _______,  BOTTOM, _______, _______, _______,     _______, _______, KC_BL,   KC_BH,   KC_BOR,  _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,              _______, _______, _______
                                // └────────┴────────┴────────┘            └────────┴────────┴────────┘
  )
};

void handle_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t *record, uint16_t* p_hash_timer);
void handle_cursor(uint16_t keycode, uint8_t mods, bool* flag, keyrecord_t *record);
void handle_top(bool isGui, bool isAlt);
void handle_bottom(bool isGui, bool isAlt);
void handle_left(bool isGui, bool isAlt);
void handle_right(bool isGui, bool isAlt);

void handle_top(bool isGui, bool isAlt) {
  if (isGui)
    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("3"))));
  else if (isAlt) {
    tap_code16(LGUI(KC_K));
    tap_code16(LGUI(KC_DOWN));
  } else {
    tap_code16(LGUI(LCTL(KC_LEFT)));
  }
}

void handle_bottom(bool isGui, bool isAlt) {
  if (isGui)
    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("2"))));
  else if (isAlt) {
    tap_code16(LGUI(KC_K));
    tap_code16(LGUI(KC_DOWN));
  } else {
    tap_code16(LGUI(LCTL(KC_LEFT)));
  }
}

void handle_left(bool isGui, bool isAlt) {
  if (isGui)
    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("4"))));
  else if (isAlt) {
    tap_code16(LGUI(KC_K));
    tap_code16(LGUI(KC_LEFT));
  } else {
    tap_code16(LGUI(LCTL(KC_LEFT)));
  }
}

void handle_right(bool isGui, bool isAlt) {
  if (isGui)
    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("1"))));
  else if (isAlt) {
    tap_code16(LGUI(KC_K));
    tap_code16(LGUI(KC_RIGHT));
  } else {
    tap_code16(LGUI(LCTL(KC_RIGHT)));
  }
}

void handle_cursor(uint16_t keycode, uint8_t mods, bool* flag, keyrecord_t *record) {
  uint16_t kc;
  bool isColemak = default_layer_state == _COLEMAK;
  void (*f_ptr)(bool, bool);
  void (*f_ptr_top)(bool, bool) = &handle_top;
  void (*f_ptr_bottom)(bool, bool) = &handle_bottom;
  void (*f_ptr_left)(bool, bool) = &handle_left;
  void (*f_ptr_right)(bool, bool) = &handle_right;

  if (default_layer_state == _COLEMAK) {
    switch (keycode) {
      case TOP:
        kc = isColemak ? KC_F : KC_E;
        f_ptr = f_ptr_top;
        break;
      case RIGHT:
        kc = isColemak? KC_T : KC_F;
        f_ptr = f_ptr_right;
        break;
      case BOTTOM:
        kc = isColemak ? KC_C : KC_C;
        f_ptr = f_ptr_bottom;
        break;
      case LEFT:
        kc = isColemak ? KC_R : KC_S;
        f_ptr = f_ptr_left;
        break;
    }
  }
  *flag = false;
  if (record->event.pressed ) {
    clear_mods();
    (*f_ptr)(mods & MOD_MASK_GUI, mods & MOD_MASK_ALT);
    set_mods(mods);
    register_code(kc);
    *flag = true;
  }
  else {
    if (*flag) {
      unregister_code(kc);
      *flag = false;
    }
    unregister_code(kc);
  }
}

void handle_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t *record, uint16_t* p_hash_timer) {
    if(record->event.pressed) {
        *p_hash_timer = timer_read();
    } else {
        if (timer_elapsed(*p_hash_timer) < TAPPING_TERM)
            tap_code16(kc1);
        else {
            tap_code16(kc1);
            tap_code16(kc2);
            tap_code16(KC_LEFT);
        }
    }
}

// Enable the ctrl+backspace (KC_BSPC) to function as delete forward (KC_DEL)
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_hash_timer;
    mod_state = get_mods();
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_OCPRN:
            handle_openclose(KC_LPRN, KC_RPRN, record, &my_hash_timer);
            return false;
        case KC_OCBRC:
            handle_openclose(KC_LBRC, KC_RBRC, record, &my_hash_timer);
            return false;
        case KC_OCCBR:
            handle_openclose(KC_LCBR, KC_RCBR, record, &my_hash_timer);
            return false;
        case KC_OCDQUO:
            handle_openclose(KC_DQUO, KC_DQUO, record, &my_hash_timer);
            return false;
        case KC_OCQUOT:
            handle_openclose(KC_QUOT, KC_QUOT, record, &my_hash_timer);
            return false;

        case PATH:
          if (record->event.pressed){
            tap_code16(LGUI(LALT(KC_C)));
            SEND_STRING(SS_DELAY(500));
            tap_code16(LCTL(KC_GRAVE));
            tap_code16(LGUI(KC_V));

            return false;
          }
          break;
        case LEFT: {
          static bool is_left_registered = false;
          handle_cursor(LEFT, mod_state, &is_left_registered, record);
          return false;
        }
        case RIGHT: {
          static bool is_right_registered = false;
          handle_cursor(RIGHT, mod_state, &is_right_registered, record);
          return false;
        }

        case TOP:
          if (record->event.pressed){
            del_mods(MOD_MASK_GUI);
            if(mod_state & MOD_MASK_GUI)
              SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT(""))));
            else {
              SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("6")))SS_LGUI("k")); tap_code16(LGUI(KC_DOWN));
              SEND_STRING(SS_LGUI("K")); tap_code16(LGUI(KC_UP));
            }
            add_mods(MOD_BIT(KC_LGUI));
            register_code(KC_E);
          }
          else
            unregister_code(KC_E);
          return false;
        case BOTTOM:
          if (mod_state & MOD_MASK_GUI && record->event.pressed)
            SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("3"))));
          else if (record->event.pressed)
            SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("5")))SS_DELAY(50)SS_LGUI("k")); tap_code16(LGUI(KC_UP));
            SEND_STRING(("k")); tap_code16(LGUI(KC_DOWN));
          return false;
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) { // on key-down of Backspace
                if (mod_state & MOD_MASK_CTRL) {
                    // Ctrl + Backspace, or Shift + Backspace -> Forward Delete
                    if (mod_state & MOD_MASK_CTRL)
                        del_mods(MOD_MASK_CTRL);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of Backspace
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
        };

        break;
    }
    return true;
};
