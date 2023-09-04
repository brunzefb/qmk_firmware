#include QMK_KEYBOARD_H
#include "secrets.h"
#include "keymap_combo.h"
#include "uthash.h"
#include "circular_buffer.c"
#include <stdio.h>

enum iris_layers {
    _COLEMAK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _UTIL
};

#define KC_SPLO LT(_LOWER, KC_SPACE) // tap to get space, hold for switch to LOWER layer
#define KC_ADJU MO(_ADJUST)          // hold to go to ADJUST layer
#define KC_COPY LGUI(KC_C)           // cmd + c, copy
#define KC_PASTE LGUI(KC_V)          // cmd + v, paste
#define KC_CUT LGUI(KC_X)            // cmd + x, cut
#define KC_UNDO LGUI(KC_Z)           // cmd + z, undo
#define KC_SALL LGUI(KC_A)           // cmd + a, select all
#define KC_REDO LSG(KC_Z)            // cmd + shift + Z, redo
#define KC_DUPL LSA(KC_DOWN)         // shift+alt+down is duplicate line in VSCode
#define KC_EXPL LSG(KC_E)            // shift+cmd+e is view explorer file tree in VScode
#define KC_CLOS LGUI(KC_W)           // cmd+w close window
#define KC_TERM LCTL(KC_GRAVE)       // ctrl+` is Terminal focus or toggle
#define KC_CYCLE LCTL(KC_TAB)        // ctrl+tab is cycle editor windows in VSCode
#define KC_RASE MO(_RAISE)           // RAISE momentary layer change
#define KC_LOWR MO(_LOWER)           // LOWER momentary layer change
#define KC_BL LCA(KC_J)              // Rectangle Window manager for mac (WM) Bottom left
#define KC_BH LCA(KC_DOWN)           // WM Bottom half
#define KC_BOR LCA(KC_K)             // WM Bottom right
#define KC_LH LCA(KC_LEFT)           // WM Left half
#define KC_FS LCA(KC_ENTER)          // WM Full screen
#define KC_RH LCA(KC_RIGHT)          // WM Right half
#define KC_TL LCA(KC_U)              // WM Top left
#define KC_TH LCA(KC_UP)             // WM Top half
#define KC_TR LCA(KC_I)              // WM Top right
#define KC_RTRM LAG(KC_RIGHT)        // Focus next terminal in Group VSCode
#define KC_LTRM LAG(KC_LEFT)         // Focus previous terminal in Group
#define KC_MTLD LCAG(KC_LEFT)        // Rectangle: move to left display
#define KC_MTRD LCAG(KC_RIGHT)       // Rectangle: move to right display
#define KC_HIRES LCAG(KC_F11)        // SwitchResX: 4K
#define KC_LORES LCAG(KC_F12)        // SwitchResX: HD Res (edit prefs to assign shortcuts)
#define KC_CPRV LCTL(KC_LBRC)        // ctrl+[ is next file in code collaborator
#define KC_CNXT LCTL(KC_RBRC)        // ctrl+] is next file in code collaborator
#define KC_REVS LCTL(KC_R)           // ctrl+R is search in terminal history

#define TAPPING_TERM 200

// https://andywarburton.co.uk/fix-mac-osx-volume-keys-not-working-with-via-qmk/
#define MAC_VOLUME_UP 0x80
#define MAC_VOLUME_DOWN 0x81
#define MAC_MUTE 0x7f

#define K_VOLUP A(G(MAC_VOLUME_UP)) // any key macro
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
    PATH,
    ALT_TAB,
    LINUX,
    COPY,
    PASTE,
    SALL,
    CUT,
    UNDO,
    REDO,
    TERMCLR,
    BOOTLOG,
    TYPE_BUF,
    LOOKUP
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak DHm
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  ESC   │   1!   │   2@   │   3#   │   4$   │   5%   │                     │   6^   │   7&   │   8*   │   9(   │   0)   │ Bksp   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  TAB   │   Q    │   W    │   F    │   P    │   B    │                     │   J    │   L    │   U    │   Y    │   ;:   │  -_    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  `~    │   A    │   R    │   S    │   T    │   G    │                     │   M    │   N    │   E    │   I    │   O    │ Enter  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  Shift │   Z    │   X    │   C    │   D    │   V    │  RAlt  │   │ RAISE  │   K    │   H    │   ,<   │   .>   │   /?   │  ' "   │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ Ctrl   │ LAlt   │ Cmd/Gui│            │ LOWER  │ SPACE  │ ADJUST │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE,KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                          KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_RALT,     TL_UPPR,  KC_K,   KC_H,    KC_COMM, KC_DOT,  KC_SLASH,KC_QUOT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_LALT, KC_LGUI,              TL_LOWR, KC_SPACE, KC_ADJU
                                // └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

