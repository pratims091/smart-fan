/*
 * Smart Fan - A temperature controlled fan v1.0
 * Author Pratim Sarangi
 * First run 31-October-2017
 */

#include <dht.h>
#include <LiquidCrystal.h>

#define FAN1_RELAY_PIN 7
#define TEMP_SENSOR_PIN 8
#define DHT11_PIN 6
#define LCD_RS_PIN 12
#define LCD_EN_PIN 11
#define LCD_D4_PIN 5
#define LCD_D5_PIN 4
#define LCD_D6_PIN 3
#define LCD_D7_PIN 2

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
dht DHT;

void setup() {

  // put your setup code here, to run once:

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Set up the realy
  pinMode(FAN1_RELAY_PIN, OUTPUT);

  // Print a message to the LCD.
  lcd.print("Initializing...");

  Serial.begin(9600);
  Serial.println("System Initializing...");
}

void loop() {
  // Put your main code here, to run repeatedly:

  // This can be used to log DHT11 errros
  int chk = DHT.read11(DHT11_PIN);

  // Get the current temperature and humidity
  int current_temp = (int)DHT.temperature;
  int current_humidity = (int)DHT.humidity;

  // By default the fan will run
  boolean fan_running = true;

  // Check the temperature every 1 minuites
  delay(60000);

  // Set the cursor to column 0, line 0
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);

  // Print a message to first line of LCD  
  // Print current temperature and humidity to LCD
  lcd.print("Temp:");
  lcd.print(current_temp);

  Serial.println("Temparature: ");
  Serial.println(current_temp, 1);

  lcd.print(" Humi:");
  lcd.print(current_humidity);

  Serial.println("Humidity: ");
  Serial.println(current_humidity, 1);  

  // If current temperature is below 24C set the fan relay to high which will eventually power on the relay
  // which opens the AC circuit and switches off the fan
  if(current_temp <= 24) {
    digitalWrite(FAN1_RELAY_PIN, 0);
    fan_running = false;
  } else {
    digitalWrite(FAN1_RELAY_PIN, 1);
    fan_running = true;
  }

  // Print fan runnig status to LCD
  lcd.setCursor(0, 1);
  if(fan_running) {
    Serial.println("Fan:on");
    lcd.print("Fan:on");
  } else {
    Serial.println("Fan: off");
    lcd.print("Fan:off");
  }

}
