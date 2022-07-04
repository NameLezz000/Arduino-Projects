/* --------------------------------------------------------------------------------------------------------------------
 * Simple weather station with an OLED display
 * --------------------------------------------------------------------------------------------------------------------
 * 
 * Libraries used: 
 * DHT Sensor: https://github.com/adafruit/DHT-sensor-library
 * Adafruit_SSD1306: https://github.com/adafruit/Adafruit_SSD1306
 * 
 * Pin layout used:
 * 
 * Pin  Module   Use
 * D1   SSD1306  SCL
 * D2   SSD1306  SDA
 * D4   DHT11    Data 
 * 
 */


// Include all the libraries that are required for this project
#include "SPI.h"
#include "DHT.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// Creating the object sensor on pin 'D4'
#define DHTPIN  D4      // Digital pin connected to the DHT sensor

// Uncomment the type in use
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// OLED initialization
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire, -1);

void setup() 
{
  // Initialize serial communications at 9600 bps
  Serial.begin(9600);
  
  // Modules initialization
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.print("Display On");
  
  // OLED startup and clear the buffer
  display.clearDisplay();
  display.display();
  
  dht.begin();  
}

void loop() 
{
  // Reading the temperature in Celsius degrees and store in the C variable
  int C = dht.readTemperature();  
  // Reading the humidity index
  int H = dht.readHumidity();     

  // Oled Settings
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  // Print the data on the OLED display
  display.setCursor(0,6);
  display.print("Humidity: ");
  display.print(H);
  display.print("%");
  display.print("\nTemperature: ");
  display.print(C);
  display.print("C");
  // Actually display the data above
  display.display();
  
  // Print the collected data in a row on the Serial Monitor
  Serial.print("H: ");
  Serial.print(H);
  Serial.print("\tC: ");
  Serial.print(C);
  Serial.print("\n");

  delay(1000);    // Wait one second before get another temperature reading
}
