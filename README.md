# Arduino-Days-Project
Obstacle Avoidance Car:-

1. Description:- Small car that moves forward and avoids obstacles using an ultrasonic sensor. 
When it detects an obstacle, it stop, turn left, and continue moving. 

2. Components Used:- 2x DC motor, 1x Arduino uno, 1x 9v battery, Ultraonic Distance Sensor, Micro Server, LED RGB, 3x 330ohm resistor, H-bridge Motor Driver, Small Breadboard, wires(physical).

3. Simulation Link:- https://www.tinkercad.com/things/6SIxzr7VbVK/editel?sharecode=gMKBtKaR1s162qjC0m3BsPRQuRIN7_SITc2H6_6ZC_w

4. Code explained:-

Initializes motors, ultrasonic sensor, RGB LED, and servo motor.

Starts moving the car forward and positions the servo at 90° (center).

Measures distance using the ultrasonic sensor.

If distance > 5 cm → Move forward, LED Green 

If distance == 5 cm → Stop, LED Red 

If distance < 5 cm →

Servo scans left & right to find a clear path.

Car turns in the direction with more space.

Motor control: Move forward, stop, turn left/right.

Ultrasonic sensor: Measure distance, scan left/right.

RGB LED: Green when moving, Red when stopped.
