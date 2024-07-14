# ESP32 Bluetooth Accessory Control

This project demonstrates how to control accessories connected to an ESP32 microcontroller using Bluetooth communication. The ESP32 receives commands from an Android application and toggles the GPIO pins accordingly.

## Features

- Connect to the ESP32 via Bluetooth
- Send JSON commands to control GPIO pins
- Sync accessory states between the Android app and ESP32
- Toggle accessory states based on received commands

## Components

- ESP32 microcontroller
- Android device running the companion app

## Getting Started

### Prerequisites

- ESP32 development board
- Arduino IDE or PlatformIO IDE with ESP32 board support
- Android device
- Android app APK (download link below)

### Android App

Download the Android app APK from the following GitHub link:

[Download Android App APK](https://github.com/MagicBulletPro/esp32-bluetooth-home-control/android_app/Magic-BT-V1.0.apk)

### Usage

1. **Prepare the ESP32:**
    - Upload the provided code to your ESP32 using the Arduino IDE.
    - Ensure the ESP32 is powered on and discoverable via Bluetooth.

2. **Install the Android App:**
    - Download and install the APK from the provided link on your Android device.

3. **Connect to ESP32:**
    - Open the app on your Android device.
    - The app will attempt to connect to the ESP32 Bluetooth device named "ESP32_BT".
    - Once connected, the device status will be displayed on the app.

4. **Control Accessories:**
    - Use the menu button in the app to add accessories by providing a name and GPIO pin number.
    - You can toggle the accessory's state (on/off) by tapping on it in the list.
    - The app allows you to delete accessories and synchronize their states with the ESP32.

5. **Popup Menu Options:**
    - **Add Accessory:** Add a new accessory by specifying its name and GPIO pin number.
    - **Search Bluetooth:** Search and connect to available Bluetooth devices.
    - **Exit:** Exit the application.

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

### Acknowledgements

- [Arduino](https://www.arduino.cc/)
- [Espressif Systems](https://www.espressif.com/)
- [Android Developers](https://developer.android.com/)

### Contact

For any inquiries, please contact [magicbulletsoft@gmail.com](mailto:magicbulletsoft@gmail.com).
