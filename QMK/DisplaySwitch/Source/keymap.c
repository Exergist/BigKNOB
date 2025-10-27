/*
//    _       _           _  __  _   _    ____    ____  
//   | |     (_)         | |/ / | \ | |  / __ \  |  _ \ 
//   | |__    _    __ _  | ' /  |  \| | | |  | | | |_) |
//   | '_ \  | |  / _` | |  <   | . ` | | |  | | |  _ < 
//   | |_) | | | | (_| | | . \  | |\  | | |__| | | |_) |
//   |_.__/  |_|  \__, | |_|\_\ |_| \_|  \____/  |____/ 
//                 __/ |								
//                |___/    				  DISPLAY SWITCH
//														
*/

// *************
// *  SUMMARY  *
// *************

// Custom keymap for bigKNOB by Exergist (2025)
// Functionality includes:
//   • Focusing on a given port on the ATEN CS1824 KVMP switch via a corresponding key press
//   • The LED on a pressed key is briefly illuminated
//   • Pressing the encoder briefly illuminates the most recently selected key/port
//   • If no port has been selected recently, then pressing the encoder triggers an error flash

// **********************
// *  ACKNOWLEDGEMENTS  *
// **********************

// bigKNOB hardware and original source code by Craig Gardner (https://github.com/LeafCutterLabs)
// ASCII art by patorjk (https://patorjk.com/software/taag/)

// **********************
// *  INCLUDE & DEFINE  *
// **********************

#include QMK_KEYBOARD_H
#include "deferred_exec.h"

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

int selectedPort = 0; // Currently selected port on ATEN CS1824 KVMP switch
int ledIlluminationTime = 1000; // Time in milliseconds to illuminate LEDs
static deferred_token led_off_tok[RGBLIGHT_LED_COUNT]; // One deferred token per LED

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
	[0] = LAYOUT( PORT_CHECK, MACRO_1, MACRO_2, MACRO_3, MACRO_4 ) // Format = Encoder, Button1, Button2, Button3, Button4
};

// |------------------|
// | Encoder Rotation |
// |------------------|

// Defines the behavior for encoder rotation across all applicable layers
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) } // Format = Counter-clockwise action, clockwise action
};
#endif

// ***********************
// *  METHOD DEFINITION  *
// ***********************

// Method run as the very last task in the keyboard initialization process
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom();                             // Enable RGB LEDs
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);     // Set LED mode to solid color

	// Turn off all LEDs and clear any deferral tokens
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgblight_sethsv_at(0, 0, 0, i);
        led_off_tok[i] = INVALID_DEFERRED_TOKEN;
    }
}

// Turn off one LED when the timer fires
static uint32_t led_off_cb(uint32_t trigger_time, void *cb_arg) {
    uint8_t idx = (uint8_t)(uintptr_t)cb_arg;
    rgblight_sethsv_at(0, 0, 0, idx);
    led_off_tok[idx] = INVALID_DEFERRED_TOKEN;
    return 0; // don't reschedule
}

// Turn on LED now, auto-off after specified time (non-blocking)
static void light_led_for(uint8_t idx, uint8_t h, uint8_t s, uint8_t v, uint16_t ms) {
    rgblight_sethsv_at(h, s, v, idx); // show immediately

    if (led_off_tok[idx] != INVALID_DEFERRED_TOKEN) {
        // Extend the existing pending execution relative to "now"
        extend_deferred_exec(led_off_tok[idx], ms);
    } else {
        // Schedule a fresh deferral
        led_off_tok[idx] = defer_exec(ms, led_off_cb, (void *)(uintptr_t)idx);
    }
}

// Method for turning off all LEDs while keeping them enabled
static void all_leds_off_noeeprom(void) {
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) { 
        rgblight_sethsv_at(0, 0, 0, i); // Loop through and turn off each LED
    }
}

// Method for flashing RGB LEDs to alert of an issue or unexpected situation
void error_flash(void)
{	
	float timeStep = 125; // Time step for cycling flashing colors (ms)
	int flashTime = ledIlluminationTime; // Amount of time to flash LEDs (ms)
	float timer = 0;
	
	// Loop over flashTime while cycling displayed colors every timeStep
	while (timer < flashTime)
	{
		rgblight_sethsv_noeeprom(HSV_YELLOW);
		wait_ms(timeStep);
		all_leds_off_noeeprom();
		wait_ms(timeStep);
		timer += (timeStep * 2);
	}
}

// Method run whenever a key is pressed or released
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint16_t portHotkey = 0;
    switch (keycode) {
	case PORT_CHECK:
        if (record->event.pressed) {
            // When keycode PORT_CHECK is pressed
			if (selectedPort == 0) {
				// bigKNOB hasn't been used to select a port
				error_flash(); // Flash error pattern on bigKNOB
			}
			else {
				// Light the selected port's LED now; it will auto-off after ledIlluminationTime
				uint8_t idx = (uint8_t)(selectedPort - 1);
				light_led_for(idx, HSV_GREEN, (uint16_t)ledIlluminationTime);
			}
        } else {
            // When keycode PORT_CHECK is released
        }
        return true;
		
    case MACRO_1:
        if (record->event.pressed) {
            // When keycode MACRO_1 is pressed
			selectedPort = 1; // Store selected port number
			portHotkey = KC_1; // Store target portHotkey
        } else {
            // When keycode MACRO_1 is released
        }
        break;

    case MACRO_2:
        if (record->event.pressed) {
            // When keycode MACRO_2 is pressed
			selectedPort = 2; // Store selected port number
			portHotkey = KC_2; // Store target portHotkey
        } else {
            // When keycode MACRO_2 is released
        }
        break;
		
    case MACRO_3:
        if (record->event.pressed) {
            // When keycode MACRO_3 is pressed
			selectedPort = 3; // Store selected port number
			portHotkey = KC_3; // Store target portHotkey
        } else {
            // When keycode MACRO_3 is released
        }
        break;
		
    case MACRO_4:
        if (record->event.pressed) {
            // When keycode MACRO_4 is pressed
			selectedPort = 4; // Store selected port number
			portHotkey = KC_4; // Store target portHotkey
        } else {
            // When keycode MACRO_4 is released
        }
        break;
    }
	if (portHotkey == 0) {
		// Do nothing because a key was released
	} else {
		all_leds_off_noeeprom(); // Turn off all LEDs
		light_led_for(selectedPort-1, HSV_GREEN, (uint16_t)ledIlluminationTime); // Turn on LED corresponding to selected port for a period of time (they will auto-off)
		
		// Send series of key taps (macro) to focus on target port on ATEN CS1824 KVMP switch
		tap_code(KC_SCROLL_LOCK);
		wait_ms(80);
		tap_code(KC_SCROLL_LOCK);
		wait_ms(80);
		tap_code(portHotkey); // Send the keycode corresponding to the target port number
		wait_ms(80);
		tap_code(KC_ENTER);
	}
    return true;
}