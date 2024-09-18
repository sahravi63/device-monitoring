// Define pins
const int voltagePin = A0;  // Voltage sensor connected to A0
const int currentPin = A1;  // Current sensor (ACS712) connected to A1
const int tempPin = A2;     // Temperature sensor (LM35) connected to A2

// Calibration values for the sensors
float voltageDividerRatio = 5.0; // Change this based on your voltage divider setup
float ACS712_Sensitivity = 0.185; // Sensitivity in V/A for 5A version
float voltageReference = 5.0;     // Arduino analog reference voltage
float tempFactor = 0.01;          // LM35 temperature sensor scaling factor (10 mV per °C)

// Variable to store sensor readings
float voltageReading;
float currentReading;
float tempReading;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read voltage sensor value
  voltageReading = analogRead(voltagePin);
  float batteryVoltage = (voltageReading / 1023.0) * voltageReference * voltageDividerRatio;
  
  // Read current sensor value
  currentReading = analogRead(currentPin);
  float voltageOffset = (currentReading / 1023.0) * voltageReference;
  float current = (voltageOffset - 2.5) / ACS712_Sensitivity;  // Offset voltage for ACS712
  
  // Read temperature sensor value
  tempReading = analogRead(tempPin);
  float temperature = (tempReading / 1023.0) * voltageReference / tempFactor;
  
  // Print the values to Serial Monitor
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage);
  Serial.println(" V");
  
  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  // Wait a second before next reading
  delay(1000);
}