/* Qwerty
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  ESC   │   1!   │   2@   │   3#   │   4$   │   5%   │                     │   6^   │   7&   │   8*   │   9(   │   0)   │  Bksp  │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  TAB   │   Q    │   W    │   E    │   R    │   T    │                     │   Y    │   U    │   I    │   O    │   P    │  -_    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  `~    │   A    │   S    │   D    │   F    │   G    │                     │   H    │   J    │   K    │   L    │  : ;   │ ENTER  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  SHIFT │   Z    │   X    │   C    │   V    │   B    │  Alt   │   │RAISE   │   N    │   M    │   ,<   │   .>   │   /?   │ " '    │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ Ctrl   │ Lalt   │ Cmd/Gui│            │ LOWER  │ Space  │ Adjust │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RALT,     KC_RASE,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLASH, KC_QUOT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_LALT, KC_LGUI,              KC_LOWR, KC_SPACE,KC_ADJU
                                // └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

/* Lower, Note: { ( [ " ' have hold to insert closing item after 200 mhold
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │ Explor │   !    │   @    │   #    │    $   │   %    │                     │ RevSrch│ CapsLk │  \ |   │  RAlt  │ RCtl   │  Rshift│
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │Terminal│   `    │   {    │   *    │    }   │   +    │                     │ DupLn  │ Copy   │   ↑    │  Paste │ RepGlo │ RepLoc │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │   "    │   _    │   (    │   =    │    )   │   -    │                     │ Home   │   ←    │   ↓    │   →    │  End   │ PgUp   │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │ Lookup │   |    │   [    │   &    │    ]   │   /?   │   \    │   │        │ Switch │ SelAll │  Cut   │  Undo  │  Redo  │ PgDown │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
    Ctrl+tab switches editors      │        │        │        │            │        │        │        │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_EXPL, KC_EXLM, KC_AMPR, KC_HASH, KC_DLR,   KC_PERC,                        KC_REVS, KC_CAPS, KC_BSLS, KC_RALT, KC_RCTL,  KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TERM, KC_GRAVE,KC_OCCBR, KC_ASTR, KC_RCBR, KC_PLUS,                        KC_DUPL, COPY,    KC_UP,   PASTE,  LSG(KC_H),LAG(KC_F),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_OCDQUO,KC_UNDS,KC_OCPRN, KC_EQL,  KC_RPRN, KC_MINS,                        KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_PGUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LOOKUP,  KC_PIPE, KC_OCBRC,KC_AMPR, KC_RBRC, KC_SLASH,KC_BACKSLASH,  _______, ALT_TAB, SALL,    CUT,     UNDO,     REDO,   KC_PGDN,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘     └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                _______, _______, _______
  //                               └────────┴────────┴────────┘              └────────┴────────┴────────┘
  ),

/* Raise
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │ VolUp  │ VolDown│   F10  │   F11  │  F12   │        │                     │ PRT    │ NUMLK  │   /    │   *    │   -    │ Back   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │RGB_TOG │ RGB_MOD│   F7   │   F8   │  F9    │  Hue   │                     │ SCRLCK │   7    │   8    │   9    │   +    │   -    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │ Reset  │ Mute   │   F4   │   F5   │  F6    │  Sat   │                     │CLEAR T │   4    │   5    │   6    │   .    │Alt+Ent │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │ Shift  │        │   F1   │   F2   │  F3    │  Inten │        │   │        │   0    │   1    │   2    │   3    │   =    │   "    │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │            │        │        │        │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     K_VOLUP, K_VOLDN, KC_F10,  KC_F11,  KC_F12,  _______,                       KC_PSCR, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_MOD, KC_F7,   KC_F8,   KC_F9,   RGB_HUI,                       KC_SCRL, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     QK_BOOT, K_MUTE,  KC_F4,   KC_F5,   KC_F6,   RGB_SAI,                       TERMCLR, KC_P4,   KC_P5,   KC_P6,   KC_PDOT, LALT_T(KC_PENT),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, _______, KC_F1,   KC_F2,   KC_F3,   RGB_VAI, _______,     _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_DQT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,              _______, _______, _______
  //                               └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

/* Adjust / WindowMgr
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │QUERTY  │LtMouBtn│RtMouBtn│MouseUp  MWheelUp│MWheelDw│                     │<-Displ │  Help  │   =    │ LowRes │ HiRes  │Displ-> │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │COLEMAK │        │MouseL  │  Ed ↑  │MouseR  │        │                     │MissCtl │WTopLeft│WTopHalf│WTopHalf│        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │IsLinux │TYPE_BUF│ Ed ←   │MouseDwn│  Ed →  │        │                     │        │WLftHalf│ WMaxim │WRtHalf │ mouse1 │ mouse2 │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │ Path   │BOOTLOG │        │  Ed ↓  │        │        │  Menu  │   │        │        │WBotLeft│WBotHalf│WBotRigt│ Cprev  │ Cnext  │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │            │        │        │        │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QWERTY,  KC_BTN1, KC_BTN2, KC_MS_U, KC_WH_U, KC_WH_D,                       KC_MTLD, KC_HELP, KC_PEQL, KC_LORES,KC_HIRES,KC_MTRD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     COLEMAK, AC_TOGG, KC_MS_LEFT,TOP,   KC_MS_RIGHT, _______,                   KC_MCTL,  KC_TL,   KC_TH,   KC_TR,  _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     LINUX,   TYPE_BUF, LEFT,    KC_MS_DOWN,RIGHT, _______,                       _______, KC_LH,   KC_FS,   KC_RH,   KC_BTN1, KC_BTN2,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     PATH,    BOOTLOG, _______, BOTTOM,  _______, KC_MENU, _______,     _______, _______, KC_BL,   KC_BH,   KC_BOR,  KC_CPRV, KC_CNXT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,              _______, _______, _______
  //                               └────────┴────────┴────────┘            └────────┴────────┴────────┘
  ),

  /* Util
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │QUERTY  │LtMouBtn│RtMouBtn│MouseUp  MWheelUp│MWheelDw│                     │<-Displ │  Help  │   =    │ LowRes │ HiRes  │Displ-> │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │COLEMAK │        │MouseL  │  Ed ↑  │MouseR  │        │                     │MissCtl │WTopLeft│WTopHalf│WTopHalf│        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
    │IsLinux │TYPE_BUF│ Ed ←   │MouseDwn│  Ed →  │        │                     │        │WLftHalf│ WMaxim │WRtHalf │ mouse1 │ mouse2 │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │  Ed ↓  │        │        │  Menu  │   │        │        │WBotLeft│WBotHalf│WBotRigt│ Cprev  │ Cnext  │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │            │        │        │        │
                                   └────────┴────────┴────────┘            └────────┴────────┴────────┘
*/
  [_UTIL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______,_______,  _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐   ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______,  _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,              _______, _______, _______
  //                               └────────┴────────┴────────┘            └────────┴────────┴────────┘
  )
};

