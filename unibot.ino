const int fwd_left = 2;
const int rvs_left = 4;
const int enable_left = 3;

const int enable_right = 5;
const int fwd_right = 7;
const int rvs_right = 6;

const int motor_fwd = 8;
const int motor_rvs = 9;
const int enable_motor = 10;

const int top_button = 12;
const int bottom_button = 11;

void turn_left(int left_v, int right_v, int dur) {
  digitalWrite(fwd_left, HIGH);
  digitalWrite(rvs_left, LOW);
  digitalWrite(fwd_right, LOW);
  digitalWrite(rvs_right, HIGH);
  ramp_up(left_v,right_v, 1000, 50);
  delay(dur);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
}

void turn_right(int left_v, int right_v, int dur) {
  digitalWrite(fwd_left, LOW);
  digitalWrite(rvs_left, HIGH);
  digitalWrite(fwd_right, HIGH);
  digitalWrite(rvs_right, LOW);
  ramp_up(left_v,right_v, 1000, 50);
  delay(dur);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);

}

void forward(int inside_v, int outside_v, int dur) {
  digitalWrite(fwd_left, HIGH);
  digitalWrite(rvs_left, LOW);
  digitalWrite(fwd_right, HIGH);
  digitalWrite(rvs_right, LOW);
  ramp_up(inside_v,outside_v, 1000, 50);
  delay(dur);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
}

void reverse(int inside_v, int outside_v, int dur) {
  digitalWrite(fwd_left, LOW);
  digitalWrite(rvs_left, HIGH);
  digitalWrite(fwd_right, LOW);
  digitalWrite(rvs_right, HIGH);
  ramp_up(inside_v,outside_v, 1000, 50);
  delay(dur);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
}

void stop_wheels() {
  digitalWrite(enable_left, LOW);
  digitalWrite(enable_right, LOW);
}

void extend_arm() {
  digitalWrite(motor_fwd, HIGH);
  digitalWrite(motor_rvs, LOW);
  digitalWrite(enable_motor, HIGH);
}

void retract_arm() {
  digitalWrite(motor_fwd, LOW);
  digitalWrite(motor_rvs, HIGH);
  digitalWrite(enable_motor, HIGH);
}

void stop_arm() {
  analogWrite(enable_motor, 0);
  digitalWrite(motor_fwd, LOW);
  digitalWrite(motor_rvs, LOW);
}

void setup() {
  pinMode(fwd_left, OUTPUT);
  pinMode(rvs_left, OUTPUT);
  pinMode(enable_left, OUTPUT);
  pinMode(fwd_right, OUTPUT);
  pinMode(rvs_right, OUTPUT);
  pinMode(enable_right, OUTPUT);
  pinMode(top_button, INPUT_PULLUP);
  pinMode(bottom_button, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
   
}

void ramp_up(int inner, int outer,int t, int steps){
  for (int i = 1;i <= steps; i++){
    analogWrite(enable_left, outer/steps*i);
    analogWrite(enable_right, inner/steps*i);
    delay(t/steps);
  }
}
void ramp_down(int inner, int outer,int t, int steps){
  for (int i = steps;i >0; i--){
    analogWrite(enable_left, outer/steps*i);
    analogWrite(enable_right, inner/steps*i);
  }
}

void loop() {
  // extend_arm();
  // while (digitalRead(bottom_button) == HIGH){
  //   delay(10);
  // }
  // stop_arm();
  delay(1000);
  forward(255,0,500);
  delay(1000);
  turn_left(55,255,1000);
  delay(1000);
  reverse(255,0,500);
  // delay(1000);
  // retract_arm();
  // while (digitalRead(top_button) == LOW){
  //   delay(10);
  // }
  // stop_arm();
  delay(1000);
  turn_right(255,255,1000);
  delay(1000);
}