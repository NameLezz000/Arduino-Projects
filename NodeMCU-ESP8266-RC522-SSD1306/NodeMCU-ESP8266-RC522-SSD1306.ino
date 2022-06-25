/* --------------------------------------------------------------------------------------------------------------------
 * Simple RFID access control with an OLED display
 * --------------------------------------------------------------------------------------------------------------------
 * Libraries used: 
 * MFRC522: https://github.com/miguelbalboa/rfid
 * Adafruit_SSD1306: https://github.com/adafruit/Adafruit_SSD1306
 * 
 * Pin layout used:
 * 
 * Pin  Module   Use
 * D1   SSD1306  SCL
 * D2   SSD1306  SDA
 * D3   MFRC522  RST
 * D5   MFRC522  SCK
 * D6   MFRC522  MISO
 * D7   MFRC522  MOSI
 * D8   MFRC522  SDA(SS)
 * 
 */



//Include all the libraries that are required for this project
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//SPI RC522 settings
#define RST_PIN D3
#define SS_PIN D8

//RC522 permission rules
byte readCard[4];
String Allowed_UUID = "********";  //insert the allowed card/tag UUID here, without spaces
String Read_ID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);

//OLED initialization
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire, -1);

void setup() 
{
  //modules initialization
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //asks for the scan
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(20,6);
  display.print("Access Control ");
  display.setCursor(20,17);
  display.print("Scan Your Card");
  display.display();
}

void loop() 
{
  while (getID()) 
  {
    display.clearDisplay();
    display.setCursor(20,12);
    display.setTextSize(1);
    
    if (Read_ID == Allowed_UUID) 
    {
      
     display.print("ACCESS GRANTED!");
     
    }
    else
    {
      display.print("ACCESS DENIED!");
    }
    
      display.display();
      display.setCursor(0,0);
      display.display();
      
    delay(2000);

    display.clearDisplay();
    display.setCursor(20,6);
    display.print("Access Control ");
    display.setCursor(20,17);
    display.print("Scan Your Card");
    display.display();
  }
}

boolean getID() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { 
  return false;
  }
  Read_ID = "";
  for ( uint8_t i = 0; i < 4; i++) { 
  //readCard[i] = mfrc522.uid.uidByte[i];
  Read_ID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  Read_ID.toUpperCase();
  mfrc522.PICC_HaltA(); 
  return true;
}
