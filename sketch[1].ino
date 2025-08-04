#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;  // Changed RTC from DS3231 to DS1307 (Wokwi compatible)

const int lightLED = 6;  // LED simulating corridor light
const int buzzer = 5;    // Buzzer

void setup() {
    pinMode(lightLED, OUTPUT);
    pinMode(buzzer, OUTPUT);
    digitalWrite(lightLED, LOW); // Light OFF initially
    digitalWrite(buzzer, LOW);
    Serial.begin(9600);  // Enable serial monitoring
    if (!rtc.begin()) {
        Serial.println("RTC not found!");
        while (1);
    }
    
}
void loop() {
    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    int second = now.second();
    int dayOfWeek = now.dayOfTheWeek(); // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    Serial.print("Day: "); Serial.print(dayOfWeek);
    Serial.print(" Time: "); Serial.print(hour); Serial.print(":"); Serial.print(minute);
    Serial.print(":"); Serial.println(second);
    // Corridor Light Simulation (All days, 6 PM - 6 AM)
    if (hour >= 18 || hour < 6) {
        digitalWrite(lightLED, HIGH); // Turn ON LED
    } else {
        digitalWrite(lightLED, LOW); // Turn OFF LED
    }
    // Precise Buzzer Alarm Timing
    if ((dayOfWeek >= 1 && dayOfWeek <= 5) && hour == 4 && minute == 30 && second == 0) { 
        // Mon-Fri 4:30 AM
        activateBuzzer();
    } else if ((dayOfWeek == 0 || dayOfWeek == 6) && hour == 5 && minute == 30 && second == 0) { 
        // Sat-Sun 5:30 AM
        activateBuzzer();
    }
    delay(1000); // 1-second loop delay
}
void activateBuzzer() {
    Serial.println("Buzzer ON");
    digitalWrite(buzzer, HIGH);
    delay(2000); // 2 seconds
    digitalWrite(buzzer, LOW);
    Serial.println("Buzzer OFF");
}
