# BigKNOB
![image](https://user-images.githubusercontent.com/31357974/120911848-11029f80-c650-11eb-8896-d142378cb411.png)
## What Is This?
This project includes:
1. QMK files for various keymaps for the [BigKNOB](https://www.etsy.com/listing/811162898/bigknob-customizable-programmable-usb-c) (v2) macropad controller, which includes 4 RGB LED key switches and a rotary encoder.
2. C# source for application enabling bidirectional communication between BigKNOB and the host computer. 

## Key Maps
### Layout
<img width="636" height="245" alt="image" src="https://github.com/user-attachments/assets/1b8b05e4-25ac-4d93-8cf4-edc0ba5434a0" />

### HotkeyPad
Makes function keys F13-F24 readily accessible. Jump to the files [here](https://github.com/Exergist/BigKNOB/tree/main/QMK/HotkeyPad). 
<details>
<summary><b>Keymap</b></summary>

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
</details>

### DisplaySwitch
Control device for the [ATEN CS1824](https://www.aten.com/us/en/products/kvm/desktop-kvm-switches/cs1824/) 4-port KVMP switch. Jump to the files [here](https://github.com/Exergist/BigKNOB/tree/main/QMK/DisplaySwitch/). 
<details>
<summary><b>Keymap</b></summary>

 * Encoder
   * Single-Tap = Illuminate key corresponding to currently focused port (if available)
   * Clockwise Rotation = Volume Up
   * Counter-Clockwise Rotation = Volume Down
 * Button 1 = Switch to port 1
 * Button 2 = Switch to port 2
 * Button 3 = Switch to port 3
 * Button 4 = Switch to port 4
</details>

## Raw HID Functionality
 * Move to specified layer

## How to Build and Install the Firmware?
### Creating the Firmware
<details>
<summary> <b>QMK Configurator Method</b> </summary>

 1. Load the [bigKNOB default configuration](https://config.qmk.fm/#/leafcutterlabs/bigknob/LAYOUT) in the QMK Configurator.
 2. Select the functions for the buttons and click compile.
    
    <img width="881" height="819" alt="image" src="https://github.com/user-attachments/assets/253a66f3-f9da-4abe-a734-8a6507911d07" />

 3. Once the compiling is complete, download and save the firmware hex file.
</details>
<details>
<summary> <b>Code-Only Method</b> </summary>

 1. Go through [The QMK Tutorial](https://docs.qmk.fm/#/newbs). To get started, create a new keymap project within QMK MSYS environment by running `qmk new-keymap -kb [keyboard name] -km [name of project]`
    * Example: `qmk new-keymap -kb leafcutterlabs/bigknob -km DisplaySwitch`
 3. Create the desired keyboard behavior by building content in the _keymap.c_ file.
 4. Add (or copy from other bigKNOB efforts) _config.h_ and _rules.mk_ files if needed (most likely YES) into the same location as the _keymap.c_ file.
 5. When _keymap.c_ and (if applicable) _config.h_ and _rules.mk_ are ready, go back to QMK MSYS and run `qmk compile -j 0 -kb [keyboard name] -km [name of project]`.
    * Example: `qmk compile -j 0 -kb leafcutterlabs/bigknob -km DisplaySwitch`
 6. The outputted firmware (hex file) is located at `...qmk_firmware\.build\[keyboard_name]_[project_name].hex`
    * Example: `...qmk_firmware\.build\leafcutterlabs_bigknob_DisplaySwitch.hex`
</details>

### Installing the Firmware
<details>
<summary> <b>QMK Toolbox Method</b> </summary>

 1. Download/install [QMK Toolbox](https://qmk.fm/toolbox). Then launch the application.
 2. Install device drivers by navigating to the "Tools" tab and selecting "Install Drivers" (requires administrative priviledges).
 3. Select the desired firmware hex file, set MCU to atmega32u4, and check Auto-Flash.
    
    <img width="867" height="702" alt="image" src="https://github.com/user-attachments/assets/0b12e77b-b5c9-4c67-a894-3e2cd32fc850" />

 4. Press the button under the bigKNOB device (may have a small hole in the case). The device should reboot and load the new firmware. Make sure to give QMK Toolbox time to complete the flashing process.
    
    <img width="820" height="724" alt="image" src="https://github.com/user-attachments/assets/11d00ad7-0730-4cda-81e5-027d5cc2fb0a" />

    Here is example output from the QMK Toolbox after successfully flashing the bigKNOB device:
    
    <img width="726" height="320" alt="image" src="https://github.com/user-attachments/assets/85225997-a28b-43a5-9bb0-87ef254681f9" />

</details>

## Notes
 * My [BigKNOB](https://www.etsy.com/listing/811162898/bigknob-customizable-programmable-usb-c) (identified as the "v2" version) was custom-ordered through [LeafCutterLabs on Etsy](https://www.etsy.com/shop/LeafCutterLabs) in May 2021. 
 * The keymap was optimized for use with the BigKNOB dented encoder. 
 * Additional QMK resources are compiled in the [QMK Syllabus](https://docs.qmk.fm/#/syllabus).
 * A [VoiceAttack plugin](https://github.com/Exergist/VAHidInterface) for communicating with BigKNOB is also available.

## Acknowledgements

* BigKNOB hardware design, original QMK source files, and steps for using the QMK Configurator and the QMK Toolbox are by [Craig Gardner from LeafCutterLabs](https://github.com/LeafCutterLabs/bigKNOB).
* [QMK](https://qmk.fm/about) is developed and maintained by Jack Humbert of OLKB with contributions from the community (and Hasu).
* [HidLibrary](https://github.com/mikeobrien/HidLibrary) is developed and maintained by Mike O'Brien and Austin Mullins (and other contributors).
* [ini-parser](https://github.com/rickyah/ini-parser) was developed by Ricardo Amores Hernandez (and other contributors).
* Keymap header ASCII art by [patorjk](https://patorjk.com/software/taag/).
* Many thanks to the following people (and probably others) from the [qmk Discord](https://discord.gg/Uq7gcHh) for their guideance: filterpaper, drashna, Dasky, ridingquerty, Erovia, sigprof, fauxpark, bomtarnes, CovfefeMcWhiskey, trankillity, tzarc