CircularBuffer cbuff;
struct lookup {
    char           key[30];
    char           value[256];
    UT_hash_handle hh;
};
struct lookup* lookups = NULL;

void           handle_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t* record, uint16_t* p_hash_timer);
void           handle_cursor(uint16_t keycode, uint8_t mods, bool* flag, keyrecord_t* record);
uint16_t       key_to_keycode_for_default_layer(int key);
void           add_lookup_item(char* key, char* value);
struct lookup* find_lookup_item(char* key);
void           show_all_keys(void);


void keyboard_post_init_user(void) {
    InitializeBuffer(&cbuff);
    add_lookup_item("sig", REGARDS);
    add_lookup_item("smail", EMAIL);
    add_lookup_item("gmail", GMAIL);
    add_lookup_item("spw", NETADDS_PW);
    add_lookup_item("supw", NETADDS_EMAIL);
    add_lookup_item("ssupw", NETADDS_USER);
    add_lookup_item("napc", COLLABORATOR);
    add_lookup_item("conf", CONFLUENCE);
    add_lookup_item("jira", JIRA);
    add_lookup_item("jenk", JENKINS);
}

void add_lookup_item(char* key, char* value) {
    struct lookup* lookup_entry;
    lookup_entry = malloc(sizeof(struct lookup));
    strncpy(lookup_entry->key, key, sizeof(lookup_entry->key) - 1);
    lookup_entry->key[sizeof(lookup_entry->key) - 1] = '\0';
    strncpy(lookup_entry->value, value, sizeof(lookup_entry->value) - 1);
    lookup_entry->value[sizeof(lookup_entry->value) - 1] = '\0';
    HASH_ADD_STR(lookups, key, lookup_entry);
}

