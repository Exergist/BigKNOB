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
// Functionality includes:
//   • STUFF

// **********************
// *  ACKNOWLEDGEMENTS  *
// **********************

// bigKNOB hardware and original source code by Craig Gardner (https://github.com/LeafCutterLabs)
// ASCII art by patorjk (https://patorjk.com/software/taag/)

// **********************
// *  INCLUDE & DEFINE  *
// **********************

#include QMK_KEYBOARD_H
#include "raw_hid.h"

#define _MAIN 0 // In default keymap, not sure if needed

// ********************************
// *  CUSTOM KEYCODE DECLARATION  *
// ********************************

// Name and assigned unique numbers for custom keycodes
enum customKeycodes
{
	MACRO_1 = SAFE_RANGE,
	MACRO_2,
	MACRO_3,
	MACRO_4,
	PORT_CHECK
};

// **********************
// *  GLOBAL VARIABLES  *
// **********************

uint8_t selectedPort = -1; // Currently selected port on ATEN CS1824 KVMP switch

// ************
// *  LAYERS  *
// ************

// Declare keymap layers
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
	
	[_PRIMARY] = LAYOUT // Layer 0 keymap
	(
		// F13, F14, F15, F16, F17
		PORT_CHECK, MACRO_1, MACRO_2, MACRO_3, MACRO_4
	)
	// [_SECONDARY] = LAYOUT // Layer 1 keymap
	// (
		// // ENCODER_DANCE, F17, F18, F19, F20
		// TD(ENCODER_DANCE), KC_F17, KC_F18, KC_F19, KC_F20
	// ),
	// [_TERTIARY] = LAYOUT // Layer 2 keymap
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

// ***********************
// *  METHOD DEFINITION  *
// ***********************

// Method run as the very last task in the keyboard initialization process
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom();                             // Enable RGB LEDs
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);     // Set LED mode to solid color
}

// Method for turning off all LEDs while keeping them enabled
static void all_leds_off_noeeprom(void) {
    for (uint8_t i = 0; i < MATRIX_COLS-1; i++) { 
        rgblight_sethsv_at(0, 0, 0, i); // Loop through and turn off each LED
		//wait_ms(30); // Brief pause
    }
}

// Method run whenever a key is pressed or released
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	case PORT_CHECK:
        if (record->event.pressed) {
            // When keycode PORT_CHECK is pressed
			if (selectedPort == -1) {
				// Do nothing, bigKNOB hasn't been used to select a port
			}
			else {
				all_leds_off_noeeprom(); // Turn off all LEDs
				wait_ms(500); // Brief pause
				rgblight_sethsv_at(HSV_GREEN, selectedPort-1); // Turn on LED corresponding to selected port
			}
        } else {
            // When keycode PORT_CHECK is pressed
        }
        break;
		
    case MACRO_1:
        if (record->event.pressed) {
            // When keycode MACRO_1 is pressed
			selectedPort = 1; // Store selected port number
			all_leds_off_noeeprom(); // Turn off all LEDs
			rgblight_sethsv_at(HSV_GREEN, selectedPort-1); // Turn on LED corresponding to selected port
            SEND_STRING(SS_TAP(X_SCROLL_LOCK) // Send macro to switch to ATEN CS1824 port 1
						SS_DELAY(100) 
						SS_TAP(X_SCROLL_LOCK) 
						SS_DELAY(100) 
						SS_TAP(X_1)
						SS_DELAY(100)
						SS_TAP(X_ENTER));
        } else {
            // When keycode MACRO_1 is released
        }
        break;

    case MACRO_2:
        if (record->event.pressed) {
            // When keycode MACRO_2 is pressed
			selectedPort = 2; // Store selected port number
			all_leds_off_noeeprom(); // Turn off all LEDs
			rgblight_sethsv_at(HSV_GREEN, selectedPort-1); // Turn on LED corresponding to selected port
            SEND_STRING(SS_TAP(X_SCROLL_LOCK) // Send macro to switch to ATEN CS1824 port 2
						SS_DELAY(100) 
						SS_TAP(X_SCROLL_LOCK) 
						SS_DELAY(100) 
						SS_TAP(X_2)
						SS_DELAY(100)
						SS_TAP(X_ENTER));
        } else {
            // When keycode MACRO_2 is released
        }
        break;
		
    case MACRO_3:
        if (record->event.pressed) {
            // When keycode MACRO_3 is pressed
			selectedPort = 3; // Store selected port number
			all_leds_off_noeeprom(); // Turn off all LEDs
			rgblight_sethsv_at(HSV_GREEN, selectedPort-1); // Turn on LED corresponding to selected port
            SEND_STRING(SS_TAP(X_SCROLL_LOCK) // Send macro to switch to ATEN CS1824 port 3
						SS_DELAY(100) 
						SS_TAP(X_SCROLL_LOCK) 
						SS_DELAY(100) 
						SS_TAP(X_3)
						SS_DELAY(100)
						SS_TAP(X_ENTER));
        } else {
            // When keycode MACRO_3 is released
        }
        break;
		
    case MACRO_4:
        if (record->event.pressed) {
            // When keycode MACRO_4 is pressed
			selectedPort = 4; // Store selected port number
			all_leds_off_noeeprom(); // Turn off all LEDs			
			rgblight_sethsv_at(HSV_GREEN, selectedPort-1); // Turn on LED corresponding to selected port
            SEND_STRING(SS_TAP(X_SCROLL_LOCK) // Send macro to switch to ATEN CS1824 port 4
						SS_DELAY(100) 
						SS_TAP(X_SCROLL_LOCK) 
						SS_DELAY(100) 
						SS_TAP(X_4)
						SS_DELAY(100)
						SS_TAP(X_ENTER));
        } else {
            // When keycode MACRO_4 is released
        }
        break;
    }
    return true;
};

