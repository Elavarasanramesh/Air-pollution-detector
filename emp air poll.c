#include <Wire.h> 
#include <U8x8lib.h> 
// Initialize OLED display 
U8X8_SSD1306_128X64_NONAME_SW_I2C display(A5, A4, 
U8X8_PIN_NONE); 
const int MQ135_PIN = A0;  // MQ-135 sensor pin 
const int BUZZER_PIN = 3;  // Buzzer pin 
const float THRESHOLD = 2.5;  // Air pollution threshold 
void setup() { 
display.begin(); 
display.setPowerSave(0); 
display.setFont(u8x8_font_chroma48medium8_r); 
Serial.begin(9600);  // Start serial communication 
pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer as output 
display.drawString(0, 0, "Air Monitor Ready!"); 
} 
18 
void loop() { 
int sensorValue = analogRead(MQ135_PIN);  // Read MQ-135 sensor 
float airQuality = sensorValue * (5.0 / 1023.0);  // Convert reading to 
voltage 
display.clear(); 
display.drawString(0, 0, "Air Quality:"); 
display.setCursor(0, 1); 
display.print(airQuality); 
Serial.print("Air Quality: "); 
Serial.println(airQuality); 
// Check if pollution exceeds threshold 
if (airQuality > THRESHOLD) { 
digitalWrite(BUZZER_PIN, HIGH);  // Activate buzzer 
display.drawString(0, 2, "WARNING: HIGH!"); 
delay(500);  // Buzzer ON for 1 sec 
digitalWrite(BUZZER_PIN, LOW);   // Turn off buzzer 
} else { 
digitalWrite(BUZZER_PIN, LOW);  // Ensure buzzer remains off 
} 
delay(2000);  // Wait before next reading 
}