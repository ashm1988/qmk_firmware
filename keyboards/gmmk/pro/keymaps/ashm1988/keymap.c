/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Jonavin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_layers {
    _COLE,
    _QWER,
    _FN,
};

// ------ Tap Dance ------ //
enum custom_tapdance {
  TD_MUTE_PLAY,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUTE_PLAY] = ACTION_TAP_DANCE_DOUBLE(KC_MUTE, KC_MPLY),
};
// ------ Tap Dance ------ //

// ------ Win Lock ------ //
enum custom_keycodes {
  KC_WINLCK,    //Toggles Win key on and off
};

bool _isWinKeyDisabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;
    }
    return true;
};
// ------ Win Lock ------ //


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       Alt/F10  CTL/F11  SFT/F12	 Ins           Rotary(Mute/Play)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        F        P        G        J        L        U        Y        ;        [        ]        \                 PgUp
//      CapsLock A        R        S        T        D        H        N        E        I        O        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        K        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [_COLE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   RALT_T(KC_F10),  RCTL_T(KC_F11),  RSFT_T(KC_F12),  LALT_T(KC_INS), TD(TD_MUTE_PLAY),
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                   KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_QWER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   RALT_T(KC_F10),  RCTL_T(KC_F11),  RSFT_T(KC_F12),  LALT_T(KC_INS), TD(TD_MUTE_PLAY),
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,           KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,           KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,            KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                    KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        _______, KC_F13,   KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24, _______,            _______,
        _______, TO(_COLE),TO(_QWER),_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,          RGB_TOG,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, KC_SLCK, KC_PAUS, KC_PSCREEN, _______, _______, RESET,          _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,           _______,
        _______,          _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MODE_FORWARD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_MODE_REVERSE, RGB_SPI
    ),

};


#ifdef ENCODER_ENABLE       // Encoder Functionality

    bool encoder_update_user(uint8_t index, bool clockwise) {

        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_RSFT) ) {        // If you are holding R shift, Game vol
                tap_code(KC_F24);
            } else if (keyboard_report->mods & MOD_BIT(KC_RCTL)) {  // if holding R CTL, Sys vol
                tap_code(KC_F22);
            } else if (keyboard_report->mods & MOD_BIT(KC_RALT)) {  // if holding R Alt, Spotify vol
                tap_code(KC_F20);
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                tap_code(KC_VOLU);                                  // Otherwise it just changes volume
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_RSFT) ) {
                tap_code(KC_F23);
            } else if (keyboard_report->mods & MOD_BIT(KC_RCTL)) {
                tap_code(KC_F21);
            } else if (keyboard_report->mods & MOD_BIT(KC_RALT)) {
                tap_code(KC_F19);
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) { 
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        return true;
    }
#endif