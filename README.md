# arduino-gm
Arduino-controlled GM counter and temp/humidity meter based on modified RadiationD-v1.1(CAJOE). Radiation level, temperature, and humidity are displayed on OLED and transmitted via USB serial in JSON format, for example: `{"rad1":0.18,"temp1":20.60,"hum1":71.50}`

2N7000 N-MOSFET is used to enable/disable power for modified RadiationD board. It's necessary for Arduino boards with 3.3V logic level.

![Photo of the prototyped system](https://github.com/malipek/arduino-gm/blob/master/media/gm-counter.png?raw=true)

![Schematic of system connections](https://github.com/malipek/arduino-gm/blob/master/media/Schematic_GM_connection_2022-10-09.png?raw=true)

## External dependencies

* Adafruit's SSD1306 library for monochrome 
OLED displays
* Adafruit's DHT22 library


## Components

* Arduino controller 5V or 3.3V (tested on Arduino Uno and Arduino Pro Micro), **powered with 5V USB**
* 0.96" SSD1306 128x64 OLED in I2C mode (check vendor's documentation)
* DHT 22
* Modified RadiationD-v1.1(CAJOE) with J305β (check below)
* 2N7000 N-MOSFET

## Notes

* It's important that Arduino board is powered with stabilized 5V (stable 5V is present on Arduino RAW pin)
* System works with both 5V and 3.3V logic level
* Data is refreshed approximately every 1 hour. After the measurement the GM counter is powered down, to extend lifespan of the Geiger tube
* OLED display is set to I2C mode
* **Danger! Geiger tube is powered with high voltage! Don't touch bare metal connections when the board is powered! Discharge the step-up converter before you start the work, for example by attaching voltmeter in the 1000V range to Geiger tube, until voltage drops to 0.**

## RadiationD-v1.1(CAJOE) modification
Because the system uses Arduino as a counter, all signaling circuits were removed from the GM board. It allowed reducing power consumption down to 8mA.

Avalanche discharge logic-side power was decoupled from board's 5V power, and needs to be supplied externally, from Arduino's VCC pin. This allows operating in both: 5V and 3.3V logic.

![Schema of modified RadiationD circut](https://github.com/malipek/arduino-gm/blob/master/media/modified_GM_counter.png?raw=true)

# Diclaimer
**Modyfications shown above are for informational purposes only. Any modification to electrical equipment based on materials published will be made on your own risk. I will not be liable for any damage caused by following information published in this repository.**
