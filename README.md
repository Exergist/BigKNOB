![image](https://user-images.githubusercontent.com/31357974/120911848-11029f80-c650-11eb-8896-d142378cb411.png)

# BigKNOB

## What Is This?
This project includes:
1. QMK files for BigKNOB macropad controller with RGB LED key switches.
2. C# source for application enabling bidirectional communication between BigKNOB and the host computer. 

## Key Maps
### HotkeyPad
Makes function keys F13-F24 readily accessible. Jump to the files [here](https://github.com/Exergist/BigKNOB/tree/main/QMK/HotkeyPad). 
 * Encoder
   * Single-Tap = Next Layer
   * Double-Tap = Toggle RGB LEDs On/Off
   * Press-Hold = Previous Layer
   * Clockwise Rotation = Next Layer
   * Counter-Clockwise Rotation = Previous Layer
 * Button 1:
   * Layer 0 = F13
   * Layer 1 = F17
   * Layer 2 = F21
 * Button 2:
   * Layer 0 = F14
   * Layer 1 = F18
   * Layer 2 = F22
 * Button 3:
   * Layer 0 = F15
   * Layer 1 = F19
   * Layer 2 = F23
 * Button 4:
   * Layer 0 = F16
   * Layer 1 = F20
   * Layer 2 = F24
 * RGB LED Colors:
   * Layer 0 = Red
   * Layer 1 = Green
   * Layer 2 = Blue

### DisplaySwitch
Control device for the [ATEN CS1824](https://www.aten.com/us/en/products/kvm/desktop-kvm-switches/cs1824/) 4-port KVMP switch. Jump to the files [here](https://github.com/Exergist/BigKNOB/tree/main/QMK/DisplaySwitch/). 
 * Encoder
   * Single-Tap = WIP
   * Double-Tap = WIP
   * Press-Hold = WIP
   * Clockwise Rotation = WIP
   * Counter-Clockwise Rotation = WIP
 * Button 1 = WIP
 * Button 2 = WIP
 * Button 3 = WIP
 * Button 4 = WIP

## Raw HID Functionality
 * Move to specified layer

## How to Install the Firmware?
 1. Go through [The QMK Tutorial](https://docs.qmk.fm/#/newbs).
 2. Insert the desired _config.h_, _rules.mk_, and _keymap.c_ files where appropriate prior to building and uploading the firmware. 
   
## Notes
 * My [BigKNOB](https://www.etsy.com/listing/811162898/bigknob-customizable-programmable-usb-c) was custom-ordered through [LeafCutterLabs on Etsy](https://www.etsy.com/shop/LeafCutterLabs) on 5/9/2021. 
 * The keymap was optimized for use with the BigKNOB dented encoder. 
 * Additional QMK resources are compiled in the [QMK Syllabus](https://docs.qmk.fm/#/syllabus).
 * A [VoiceAttack plugin](https://github.com/Exergist/VAHidInterface) for communicating with BigKNOB is also available.

## Acknowledgements

* BigKNOB hardware design and original QMK source files are by [Craig Gardner from LeafCutterLabs](https://github.com/LeafCutterLabs).
* [QMK](https://qmk.fm/about) is developed and maintained by Jack Humbert of OLKB with contributions from the community (and Hasu).
* [HidLibrary](https://github.com/mikeobrien/HidLibrary) is developed and maintained by Mike O'Brien and Austin Mullins (and other contributors).
* [ini-parser](https://github.com/rickyah/ini-parser) was developed by Ricardo Amores Hernandez (and other contributors).
* Keymap header ASCII art by [patorjk](https://patorjk.com/software/taag/).
* Many thanks to the following people (and probably others) from the [qmk Discord](https://discord.gg/Uq7gcHh) for their guideance:
  * filterpaper
  * drashna
  * Dasky
  * ridingquerty
  * Erovia
  * sigprof
  * fauxpark
  * bomtarnes
  * CovfefeMcWhiskey
  * trankillity
  * tzarc
