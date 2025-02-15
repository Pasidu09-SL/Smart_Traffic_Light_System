// Define pins for traffic lights

// Road 1 (3 lanes)
const int r1LeftRed = 2, r1LeftYellow = 3, r1LeftGreen = 4;
const int r1MidRed = 5, r1MidYellow = 6, r1MidGreen = 7;
const int r1RightRed = 8, r1RightYellow = 9, r1RightGreen = 10;
const int p1Red = 11, p1Green = 12;  // Pedestrian lights

// Road 2 (3 lanes)
const int r2LeftRed = 22, r2LeftYellow = 23, r2LeftGreen = 24;
const int r2MidRed = 25, r2MidYellow = 26, r2MidGreen = 27;
const int r2RightRed = 28, r2RightYellow = 29, r2RightGreen = 30;
const int p2Red = 31, p2Green = 32;

// Road 3 (3 lanes)
const int r3LeftRed = 33, r3LeftYellow = 34, r3LeftGreen = 35;
const int r3MidRed = 36, r3MidYellow = 37, r3MidGreen = 38;
const int r3RightRed = 39, r3RightYellow = 40, r3RightGreen = 41;
const int p3Red = 42, p3Green = 43;

// Road 4 (3 lanes)
const int r4LeftRed = 44, r4LeftYellow = 45, r4LeftGreen = 46;
const int r4MidRed = 47, r4MidYellow = 48, r4MidGreen = 49;
const int r4RightRed = 50, r4RightYellow = 51, r4RightGreen = 52;
const int p4Red = A0, p4Green = A1;  // Analog pins used as digital

// Timing constants (in milliseconds)
const int greenTime = 20000, yellowTime = 3000, leftTurnTime = 10000;
const int pedestrianTime = 15000, safetyDelay = 1000;

void setup() {
  Serial.begin(9600);  // Initialize Serial for debugging

  // Initialize all traffic light pins as OUTPUTS
  int allPins[] = {r1LeftRed, r1LeftYellow, r1LeftGreen, r1MidRed, r1MidYellow, r1MidGreen,
                   r1RightRed, r1RightYellow, r1RightGreen, p1Red, p1Green,
                   r2LeftRed, r2LeftYellow, r2LeftGreen, r2MidRed, r2MidYellow, r2MidGreen,
                   r2RightRed, r2RightYellow, r2RightGreen, p2Red, p2Green,
                   r3LeftRed, r3LeftYellow, r3LeftGreen, r3MidRed, r3MidYellow, r3MidGreen,
                   r3RightRed, r3RightYellow, r3RightGreen, p3Red, p3Green,
                   r4LeftRed, r4LeftYellow, r4LeftGreen, r4MidRed, r4MidYellow, r4MidGreen,
                   r4RightRed, r4RightYellow, r4RightGreen, p4Red, p4Green};

  for (int i = 0; i < sizeof(allPins) / sizeof(allPins[0]); i++) {
    pinMode(allPins[i], OUTPUT);
    digitalWrite(allPins[i], LOW);  // Start with all lights OFF
  }

  Serial.println("Traffic Light System Initialized.");
  allRed();  // Set initial state
}

// Function to turn all lights RED (Safe State)
void allRed() {
  int redLights[] = {r1LeftRed, r1MidRed, r1RightRed, r2LeftRed, r2MidRed, r2RightRed,
                     r3LeftRed, r3MidRed, r3RightRed, r4LeftRed, r4MidRed, r4RightRed,
                     p1Red, p2Red, p3Red, p4Red};

  for (int i = 0; i < sizeof(redLights) / sizeof(redLights[0]); i++) {
    digitalWrite(redLights[i], HIGH);
  }

  Serial.println("All Lights Set to RED.");
}

// Function to allow North-South Left Turn
void northSouthLeftTurn() {
  Serial.println("North-South Left Turn Phase Started.");
  digitalWrite(r1LeftGreen, HIGH);
  digitalWrite(r3LeftGreen, HIGH);
  delay(leftTurnTime);
  digitalWrite(r1LeftGreen, LOW);
  digitalWrite(r3LeftGreen, LOW);
}

// Function to allow North-South Straight and Right
void northSouthStraightAndRight() {
  Serial.println("North-South Straight and Right Phase Started.");
  digitalWrite(r1MidGreen, HIGH);
  digitalWrite(r1RightGreen, HIGH);
  digitalWrite(r3MidGreen, HIGH);
  digitalWrite(r3RightGreen, HIGH);
  delay(greenTime);
  digitalWrite(r1MidGreen, LOW);
  digitalWrite(r1RightGreen, LOW);
  digitalWrite(r3MidGreen, LOW);
  digitalWrite(r3RightGreen, LOW);
}

// Function to allow East-West Left Turn
void eastWestLeftTurn() {
  Serial.println("East-West Left Turn Phase Started.");
  digitalWrite(r2LeftGreen, HIGH);
  digitalWrite(r4LeftGreen, HIGH);
  delay(leftTurnTime);
  digitalWrite(r2LeftGreen, LOW);
  digitalWrite(r4LeftGreen, LOW);
}

// Function to allow East-West Straight and Right
void eastWestStraightAndRight() {
  Serial.println("East-West Straight and Right Phase Started.");
  digitalWrite(r2MidGreen, HIGH);
  digitalWrite(r2RightGreen, HIGH);
  digitalWrite(r4MidGreen, HIGH);
  digitalWrite(r4RightGreen, HIGH);
  delay(greenTime);
  digitalWrite(r2MidGreen, LOW);
  digitalWrite(r2RightGreen, LOW);
  digitalWrite(r4MidGreen, LOW);
  digitalWrite(r4RightGreen, LOW);
}

// Function to print active LEDs
void printActiveLEDs() {
  Serial.println("Active LEDs:");
  int allPins[] = {r1LeftGreen, r1MidGreen, r1RightGreen, r2LeftGreen, r2MidGreen, r2RightGreen,
                   r3LeftGreen, r3MidGreen, r3RightGreen, r4LeftGreen, r4MidGreen, r4RightGreen};

  for (int i = 0; i < sizeof(allPins) / sizeof(allPins[0]); i++) {
    if (digitalRead(allPins[i]) == HIGH) {
      Serial.print("LED ON: ");
      Serial.println(allPins[i]); // Print pin number of active LED
    }
  }
}

void loop() {
  allRed();
  Serial.println("All Red - Safety Phase");
  delay(safetyDelay);

  printActiveLEDs();

  northSouthLeftTurn();
  Serial.println("North-South Left Turn Complete");
  delay(safetyDelay);
  printActiveLEDs();

  northSouthStraightAndRight();
  Serial.println("North-South Straight and Right Complete");
  delay(safetyDelay);
  printActiveLEDs();

  eastWestLeftTurn();
  Serial.println("East-West Left Turn Complete");
  delay(safetyDelay);
  printActiveLEDs();

  eastWestStraightAndRight();
  Serial.println("East-West Straight and Right Complete");
  delay(safetyDelay);
  printActiveLEDs();
}