// // Method to toggle an LED
// void toggle_LED(uint16_t lightNumber, bool lightOn) {
	// if (lightOn == true)
		// rgblight_sethsv_at(HSV_GREEN, lightNumber); // Set LED to GREEN
	// else {
		// wait_ms(500); // Pause for 500 milliseconds
		// rgblight_sethsv_at(0, 0, 0, lightNumber); // Turn off LED
	// }
// }

// // Method run whenever a key is pressed or released
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    // case MACRO_1:
        // if (record->event.pressed) {
            // // when keycode MACRO_1 is pressed
			// rgblight_sethsv_at(HSV_GREEN, 0); // Turn on LED 0
            // SEND_STRING(SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_1)
						// SS_DELAY(100)
						// SS_TAP(X_ENTER));
			// toggle_LED(0, false); // Brief pause then turn off LED 0
        // } else {
            // // when keycode MACRO_1 is released
        // }
        // break;

    // case MACRO_2:
        // if (record->event.pressed) {
            // // when keycode MACRO_2 is pressed
			// toggle_LED(1, true); // Turn on LED 1
            // SEND_STRING(SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_2)
						// SS_DELAY(100)
						// SS_TAP(X_ENTER));
			// toggle_LED(1, false); // Brief pause then turn off LED 1
        // } else {
            // // when keycode MACRO_2 is released
        // }
        // break;
		
    // case MACRO_3:
        // if (record->event.pressed) {
            // // when keycode MACRO_3 is pressed
			// toggle_LED(2, true); // Turn on LED 2
            // SEND_STRING(SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_3)
						// SS_DELAY(100)
						// SS_TAP(X_ENTER));
			// toggle_LED(2, false); // Brief pause then turn off LED 2
        // } else {
            // // when keycode MACRO_3 is released
        // }
        // break;
		
    // case MACRO_4:
        // if (record->event.pressed) {
            // // when keycode MACRO_4 is pressed
			// toggle_LED(3, true); // Turn on LED 3
            // SEND_STRING(SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_SCROLL_LOCK) 
						// SS_DELAY(100) 
						// SS_TAP(X_4)
						// SS_DELAY(100)
						// SS_TAP(X_ENTER));
			// toggle_LED(3, false); // Brief pause then turn off LED 3
        // } else {
            // // when keycode MACRO_4 is released
        // }
        // break;
    // }
    // return true;
// };

// // Method to briefly turn on an LED
// void flash_LED(uint16_t lightNumber, uint16_t lightOnTime){
	// rgblight_sethsv_at(HSV_GREEN, lightNumber); // Set LED to GREEN
	// wait_ms(lightOnTime); // Pause for lightOnTime milliseconds
	// rgblight_sethsv_at(0, 0, 0, lightNumber); // Turn off LED
// }

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