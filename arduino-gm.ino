/*
 * Original author:JiangJie Zhang
 * 
 * License: MIT License
 * 
 * Please use freely with attribution. Thank you!
 * 
 * Connection at modified RadiationD-v1.1(CAJOE) counter side:
 *  +5V (Power) -> Arduino RAW power (5V from USB)
 *  VCC (separate logic-level voltage) -> Arduino VCC (3.3V or 5V) 
 *  VIN (Pulse signal (inverted logic), low = Arduino VCC level, high = 0V) 
 *     -> Arduino INTERRUPT_PIN pin, depending on platform
 *  GND -> 2N7000 Drain
 * 
 * Connection at DH22 side
 *  VCC -> Arduino VCC (3.3V or 5V)
 *  Data -> Arduino DHTPIN pin
 *  Ground -> Arduino GND pin
 * 
 * Connection at 2N7000 side
 *  Source -> Ardunino GND pin
 *  Gate -> Arduino ENABLE_PIN
 *  Drain -> RadiationD-v1.1(CAJOE) counter counter GND

 * Connection at SSD1306 OLED display in I2C mode
 *  RES -> Arduino OLED_RESET pin
 *  D/C -> Arduino GND
 *  CS -> Arduino GND
 *  CLK -> Arduno SCL
 *  DIN -> Arduino SDA
 *  GND -> Arduino GND
 *  VCC -> Arduino VCC
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define ENABLE_PIN 8      //Arduino digital PIN for enabling GM power
#define INTERRUPT_PIN 7
#define LOG_PERIOD 300000  //Logging period in milliseconds
#define MAX_PERIOD 60000  //1min (for CPM)
#define DISABLE_PERIOD 1498000 //Off-time period in miliseconds

#define OLED_RESET     9 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

unsigned long counts; //number of counts in the given timeframe
unsigned long cpm; //calculated counts per minute (CPM)
float multiplier;  //multiplier for counts to CPM conversion
unsigned long previousMillis;  //variable for time measurement


void tube_impulse(){       //interrupt handler
  counts++;               //increment the counter
}

void setup(){             //setup (runs on microcontroler init)
  counts = 0;             //reset counts
  multiplier = MAX_PERIOD / LOG_PERIOD; //calculate multiplier for CPM
  Serial.begin(9600);                   //serial console (for debug)
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), tube_impulse, FALLING);  //attach handler to the interrupt, on the falling edge
  pinMode(ENABLE_PIN,OUTPUT);                 //set enable pin mod to output
  digitalWrite(ENABLE_PIN,HIGH);              //enable GM power - initial
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Radiation: counting"));
  display.setCursor(0,10);
  display.println(F("Temperature: counting"));
  display.setCursor(0,20);
  display.println(F("Humidity: counting"));
  display.display();
  dht.begin();
}

void loop(){//main cycle - runs forever
  unsigned long currentMillis = millis();   //get miliseconds (no RTC, from start)
  float rad,h,t;
  if(currentMillis - previousMillis > LOG_PERIOD){  //LOG_PERIOD exceeded, calculate measures
    cpm = counts * multiplier;              //calculate CPM for given LOG_PERIOD
    rad = cpm/123.15; //J305 beta CPM to uSv/h ratio
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.print(F("{"));
    Serial.print("\"rad1\":");
    Serial.print(rad);
    Serial.print(",\"temp1\":");
    Serial.print(t);
    Serial.print(",\"hum1\":");
    Serial.print(h);
    Serial.println(F("}"));                //cpm to uSv/h ration for the tube
    display.clearDisplay();    
    display.setCursor(0,0);             // Start at top-left corner
    display.print(F("Radiation: "));
    display.print(rad);
    display.print(F(" "));
    display.print(char(229)); //micro
    display.println(F("Sv/h"));
    display.setCursor(0,10);
    display.print(F("Temperature: "));
    display.print(t);
    display.print(F(" "));
    display.print(char(247)); //deg
    display.println(F("C"));
    display.setCursor(0,20);
    display.print(F("Humidity: "));
    display.print(h);
    display.print(F(" "));
    display.println(F("%"));
    display.display();
    counts = 0;                             //zero counter
    digitalWrite(ENABLE_PIN,LOW);           //disable GM power
    delay(DISABLE_PERIOD);                  //wait for DISABLE_PERIOD
    previousMillis = millis();              //zeroing time miliseconds delta
    digitalWrite(ENABLE_PIN,HIGH);          //enable GM power
  }
  
}
