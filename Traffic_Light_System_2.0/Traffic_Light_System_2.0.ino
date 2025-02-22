// Define pins for traffic lights
struct TrafficLight {
    int red, yellow, green;
};

// North (Road 1)     red, yellow, green
TrafficLight  northL = {2, 3, 4}, 
              northM = {5, 6, 7}, 
              northR = {8, 9, 10};
              int p1Red = 11, p1Green = 12;  // Pedestrian lights

// East (Road 2)      red, yellow, green
TrafficLight  eastL = {22, 23, 24}, 
              eastM = {25, 26, 27}, 
              eastR = {28, 29, 30};
              int p2Red = 31, p2Green = 32;

// South (Road 3)      red, yellow, green
TrafficLight  southL = {33, 34, 35}, 
              southM = {36, 37, 38}, 
              southR = {39, 40, 41};
              int p3Red = 42, p3Green = 43;

// West (Road 4)      red, yellow, green
TrafficLight  westL = {44, 45, 46}, 
              westM = {47, 48, 49}, 
              westR = {50, 51, 52};
              int p4Red = A0, p4Green = A1; // Analog pins as digital

// Sensor Pins
const int PIR_1 = A2, PIR_2 = A9; //North (A2 - A8)   East(A9 - A15)
const int ULTRA_TRIGGER[] = {A3, A5, A7, A10, A12, A14};
const int ULTRA_ECHO[] = {A4, A6, A8, A11, A13, A15};
//North PIR Senseor - A2
//North Left lane Ultra Sonic Sensor Trigger - A3
//North Left lane Ultra Sonic Sensor Echo - A4
//North Middle lane Ultra Sonic Sensor Trigger - A5
//North Middle lane Ultra Sonic Sensor Echo - A6
//North Right lane Ultra Sonic Sensor Trigger - A7
//North Right lane Ultra Sonic Sensor Echo - A8

//East PIR Senseor - A9
//East Left lane Ultra Sonic Sensor Trigger - A10
//East Left lane Ultra Sonic Sensor Echo - A11
//East Middle lane Ultra Sonic Sensor Trigger - A12
//East Middle lane Ultra Sonic Sensor Echo - A13
//East Right lane Ultra Sonic Sensor Trigger - A14
//East Right lane Ultra Sonic Sensor Echo - A15


// Timing constants (milliseconds)
const int greenTime = 20000, yellowTime = 3000, rightTurnTime = 10000;
const int pedestrianTime = 15000, safetyDelay = 1000;

// Enum for light states
enum LightState { RED, YELLOW, GREEN };

// Function to control traffic lights
void setTrafficLight(TrafficLight light, LightState state) {
    digitalWrite(light.red, state == RED ? HIGH : LOW);
    digitalWrite(light.yellow, state == YELLOW ? HIGH : LOW);
    digitalWrite(light.green, state == GREEN ? HIGH : LOW);
}

// Transition  Red → Yellow → Green
void switchToGreen(TrafficLight light){
  setTrafficLight(light, 0); // Red
  delay(safetyDelay);
  setTrafficLight(light, 1); // Yellow
  delay(yellowTime);
  setTrafficLight(light, 2); // Green
}

void setAllRed(){
  TrafficLight lights[] = {northL, northM, northR, eastL, eastM, eastR, southL, southM, southR, westL, westM, westR};
  for (int i = 0; i < sizeof(lights) / sizeof(lights[0]); i++) {
    // Check if the current light is green
    if (digitalRead(lights[i].green) == HIGH) {
    // Transition: Green → Yellow → Red
    setTrafficLight(lights[i], YELLOW); // Set to yellow
    delay(yellowTime); // Wait for yellow time
    setTrafficLight(lights[i], RED); // Set to red
    } else {
      // If not green, set directly to red
      setTrafficLight(lights[i], RED);
    }
  }
  digitalWrite(p1Green,LOW);
  digitalWrite(p2Green,LOW);
  digitalWrite(p3Green,LOW);
  digitalWrite(p4Green,LOW);

  digitalWrite(p1Red,HIGH);
  digitalWrite(p2Red,HIGH);
  digitalWrite(p3Red,HIGH);
  digitalWrite(p4Red,HIGH);
}

//PHASE 1: N-S Through Traffic
void phase1_NSThrough() {

    switchToGreen(northL);
    switchToGreen(southL);

    switchToGreen(northM);
    switchToGreen(southM);
    
    delay(greenTime);
}

//PHASE 2: N-S Right Traffic
void phase2_NSRight() {

    switchToGreen(northR);
    switchToGreen(southR);
    
    delay(greenTime);
}

//PHASE 3: E-W Through Traffic
void phase3_EWThrough() {

    switchToGreen(eastL);
    switchToGreen(westL);

    switchToGreen(eastM);
    switchToGreen(westM);
    
    delay(greenTime);
}

//PHASE 4: E-W Through Traffic
void phase4_EWRight() {

    switchToGreen(eastR);
    switchToGreen(westR);
    
    delay(greenTime);
}

//PHASE 5: Predestrian Phase AllDirection Traffic
void phase5_PedestrianAllDirection() {


  digitalWrite(p1Red,LOW);
  digitalWrite(p2Red,LOW);
  digitalWrite(p3Red,LOW);
  digitalWrite(p4Red,LOW);

  delay(safetyDelay);

  digitalWrite(p1Green,HIGH);
  digitalWrite(p2Green,HIGH);
  digitalWrite(p3Green,HIGH);
  digitalWrite(p4Green,HIGH);

  delay(pedestrianTime);
}

void setup() {
    Serial.begin(9600);

    // Initialize all traffic light pins
    TrafficLight lights[] = {northL, northM, northR, eastL, eastM, eastR, southL, southM, southR, westL, westM, westR};
    for (TrafficLight light : lights) {
        pinMode(light.red, OUTPUT);
        pinMode(light.yellow, OUTPUT);
        pinMode(light.green, OUTPUT);
    }

    // Initialize pedestrian lights
    int pedestrianLights[] = {p1Red, p1Green, p2Red, p2Green, p3Red, p3Green, p4Red, p4Green};
    for (int pin : pedestrianLights) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    // Initialize sensors
    pinMode(PIR_1, INPUT);
    pinMode(PIR_2, INPUT);
    for (int i = 0; i < 6; i++) {
        pinMode(ULTRA_TRIGGER[i], OUTPUT);
        pinMode(ULTRA_ECHO[i], INPUT);
    }

    Serial.println("Traffic Light System Initialized.");
}

void loop() {
  setAllRed();
  phase1_NSThrough();
  setAllRed();
  phase2_NSRight();
  setAllRed();
  phase3_EWThrough();
  setAllRed();
  phase4_EWRight();
  setAllRed();
  phase5_PedestrianAllDirection();
  setAllRed();
}
