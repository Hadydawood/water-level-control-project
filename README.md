# water-level-control-project
# Ultrasonic Sensor Water Level Controller

## Overview

This project implements a water level controller using an ultrasonic sensor to measure the water level and control a water pump accordingly. The system also includes an LCD display for status updates, LEDs to indicate different states, and a buzzer for audible alerts. The controller can operate in both manual and automatic modes.

## Components

- **Ultrasonic Sensor (HC-SR04)**: Measures the distance to the water surface.
- **LCD Display (I2C 16x2)**: Displays water level and pump status.
- **LEDs**: Indicate different statuses (red, yellow, green).
- **Buzzer**: Provides audible alerts for different conditions.
- **Float Switches**: Detect minimum and maximum water levels.
- **Relay Module**: Controls the water pump.
- **Push Button and Toggle Switch**: For manual pump control and switching between manual and automatic modes.

## Wiring

- **Ultrasonic Sensor**: 
  - Trig Pin: Digital Pin 10
  - Echo Pin: Digital Pin 11
- **LCD Display**: I2C Address 0x27
- **LEDs**:
  - Red LED: Digital Pin 4
  - Yellow LED: Digital Pin 7
  - Green LED: Digital Pin 8
- **Buzzer**: Digital Pin 9
- **Float Switches**:
  - Low Level Float: Digital Pin 12
  - Max Level Float: Digital Pin 13
- **Relay Module**:
  - Dry Run Pin: Digital Pin 3
  - Relay Pin: Digital Pin 2
- **Manual Control**:
  - Pump Manual: Digital Pin 5
  - Auto/Manual: Digital Pin 6

## Code Description

### Libraries

- `EEPROM.h`: For EEPROM operations (though not used in the provided code).
- `Wire.h`: For I2C communication.
- `LiquidCrystal_I2C.h`: For LCD display control.

### Setup

In the `setup()` function:
- Initialize the LCD.
- Set up pin modes for the ultrasonic sensor, relay, float switches, LEDs, buzzer, and manual control buttons.

### Loop

In the `loop()` function:
- Send an ultrasonic pulse and calculate the distance to the water surface.
- Map the distance to a water level value.
- Update the LCD display with the current water level and pump status.
- Check the dry run protection and float switch states to determine whether to turn the pump on or off.
- Switch between manual and automatic modes based on the toggle switch state.
- Control the LEDs and buzzer based on the system state.

### Functions

- `sendSoundWave()`: Sends a pulse from the ultrasonic sensor.
- `buzzer1()`, `buzzer2()`, `buzzer3()`: Generate different buzzer tones for various alerts.

## How to Use

1. **Setup the Hardware**: Connect the components as described in the wiring section.
2. **Upload the Code**: Upload the provided code to the Arduino.
3. **Monitor the LCD**: The LCD will display the water level and pump status.
4. **Manual Mode**: Use the push button to manually control the pump.
5. **Automatic Mode**: The pump will automatically turn on or off based on the water level detected by the float switches and the ultrasonic sensor.

## Troubleshooting

- Ensure all connections are secure and correctly wired.
- Verify the I2C address of the LCD if it doesn't display correctly.
- Check the ultrasonic sensor for accurate distance measurement.

## Future Enhancements

- Add EEPROM functionality to save settings or states.
- Implement more robust error handling.
- Integrate with a mobile app for remote monitoring and control.

## License

This project is open-source. Feel free to modify and distribute it as needed.
