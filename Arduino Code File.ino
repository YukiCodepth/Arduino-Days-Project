#include <Servo.h>

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// Motor Driver Pins (L293D)
#define ENA 3    
#define ENB 5    
#define IN1 2    
#define IN2 4    
#define IN3 6    
#define IN4 7    

// RGB LED Pins
#define RED_LED 11
#define GREEN_LED 12
#define BLUE_LED 13

// Servo Motor Pin
#define SERVO_PIN 8  

Servo ultrasonicServo;

void setup() {
    Serial.begin(9600);

    // Motor Pins
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Ultrasonic Sensor Pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // RGB LED Pins
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    // Setup Servo
    ultrasonicServo.attach(SERVO_PIN);
    ultrasonicServo.write(90); // Start at center position

    moveForward();
}

void loop() {
    int distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 10) {
        // ✅ Move forward and set LED to solid green
        moveForward();
        setRGB(0, 255, 0);  // Green
    } 
    else if (distance > 5 && distance <= 10) {
        // ✅ Flash red (faster as it gets closer)
        setRGB(255, 0, 0);  // Red
        delay(300 - (distance * 20));  // Dynamic flashing
        setRGB(0, 0, 0);
        delay(300 - (distance * 20));
    } 
    else {
        // ✅ Stop and turn left
        Serial.println("Obstacle detected! Turning left...");
        stopMotors();
        setRGB(255, 0, 0);  // Solid Red
        delay(500);
        
        // Check left and right
        int leftDistance = scanLeft();
        int rightDistance = scanRight();

        if (rightDistance > leftDistance) {
            turnRight();
        } else {
            turnLeft();
        }
        
        delay(500); // ✅ Added delay after turning
    }
}

// Function to measure distance using Ultrasonic Sensor
int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

// Scan Left
int scanLeft() {
    ultrasonicServo.write(0);
    delay(500);
    int distance = getDistance();
    ultrasonicServo.write(90);
    return distance;
}

// Scan Right
int scanRight() {
    ultrasonicServo.write(180);
    delay(500);
    int distance = getDistance();
    ultrasonicServo.write(90);
    return distance;
}

// Move Forward
void moveForward() {
    Serial.println("Moving Forward...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 170); // 🔼 Increased power
    analogWrite(ENB, 170);
}

// Stop Motors
void stopMotors() {
    Serial.println("Stopping...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Turn Left
void turnLeft() {
    Serial.println("Turning Left...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(700);
}

// Turn Right
void turnRight() {
    Serial.println("Turning Right...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(700);
}

// ✅ Set RGB LED Color with flashing logic
void setRGB(int r, int g, int b) {
    analogWrite(RED_LED, r);
    analogWrite(GREEN_LED, g);
    analogWrite(BLUE_LED, 0);  // ✅ Always keep BLUE off
}
