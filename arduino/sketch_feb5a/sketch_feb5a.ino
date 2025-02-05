void setup() {
  Serial.begin(115200);
  Serial.println("ESP-EYE Test Start!");
}

void loop() {
  Serial.println("ESP-EYE is running...");
  delay(1000);
}

// select ESP32 Wrover Module 
// change QIO to DIO
//