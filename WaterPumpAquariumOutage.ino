//**********************************************************************************
//    Aquarium Water Pump Auto-Restart after Power Outage
//
//    Developed by: Dom_F0xtrot_
//    Optimized by: Jules
//
//    Version: 1.1
//    Last updated: 2025-09-17
//
//    Project Description:
//    This project uses an Arduino Uno, a water level sensor, and a relay to
//    automatically restart an aquarium filter pump after a power outage.
//    To prevent corrosion and extend the sensor's lifespan, the sensor is only
//    powered on when a reading is being taken.
//
//    Hardware:
//    - Board: Arduino Uno
//    - Water Pump: 5V submersible pump
//    - Water Sensor: T1592
//    - Relay Module: 5V single channel (Active-LOW)
//
//    Wiring:
//    - Water Sensor VCC: D7
//    - Water Sensor GND: GND
//    - Water Sensor Signal: A0
//    - Relay VCC: 5V
//    - Relay GND: GND
//    - Relay Signal: D3
//
//**********************************************************************************

// --- Pin Definitions ---
const int SENSOR_POWER_PIN = 7;
const int SENSOR_ANALOG_PIN = A0;
const int RELAY_PIN = 3;

// --- Constants ---
// The analog reading threshold from the water sensor.
// This value is calibrated manually. A reading ABOVE this threshold indicates
// that the water level is too low, and the pump should be turned off to prevent damage.
const int WATER_LEVEL_THRESHOLD = 300;

// The relay module is Active-LOW, meaning a LOW signal turns it ON and HIGH turns it OFF.
const int PUMP_ON = LOW;
const int PUMP_OFF = HIGH;

// --- Delays and Serial Configuration ---
const long BAUD_RATE = 9600;
const int SENSOR_READ_STABILIZATION_MS = 20; // Time to wait for the sensor to stabilize after powering on.
const unsigned long LOOP_DELAY_MS = 10000;   // Check water level every 10 seconds.


void setup() {
  Serial.begin(BAUD_RATE);

  // Configure pin modes
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Ensure the sensor is off and the pump is off initially for safety.
  digitalWrite(SENSOR_POWER_PIN, LOW);
  digitalWrite(RELAY_PIN, PUMP_OFF);

  Serial.println("System initialized. Pump is OFF.");
  Serial.println("---------------------------------");
}

void loop() {
  // 1. Read the water level from the sensor.
  int waterLevel = readWaterSensor();

  // 2. Decide whether to turn the pump on or off.
  if (waterLevel > WATER_LEVEL_THRESHOLD) {
    // Water level is too low. Turn the pump OFF.
    digitalWrite(RELAY_PIN, PUMP_OFF);
    Serial.print("Water level is LOW. Pump turned OFF. ");
  } else {
    // Water level is sufficient. Turn the pump ON.
    digitalWrite(RELAY_PIN, PUMP_ON);
    Serial.print("Water level is OK. Pump turned ON.  ");
  }

  // 3. Print the current sensor reading for debugging.
  Serial.print("Sensor reading: ");
  Serial.println(waterLevel);

  // 4. Wait before the next reading.
  delay(LOOP_DELAY_MS);
}

/**
 * @brief Reads the value from the water level sensor.
 *
 * This function powers the sensor on, waits briefly for the reading to stabilize,
 * takes an analog reading, and then powers the sensor off to prevent corrosion.
 *
 * @return The analog reading from the water sensor (0-1023).
 */
int readWaterSensor() {
  digitalWrite(SENSOR_POWER_PIN, HIGH);     // Power the sensor ON
  delay(SENSOR_READ_STABILIZATION_MS);      // Wait for the reading to stabilize
  int sensorValue = analogRead(SENSOR_ANALOG_PIN); // Read the analog value
  digitalWrite(SENSOR_POWER_PIN, LOW);      // Power the sensor OFF
  return sensorValue;
}
