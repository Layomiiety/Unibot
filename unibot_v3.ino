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

const int ping_pin = 13;


void turn_left() {
  digitalWrite(fwd_left, HIGH);
  digitalWrite(rvs_left, LOW);
  digitalWrite(fwd_right, LOW);
  digitalWrite(rvs_right, HIGH);
}

void turn_right() {
  digitalWrite(fwd_left, LOW);
  digitalWrite(rvs_left, HIGH);
  digitalWrite(fwd_right, HIGH);
  digitalWrite(rvs_right, LOW);
}

void backward() {
  digitalWrite(fwd_left, HIGH);
  digitalWrite(rvs_left, LOW);
  digitalWrite(fwd_right, HIGH);
  digitalWrite(rvs_right, LOW);
}

void forward() {
  digitalWrite(fwd_left, LOW);
  digitalWrite(rvs_left, HIGH);
  digitalWrite(fwd_right, LOW);
  digitalWrite(rvs_right, HIGH);
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
  digitalWrite(enable_motor, LOW);
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
}

long microsecondsToCentimeters(long microseconds)
{
   // The speed of sound is 340 m/s or 29 microseconds per centimeter.
   // The ping travels out and back, so to find the distance of the
   // object we take half of the distance travelled.
   return microseconds / 29 / 2;
}

void ramp(int left_new_v, int right_new_v, int left_base_v, int right_base_v, int t){
  int steps = 20;
  float t_step = t/steps;
  for (int i = 1; i <= steps; i++){
    analogWrite(enable_left, (((left_new_v - left_base_v)/steps)*i) + left_base_v);
    analogWrite(enable_right, (((right_new_v - right_base_v)/steps)*i) + right_base_v);
    delay(t_step);
  }
}


long read_distance() {
  long duration, distance_cm;

  pinMode(ping_pin, OUTPUT);
  digitalWrite(ping_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_pin, LOW);

  pinMode(ping_pin, INPUT);
  duration = pulseIn(ping_pin, HIGH);
  distance_cm = microsecondsToCentimeters(duration);
  return distance_cm;
}

void loop() {
  long distance_cm;
  delay(1000);
  for (int i = 0; i <= 3; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  delay(1000);

  forward();
  ramp(200, 255, 100, 100, 1000);
  delay(800);
  ramp(100, 100, 200, 255, 1000);
  stop_wheels();

  delay(1000);

  
  extend_arm();

  int dist_1 = 100;
  int dist_2 = 100;
  int dist_3 = 100;
  int av_dist = 100;
  while (digitalRead(bottom_button) == HIGH){
    dist_1 = dist_2;
    dist_2 = dist_3;
    dist_3 = read_distance();
    av_dist = (dist_1 + dist_2 + dist_3)/3;
    while (av_dist < 5) {
      stop_arm();
      delay(500);
      dist_1 = dist_2;
      dist_2 = dist_3;
      dist_3 = read_distance();
      av_dist = (dist_1 + dist_2 + dist_3)/3;
    }
    extend_arm();
    
    delay(10);
  }
  stop_arm();
  
  delay(1000);
  
  backward();
  ramp(255, 150, 100, 100, 1000);
  delay(500);
  ramp(255, 100, 255, 150, 300);

  for (int i = 0; i <= 4; i++){
    turn_left();
    ramp(255, 255, 255, 100, 300);
    delay(1200);
    ramp(255, 150, 255, 255, 100);
    backward();
    delay(500);
  }
  turn_left();
  ramp(255, 255, 255, 150, 300);
  ramp(100, 100, 255, 255, 300);
  stop_wheels();
  
  delay(1000);

  retract_arm();
  while (digitalRead(top_button) == LOW){
     delay(10);
  }
  stop_arm();

  delay(1000000);

}