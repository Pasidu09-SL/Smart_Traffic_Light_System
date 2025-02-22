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

// Transition Green → Yellow → Red
void switchToRed(TrafficLight light){
  setTrafficLight(light, 2); // Green
  delay(greenTime);
  setTrafficLight(light, 1); // Yellow
  delay(yellowTime);
  setTrafficLight(light, 0); // Red
}

//PHASE 1: N-S Through Traffic
void phase1_NSThrough() {
    switchToGreen(northM);
    switchToGreen(southM);
    
    switchToRed(northL);
    switchToRed(northR);
    
    switchToRed(southL);
    switchToRed(southR);
    
    switchToRed(eastM);
    switchToRed(westM);
    
    delay(greenTime);
}

void setup() {
    Serial.begin(9600);

    // Initialize all traffic light pins
    TrafficLight lights[] = {northL, northM, northR, eastL, eastM, eastR, southL, southM, southR, westL, westM, westR};
    for (TrafficLight light : lights) {
        pinMode(light.red, OUTPUT);
        pinMode(light.yellow, OUTPUT);
        pinMode(light.green, OUTPUT);
        setTrafficLight(light, RED); // Start with all red
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
  phase1_NSThrough();
}
