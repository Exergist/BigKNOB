/*
//    _       _           _  __  _   _    ____    ____
//   | |     (_)         | |/ / | \ | |  / __ \  |  _ \
//   | |__    _    __ _  | ' /  |  \| | | |  | | | |_) |
//   | '_ \  | |  / _` | |  <   | . ` | | |  | | |  _ <
//   | |_) | | | | (_| | | . \  | |\  | | |__| | | |_) |
//   |_.__/  |_|  \__, | |_|\_\ |_| \_|  \____/  |____/
//                 __/ |
//                |___/    
//
*/

// ***********
// *  NOTES  *
// ***********

// Custom keymap for bigKNOB by Exergist (2025)
// Modified from original source code with:
//   • STUFF

// **********************
// *  ACKNOWLEDGEMENTS  *
// **********************

// bigKNOB hardware and original source code by Craig Gardner (https://github.com/LeafCutterLabs)
// ASCII art by patorjk (https://patorjk.com/software/taag/)

/* Copyright 2021 Craig Gardner
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

// **********************
// *  INCLUDE & DEFINE  *
// **********************

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#define RBG_VAL 50 // Sets initial RGB color for key backlights?

#define _MAIN 0 // In default keymap, not sure if needed

// ************
// *  LAYERS  *
// ************

// Layer declarations
enum layers
{ 
	_PRIMARY
	// _SECONDARY,
	// _TERTIARY
};

// ************
// *  KEYMAP  *
// ************

// |---------------|
// | Keypad Layout |
// |---------------|

//
//                .-------------------------------------------------------------------------------.
//                |      _.-""""-._                                                               |
//                |    .'          `.   .------------..------------..------------..------------.  |
//                |   /              \  |            ||            ||            ||            |  |
//                |  |                | |            ||            ||            ||            |  |
//   USB-C <====> |  |     Encoder    | |  Button1   ||  Button2   ||  Button3   ||  Button4   |  |
//                |  |                | |            ||            ||            ||            |  |
//                |   \              /  |            ||            ||            ||            |  |
//                |    `._        _.'   '------------''------------''------------''------------'  |
//                |       `-....-'                                                                |
//                '-------------------------------------------------------------------------------'
//

// |---------------|
// | Device Keymap |
// |---------------|

// Defines the behavior for encoder and key presses across all applicable layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// NOTES:
	// Format = Encoder, Button1, Button2, Button3, Button4
	// [WIP] TD(ENCODER_DANCE) = [Single-Tap = Activate Next Layer, Double-Tap = Toggle RGB LEDs On/Off, Press-Hold = Activate Previous Layer]
	
	[_PRIMARY] = LAYOUT // Layer 0
	(
		// F13, F14, F15, F16, F16
		KC_F13, KC_F14, KC_F15, QK_UNDERGLOW_HUE_UP, QK_UNDERGLOW_TOGGLE
	)
	// [_SECONDARY] = LAYOUT // Layer 1
	// (
		// // ENCODER_DANCE, F17, F18, F19, F20
		// TD(ENCODER_DANCE), KC_F17, KC_F18, KC_F19, KC_F20
	// ),
	// [_TERTIARY] = LAYOUT // Layer 2
	// (
		// // ENCODER_DANCE, F21, F22, F23, F24
		// TD(ENCODER_DANCE), KC_F21, KC_F22, KC_F23, KC_F24
	// )
};

// |------------------|
// | Encoder Rotation |
// |------------------|

// Defines the behavior for encoder rotation across all applicable layers
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
    // [1] = { ENCODER_CCW_CW(UG_HUED, UG_HUEU),  ENCODER_CCW_CW(UG_SATD, UG_SATU)  },
    // [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    // [3] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT),  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

// Method run as the very last task in the keyboard initialization process
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();                               // Ensure RGB LEDs are on
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);       // Set RGB mode to solid color
    rgblight_sethsv_noeeprom(HSV_GREEN);                      // Set initial RGB color
}

// // Note that this might be depreciated as of 10/24/2025. See https://docs.qmk.fm/ChangeLog/20250525#deprecation-of-encoder-update-kb-user
// bool encoder_update_user(uint8_t index, bool clockwise) {
	// if (index == 0) {
		// if (clockwise) {
			// tap_code(KC_VOLU);
		// } else {
			// tap_code(KC_VOLD);
		// }
	// }
	// return true;
// }