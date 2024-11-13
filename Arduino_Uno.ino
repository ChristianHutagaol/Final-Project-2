#include <EEPROM.h>
#include <GravityTDS.h>
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
#define TdsSensorPin A1
#define PhSensorPin A0
#define relayPin 5
#define relayPin2 6
#define relayPin3 7
#define relayPin4 8


float PH4 = 3.5;
float PH7 = 3.1;

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
GravityTDS gravityTds;
DallasTemperature sensors(&oneWire);
float temperature = 25, tdsValue = 0, po = 0;

void setup() {
    Serial.begin(115200);
    sensors.begin();
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  

    pinMode(PhSensorPin, INPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(relayPin2, OUTPUT);
    pinMode(relayPin3, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Kelompok 2  ");
    lcd.setCursor(0, 1);
    lcd.print("Hydroponik Otomatis");
    delay(2000);
    lcd.clear();
}

void loop() {
    sensors.requestTemperatures();
    gravityTds.setTemperature(sensors.getTempCByIndex(0));
    gravityTds.update();
    tdsValue = gravityTds.getTdsValue();
    
    int nilai_analog_PH = analogRead(PhSensorPin);
    double TeganganPh = 5.0 / 1024.0 * nilai_analog_PH;
    double PH_step = (PH4 - PH7) / 3.0;
    po = 7.00 + ((PH7 - TeganganPh) / PH_step);

   

    if (tdsValue < 560) {
      digitalWrite(relayPin, LOW);
    } else {
      digitalWrite(relayPin, HIGH);
    }

    if (tdsValue > 840) {
      digitalWrite(relayPin4, LOW);
        
    } else {
      digitalWrite(relayPin4, HIGH);
    }


     if (po < 6) {
        digitalWrite(relayPin2, LOW);
    } else {
        digitalWrite(relayPin2, HIGH);
    }

    if (po > 7) {
        digitalWrite(relayPin3, LOW);
    } else {
        digitalWrite(relayPin3, HIGH);
    }

    Serial.print(po);
    Serial.print(",");
    Serial.print(tdsValue);

    String tdsString = String(tdsValue, 0);
    String tempString = String(sensors.getTempCByIndex(0), 0);
    String poString = String(po, 2);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TDS : ");
    lcd.print(tdsString);
    lcd.print(" ppm");

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempString);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(10, 1);
    lcd.print("pH:");
    lcd.print(poString);
    

    delay(500);
}
