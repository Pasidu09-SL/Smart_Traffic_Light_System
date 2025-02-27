/**
   HC-SR04 Distance Sensor Example
   https://wokwi.com/arduino/projects/304444938977804866
*/

const int ULTRA_TRIGGER[] = {A3, A5, A7, A10, A12, A14};
const int ULTRA_ECHO[] = {A4, A6, A8, A11, A13, A15};

void setup() {
  Serial.begin(9600);
      for (int i = 0; i < 6; i++) {
        pinMode(ULTRA_TRIGGER[i], OUTPUT);
        pinMode(ULTRA_ECHO[i], INPUT);
    }
}
long getDistance(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read pulse duration
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 58; // Convert to cm

    // Lane names based on trigger pin
    const char* laneNames[] = {
        "North Left Side",   // Trigger pin A3
        "North Middle Side", // Trigger pin A5
        "North Right Side",  // Trigger pin A7
        "East Left Side",    // Trigger pin A10
        "East Middle Side",  // Trigger pin A12
        "East Right Side"    // Trigger pin A14
    };

    // Find the trigger pin index
    int index = -1;
    for (int i = 0; i < 6; i++) {
        if (ULTRA_TRIGGER[i] == triggerPin) {
            index = i;
            break;
        }
    }

    // Print lane information if detected
    if (index != -1) {
        Serial.print("Vehicle detected at ");
        Serial.print(laneNames[index]);
        Serial.print(": ");
        Serial.print(distance);
        Serial.println(" cm");
        Serial.println("-----------------------------------------");
    }

    return distance;
}


void loop() {
  // Start a new measurement:
  // digitalWrite(PIN_TRIG, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(PIN_TRIG, LOW);

  // // Read the result:
  // int duration = pulseIn(PIN_ECHO, HIGH);
  // Serial.print("Distance in CM: ");
  // Serial.println(duration / 58);
  // Serial.print("Distance in inches: ");
  // Serial.println(duration / 148);

  getDistance(ULTRA_TRIGGER[2],ULTRA_ECHO[2]);
  

  delay(1000);
}