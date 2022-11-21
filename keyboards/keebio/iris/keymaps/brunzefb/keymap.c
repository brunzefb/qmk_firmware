#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _QUERTY 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4
#define KC_SHLK TD(TD_SHFT_CAPS)
#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QUERTY,
  LOWER,
  RAISE,
  ADJUST,
};

enum custom_tapdances {
   TD_SHFT_CAPS = 0,
};

// Shift vs. capslock function. From bbaserdem's Planck keymap (since deprecated).
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
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
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak DHm
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  Esc   │   1!   │   2@   │   3#   │   4$   │   5%   │                          │   6^   │   7&   │   8*   │   9(   │   0)   │ Bksp   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  Tab   │   Q    │   W    │   F    │   P    │   B    │                          │   J    │   L    │   U    │   Y    │   ;:   │  |\    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  ` .   │   A    │   R    │   S    │   T    │   G    │                          │   M    │   N    │   E    │   I    │   O    │   " '  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  Ctrl  │   Z    │   X    │   C    │   D    │   V    │  Alt   │        │ Querty │   K    │   H    │   ,<   │   .>   │   /?   │ Enter  │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ cmd    │ Shift  │MO-LOWER│                 │MO-RAISE│ Space  │ cmd    │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LALT,       TO(_QUERTY), KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH, KC_ENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_SHLK, KC_LOWR,                   KC_RASE,  KC_SPC, KC_RGUI
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

/* Querty
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │  Esc   │   1!   │   2@   │   3#   │   4$   │   5%   │                          │   6^   │   7&   │   8*   │   9(   │   0)   │  Bksp  │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  Tab   │   Q    │   W    │   E    │   R    │   T    │                          │   Y    │   U    │   I    │   O    │   P    │  |\    │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │   `    │   A    │   S    │   D    │   F    │   G    │                          │   H    │   J    │   K    │   L    │  : ;   │   " '  │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │  Ctrl  │   Z    │   X    │   C    │   V    │   B    │  Alt   │        │Colemak │   N    │   M    │   ,<   │   .>   │   /?   │ Enter  │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │ cmd    │ Shift  │MO-LOWER│                 │MO-RAISE│ Space  │ cmd    │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_QUERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,      TO(_COLEMAK), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_ENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_SHLK, KC_LOWR,                   KC_RASE,  KC_SPC, KC_RGUI
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

/* Lower
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │   F1   │   F2   │   F3   │   F4   │  F5    │  F6    │                          │  F7    │   F8   │   F9   │  F10   │  F11   │  F12   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │                          │        │   7    │   8    │   9    │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │                          │        │   4    │   5    │   6    │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │        │        │        │        │   1    │   2    │   3    │        │        │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │                 │        │   0    │        │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
 // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_7,    KC_8,    KC_9,    _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_4,    KC_5,    KC_6,    _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,  _______,         _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______,  KC_0,   _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


/* Raise
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │   F1   │   F2   │   F3   │   F4   │  F5    │  F6    │                          │  F7    │   F8   │   F9   │  F10   │  F11   │  F12   │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │  RGB   │        │        │        │        │        │                          │        │        │        │        │ Home   │  PgUp  │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │                          │   ←    │   ↓    │   ↑    │   →    │  End   │PageDown│
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │        │        │        │        │        │        │        │        │        │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │                 │        │        │        │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, KC_HOME, KC_PGUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_END,  KC_PGDN,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,  _______,         _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

/* Customize
    ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    │        │        │        │        │        │        │                          │        │        │        │        │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │                          │        │        │        │        │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │                          │        │        │        │        │        │        │
    ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    │        │        │        │        │        │        │        │        │        │        │        │        │        │        │        │
    └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   │        │        │        │                 │        │        │        │
                                   └────────┴────────┴────────┘                 └────────┴────────┴────────┘
*/
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

// Enable the ctrl+backspace (KC_BSPC) to function as delete forward (KC_DEL)
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) { // on key-down of Backspace
                if (mod_state & MOD_MASK_CTRL) {
                    // Ctrl + Backspace -> Forward Delete
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


