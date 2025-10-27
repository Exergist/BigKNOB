/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#pragma once

// USB Device descriptor parameters
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    "leafcutterlabs"
#define PRODUCT         "bigKNOB"
#define DESCRIPTION     5 key with rotary board
#define RAW_USAGE_PAGE 	0xFF60 // Raw HID communication (added by Exergist)
#define RAW_USAGE_ID 	0x61 // Raw HID communication (added by Exergist)

#define TAPPING_TERM 250 // Speed for double-tap

#define ENCODER_RESOLUTION 4 // Original default was 2, however a value of 4 works better

// RGB LEDs are ws2812
#define RGBLIGHT_LIMIT_VAL 128 // Set max value (brightness) for LEDs (max limit is 255 or RGBLIGHT_LIMIT_VAL)
#define RGBLIGHT_SLEEP // RGB lighting will be switched off when the host goes to sleep