#include <Servo.h>

// Pin definitions
const int trigPin = 9;       // Ultrasonic sensor Trig pin
const int echoPin = 10;      // Ultrasonic sensor Echo pin
const int motorLeft1 = 2;    // L293D IN1 (Left Motor)
const int motorLeft2 = 3;    // L293D IN2 (Left Motor)
const int motorRight1 = 4;   // L293D IN3 (Right Motor)
const int motorRight2 = 5;   // L293D IN4 (Right Motor)
const int redPin = 6;        // RGB LED Red
const int greenPin = 11;     // RGB LED Green
const int bluePin = 12;      // RGB LED Blue
const int servoPin = 8;      // Servo motor pin

Servo ultrasonicServo;

void setup() {
    Serial.begin(9600);

    // Motor setup
    pinMode(motorLeft1, OUTPUT);
    pinMode(motorLeft2, OUTPUT);
    pinMode(motorRight1, OUTPUT);
    pinMode(motorRight2, OUTPUT);

    // Ultrasonic setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // RGB LED setup
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // Servo setup
    ultrasonicServo.attach(servoPin);
    ultrasonicServo.write(90); // Start at center position

    moveForward();
}

// Function to get distance from ultrasonic sensor
long getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

// Move forward
void moveForward() {
    Serial.println("Moving forward...");
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);
}

// Stop car
void stopCar() {
    Serial.println("Stopping...");
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorRight2, LOW);
}

// Turn left
void turnLeft() {
    Serial.println("Turning left...");
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, HIGH);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);
    delay(700);
}

// Turn right
void turnRight() {
    Serial.println("Turning right...");
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorRight2, HIGH);
    delay(700);
}

// Servo scan left
int scanLeft() {
    ultrasonicServo.write(0);
    delay(500);
    int distance = getDistance();
    Serial.print("Left distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    ultrasonicServo.write(90);
    return distance;
}

// Servo scan right
int scanRight() {
    ultrasonicServo.write(180);
    delay(500);
    int distance = getDistance();
    Serial.print("Right distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    ultrasonicServo.write(90);
    return distance;
}

// RGB LED control
void setRGB(int red, int green) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, 0);  // Keep blue off
}

void loop() {
    long distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 10) {
        // Move forward and set LED to green
        moveForward();
        setRGB(0, 255);  // Green
    } 
    else if (distance > 5 && distance <= 10) {
        // Flash red (faster as it gets closer)
        Serial.println("Obstacle detected!");
        setRGB(255, 0);  // Red
        delay(300 - (distance * 20));
        setRGB(0, 0);
        delay(300 - (distance * 20));
    } 
    else {
        // Stop and scan left and right before turning
        Serial.println("Obstacle detected! Scanning left and right...");
        stopCar();
        setRGB(255, 0);  // Solid Red
        delay(500);

        int leftDistance = scanLeft();
        int rightDistance = scanRight();

        if (rightDistance > leftDistance) {
            turnRight();
        } else {
            turnLeft();
        }
    }
}

