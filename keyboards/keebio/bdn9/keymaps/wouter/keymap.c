/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define _MEDIA 0
#define _RAISE 1
#define _BLENDER 2
#define _MISC 2

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

// TODO Change lighting on layer.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |                  | Knob 2: Page Dn/Up |
        | Press: Mute       | Home             | Press: Play/Pause  |
        | Hold: Layer 2     | Print Screen     | RGB Mode           |
        | Media Previous    | Media Pause/Play | Right              |
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE,    KC_MEDIA_SELECT,    KC_MPLY,
        MO(_RAISE), KC_PSCREEN,         TO_(_BLENDER),
        KC_MPRV,    KC_MPLY,            KC_MNXT
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [_RAISE] = LAYOUT(
        _______, BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),

    // TODO
    [_BLENDER] = LAYOUT(
        _______, BL_STEP, KC_STOP,
        _______, KC_HOME, TO_(_MISC),
        KC_MPRV, KC_END , TO_(_MEDIA)
    ),

    [_MISC] = LAYOUT(
        RESET  , BL_STEP,       KC_STOP,
        _______, KC_SCROLLLOCK, TO_(_MEDIA),
        KC_MPRV, KC_CAPSLOCK,   KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
