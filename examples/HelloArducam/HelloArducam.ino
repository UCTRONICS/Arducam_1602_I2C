//www.uctronics.com
//Add support detecting the i2c address automaticly.
//Users don't need to care the i2c address.
//Update 07/06/2018
#include <Wire.h>
#include <Arducam_I2C.h>

Arducam_I2C lcd(0x227, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display,If not work,
// you can set it to 0x27 to try. The I2c address is defined by your I2C controller.
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
  lcd._Addr = iicScanner();
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello, Arducam!");
}

void loop()
{
}



uint8_t iicScanner() {
  byte error, address, getVal;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      getVal = address;
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  return getVal;
}
