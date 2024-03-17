#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Create motor objects
AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

// BLUETOOTH SERIAL CONNECTION
SoftwareSerial mySerial(3, 2);

// BASIC ROVER NAVIGATION FUNC
void moveForward() {
  motor3.setSpeed(500);
  motor4.setSpeed(500);
  motor1.setSpeed(500);
  motor2.setSpeed(500);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  motor2.run(BACKWARD);
  motor1.run(BACKWARD);

  delay(100);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
  motor3.run(RELEASE); 
  motor4.run(RELEASE); 
}

void moveBackward() {
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(FORWARD);

  delay(100);
  motor3.setSpeed(0);
  motor2.setSpeed(0);
  motor4.setSpeed(0);
  motor1.setSpeed(0);
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
  motor3.run(RELEASE); 
  motor4.run(RELEASE); 
}

void turnRight() {
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  motor2.run(FORWARD);
  motor1.run(FORWARD);

  delay(100);
  motor3.setSpeed(0);
  motor2.setSpeed(0);
  motor4.setSpeed(0);
  motor1.setSpeed(0);
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
  motor3.run(RELEASE); 
  motor4.run(RELEASE); 
}

void turnLeft() {
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  motor2.run(BACKWARD);
  motor1.run(BACKWARD);

  delay(100);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
  motor3.run(RELEASE); 
  motor4.run(RELEASE); 
}

// USE THIS IF STOP NEEDED
// void stopMovement() {
//   motor1.setSpeed(0);
//   motor2.setSpeed(0);
//   motor3.setSpeed(0);
//   motor4.setSpeed(0);
//   motor1.run(0);
//   motor2.run(0);
//   motor3.run(0);
//   motor4.run(0);
// }


// CAMERA SERVO MOVEMENTS

Servo camSer; 
int camPoser = 30;
bool reverseFlag = false;

void camservo() {
  if (!reverseFlag) {
    // Sweep from 30 to 120 degrees
    camSer.write(camPoser); // Set servo position
    camPoser += 2;
    if (camPoser >= 120) {
      reverseFlag = true; // Set reverse flag to true
    }
  } else {
    // Sweep from 120 to 30 degrees
    camSer.write(camPoser); // Set servo position
    camPoser -= 2;
    if (camPoser <= 30) {
      reverseFlag = false; // Set reverse flag to false
    }
  }
  delay(100); 
  camSer.detach();
}

// GRAPPER SERVO MOVEMENTS

// Servo grapSer;
// int grapPoser = 45;
// bool isOpen = false;

// void grapperservo() {
//   if (!isOpen) {
//     // Open the gripper
//     grapSer.write(40); // Set servo position to fully open
//     isOpen = true; // Update flag to indicate the gripper is open
//   } else {
//     // Close the gripper
//     grapSer.write(0); // Set servo position to fully closed
//     isOpen = false; // Update flag to indicate the gripper is closed
//   }
//   delay(1000);
// }

void setup() {
  // Set up serial communication
  Serial.begin(9600);

  // Begin serial communication with Arduino and HC-05
  mySerial.begin(9600);

  camSer.attach(9);
  // grapSer.attach(10);
}

void loop() {

  if (mySerial.available()) {
    // Read the command from Bluetooth module
    char command = mySerial.read();

    // Perform action based on the command received
    switch (command) {
      case 'U':  // Move forward
        moveForward();
        Serial.println("Moving forward");
        break;
      case 'D':  // Move backward
        moveBackward();
        Serial.println("Moving backward");
        break;
      case 'L':  // Turn left
        turnLeft();
        Serial.println("Turning left");
        break;
      case 'R':  // Turn right
        turnRight();
        Serial.println("Turning right");
        break;
      case 'C':
        camservo();
        Serial.println("Cam");
        break;
      // case 'G':
      //   grapperservo();
      //   Serial.println("Grapper");
      //   break;
      default:
        // Invalid command received
        Serial.println("Invalid command received");
        break;
    }
  }

  delay(20);
}
