/*
 * How to test encoder with Arduino
 * url: http://osoyoo.com/?p=30267
 */
#include <AFMotor.h>  //Servo library 		//initialize a servo object for the connected servo
int current_angle = 0;
AF_DCMotor motor_front(2, MOTOR12_2KHZ);  // create motor #2, 64KHz pwm
AF_DCMotor motor_back(1, MOTOR12_2KHZ);
#define outputA 6
#define outputB 7
int counter = 0;
int aState;
int aLastState;
void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  Serial.begin(9600);  // set up Serial library at 9600 bps
  motor_leftfront.setSpeed(200);
  motor_leftback.setSpeed(200);
  Serial.begin(9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}


void turn_left(int t) {
  motor_front.run(FORWARD);
  motor_back.run(BACKWARD);
  delay(t);
}

void turn_right(int t) {
  motor_front.run(BACKWARD);
  motor_back.run(FORWARD);
  delay(t);
}

void move_forward(int t) {
  motor_front.run(FORWARD);
  motor_back.run(FORWARD);
  delay(t);
}

void move_backward(int t) {
  motor_front.run(BACKWARD);
  motor_back.run(BACKWARD);
  delay(t);
}

void stopwheels() {
  motor_front.run(RELEASE);
  motor_back.run(RELEASE);
}

void extend_arms()
void release_arms()
void regular(){
  extend_arms()
  move_forward(200)
  turn_left(180)
  move_forward(200)
  turn_left(180)
  release_arms()
  move_forward(200)
  turn_left(180)
  move_forward(200)
  turn_left(180) 
}
void loop() {
  aState = digitalRead(outputA);  // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) {
      counter++;
      regular()
    } else {
      counter--;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  }
  aLastState = aState;  
}