void show_all_keys(void) {
    struct lookup *s;
    char buffer[256];
    SEND_STRING("Keys:\n");
    for (s = lookups; s != NULL; s = s->hh.next) {
        snprintf(buffer, sizeof(buffer), "Key %s=%s\n", s->key, s->value);
        SEND_STRING(buffer);
    }
}

struct lookup* find_lookup_item(char* key) {
    struct lookup* lookup_entry;
    HASH_FIND_STR(lookups, key, lookup_entry);
    return lookup_entry;
}

uint16_t key_to_keycode_for_default_layer(int key) {
    bool     isColemak = default_layer_state == _COLEMAK;
    uint16_t kc;
    switch (key) {
        case TOP:
            kc = isColemak ? KC_F : KC_E;
            break;
        case RIGHT:
            kc = isColemak ? KC_T : KC_F;
            break;
        case BOTTOM:
            kc = isColemak ? KC_C : KC_C;
            break;
        case LEFT:
            kc = isColemak ? KC_R : KC_S;
            break;
        case PATH:
            kc = isColemak ? KC_LSFT : KC_LSFT;
            break;
        default:
            kc = -1;
    }
    return kc;
}

void handle_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t* record, uint16_t* p_hash_timer) {
    if (record->event.pressed) {
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

// handle auto-enable of numlock
void led_set_keymap(uint8_t usb_led) {
    if (!(usb_led & (1 << USB_LED_NUM_LOCK))) {
        register_code(KC_NUM_LOCK);
        unregister_code(KC_NUM_LOCK);
    }
}

// Enable the ctrl+backspace (KC_BSPC) to function as delete forward (KC_DEL)
// also enables ctrl+alt+del on windows via ctrl+alt+backspace
uint8_t mod_state;
bool    process_record_user(uint16_t keycode, keyrecord_t* record) {
    static uint16_t my_hash_timer;
    static bool     isLinux      = false;
    static bool     isLookupMode = false;
    static char     buffer[BUFFER_SIZE];
    struct lookup*  lookup_entry;
    mod_state = get_mods();
    switch (keycode) {
        case LOOKUP: {
            if (record->event.pressed) {
                isLookupMode = true;
                InitializeBuffer(&cbuff);
                return false;
            }
        }
        case BOOTLOG:
            if (record->event.pressed) {
                send_string_with_delay(DESKTOP_LOGIN, 100);
            }
            return false;
        case LINUX:
            if (record->event.pressed) {
                isLinux = !isLinux;
            }
            return false;
        case COPY:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_C));
                } else {
                    tap_code16(LGUI(KC_C));
                }
                return false;
            }
        case PASTE:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_V));
                } else {
                    tap_code16(LGUI(KC_V));
                }
                return false;
            }
        case CUT:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_X));
                } else {
                    tap_code16(LGUI(KC_X));
                }
                return false;
            }
        case UNDO:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_Z));
                } else {
                    tap_code16(LGUI(KC_Z));
                }
                return false;
            }
        case REDO:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_Y));
                } else {
                    tap_code16(LSG(KC_Z));
                }
                return false;
            }
        case SALL:
            if (record->event.pressed) {
                if (isLinux) {
                    tap_code16(LCTL(KC_A));
                } else {
                    tap_code16(LGUI(KC_A));
                }
                return false;
            }
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
            handle_openclose(KC_DQUO, KC_QUOT, record, &my_hash_timer);
            return false;
        case KC_OCQUOT:
            handle_openclose(KC_QUOT, KC_QUOT, record, &my_hash_timer);
        case KC_PIPE:
            if (record->event.pressed) {
                tap_code16(KC_PIPE);
                return false;
            }
        case PATH: {
            static bool path_registered;
            if (record->event.pressed) {
                tap_code16(LGUI(LALT(KC_C)));
                SEND_STRING(SS_DELAY(500));
                tap_code16(LCTL(KC_GRAVE));
                tap_code16(LGUI(KC_V));
                SEND_STRING(SS_DELAY(500));
                tap_code16(KC_ENTER);
                path_registered = true;
                return false;
            } else {
                if (path_registered) {
                    unregister_code(key_to_keycode_for_default_layer(PATH));
                    path_registered = false;
                    return false;
                }
            }
            return true;
        }
        case LEFT: {
            static bool left_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_GUI) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("-"))));
                    set_mods(mod_state);
                } else if (mod_state & MOD_MASK_CTRL) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("4"))));
                    set_mods(mod_state);
                } else
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("8"))));
                left_registered = true;
                return false;
            } else {
                if (left_registered) {
                    unregister_code(key_to_keycode_for_default_layer(LEFT));
                    left_registered = false;
                    return false;
                }
            }
            return true;
        }
        case RIGHT: {
            static bool right_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_GUI) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("="))));
                    set_mods(mod_state);
                } else if (mod_state & MOD_MASK_CTRL) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("1"))));
                    set_mods(mod_state);
                } else
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("7"))));
                right_registered = true;
                return false;
            } else {
                if (right_registered) {
                    unregister_code(key_to_keycode_for_default_layer(BOTTOM));
                    right_registered = false;
                    return false;
                }
            }
            return true;
        }
        case TOP: {
            static bool top_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_GUI) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("["))));
                    set_mods(mod_state);
                } else if (mod_state & MOD_MASK_CTRL) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("3"))));
                    set_mods(mod_state);
                } else
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("0"))));
                top_registered = true;
                return false;
            } else {
                if (top_registered) {
                    unregister_code(key_to_keycode_for_default_layer(TOP));
                    top_registered = false;
                    return false;
                }
            }
            return true;
        }
        case BOTTOM: {
            static bool bottom_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_GUI) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("]"))));
                    set_mods(mod_state);
                } else if (mod_state & MOD_MASK_CTRL) {
                    clear_mods();
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("2"))));
                    set_mods(mod_state);
                } else
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT("9"))));
                bottom_registered = true;
                return false;
            } else {
                if (bottom_registered) {
                    unregister_code(key_to_keycode_for_default_layer(TOP));
                    bottom_registered = false;
                    return false;
                }
            }
            return true;
        }
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_CTRL) {
                    del_mods(MOD_MASK_CTRL);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                } else if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }

            } else {
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
        }
        case TERMCLR: {
            static bool trm_registered;
            if (record->event.pressed) {
                tap_code16(LGUI(KC_K));
                SEND_STRING(SS_DELAY(20));
                tap_code16(LGUI(KC_V));
                trm_registered = true;
                return false;
            } else {
                if (trm_registered) {
                    unregister_code(key_to_keycode_for_default_layer(TERMCLR));
                    trm_registered = false;
                    return false;
                }
            }
        }
        case ALT_TAB: {
            if (record->event.pressed) {
                set_mods(MOD_MASK_GUI);
                tap_code16(KC_TAB);
            } else {
                clear_mods();
            }
            return false;
        }
        case TYPE_BUF: {
            if (record->event.pressed) {
                TypeBuffer(&cbuff);
            }
            return false;
        }
        default: {
            if (record->event.pressed) {
                // get out of lookup mode
                if (keycode == KC_ESC && isLookupMode) {
                    isLookupMode = false;
                    return false;
                }

                // if not enter, just remember the key, anc do not display
                if (isLookupMode && keycode != KC_ENTER) {
                    AddKeystroke(&cbuff, keycode);
                    return false;
                }

                // if enter, lookup the key
                if (isLookupMode && keycode == KC_ENTER) {
                    GetBuffer(&cbuff, buffer, BUFFER_SIZE);
                    if (strncmp(buffer, "ls", 2) == 0) {
                        show_all_keys();
                        isLookupMode = false;
                        return false;
                    }
                    lookup_entry = find_lookup_item(buffer);

                    // handle the error if the key was not found
                    if (lookup_entry == NULL) {
                        SEND_STRING(":-(");
                        SEND_STRING(SS_DELAY(500));
                        for (int i = 0; i < 3; i++) {
                            tap_code16(KC_BSPC);
                        }
                    } else {
                        SEND_STRING(lookup_entry->value);
                    }
                    isLookupMode = false;
                    return false;
                }
            }
        }

    } // end switch
    return true;
};
