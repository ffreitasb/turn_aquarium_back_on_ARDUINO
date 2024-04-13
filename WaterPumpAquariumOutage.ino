//**********************************************************************************
/*
Dveloped by Dom_F0xtrot_
-----
Initial release version 1.0 @ 13.04.24
-----
*/
//**********************************************************************************

/*
One well-known issue with these water sensors is that they have a shorter lifespan because they are constantly exposed to moisture.
Moreover, constantly applying power to the sensor while immersed in water significantly accelerates the rate of corrosion.
*/

// Water Sensor pins 
#define sensorPower 7
#define sensorPin A0
// Relay pin
int Relay = 3;

int lowerFilter = 300;  //value to turn on the relay and water pump (manually calibrated)

int val = 0;  // Value for storing water level

void setup() {
	
  // Set Sensor Power (D7) and Relay (D3) as "OUTPUT"
	pinMode(sensorPower, OUTPUT);
	pinMode(Relay, OUTPUT); 
  
  digitalWrite(sensorPower, LOW); // Set to LOW so no power flows through the sensor
	digitalWrite(Relay, LOW); // turns on the relay

	Serial.begin(9600);
}

void loop() {
  
	int level = readSensor(); //get the reading from the function below and print it
	
  if (level > lowerFilter) {
    Serial.print("Filter off! ");
    digitalWrite(Relay, HIGH); // turns on the relay
  }
  else {
    digitalWrite(Relay, LOW); // turns off the relay
  }

	Serial.print("Sensor read: ");
	Serial.println(level);
	
	delay(10000);  // checks the sensor every 10 seconds
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(20);					          		// wait 20 milliseconds
	val = analogRead(sensorPin);	  	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;						          	// send current reading
}
