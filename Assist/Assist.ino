//Khai báo động cơ di chuyển 
const int motor1pin1 = 2;
const int motor1pin2 = 3;
const int motor2pin1 = 4;
const int motor2pin2 = 5;

//Khai báo động cơ lấy bóng
const int motor_took = 6;

//Khai báo xung động cơ di chuyển 
const int PWM1 = 9;
const int PWM2 = 10;

//Khai báo xung động cơ lấy bóng 
const int PWM3 = 11;

void motor_move(bool int1, bool int2, bool int3, bool int4, int speed1, int speed2){
  digitalWrite(motor1pin1, int1);
  digitalWrite(motor1pin2, int2);
  digitalWrite(motor2pin1, int3);
  digitalWrite(motor2pin2, int4);

  analogWrite(PWM1, speed1); //ENA pin
  analogWrite(PWM2, speed2); //ENB pin
}

void motor_took(bool int1, bool int2, int speed){
  digitalWrite(motor1pin1, int1);
  digitalWrite(motor1pin2, int2);

  analogWrite(PWM3, speed); //ENA pin
}

void setup() {
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,  OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(motor_took, OUTPUT);

  pinMode(PWM1, OUTPUT); 
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
}

void loop() {
  // motor_move(1, 1, 1, 1, 225, 225);
  // Serial.println("1");
  // motor_move(1, 1, 1, 0, 225, 225);
  // Serial.println("2");
  // motor_move(1, 1, 0, 0, 225, 225);
  // Serial.println("3");
  // motor_move(1, 0, 0, 0, 225, 225);
  // Serial.println("4");

  // motor_move(0, 0, 0, 0, 225, 225);
  // Serial.println("5");
  // motor_move(0, 0, 0, 1, 225, 225);
  // Serial.println("6");
  // motor_move(0, 0, 1, 1, 225, 225);
  // Serial.println("7");
  // motor_move(0, 1, 1, 1, 225, 225);
  // Serial.println("8");
  // motor_move(0, 1, 0, 1, 225, 225);
  
  Serial.println("9");
  motor_move(1, 0, 1, 0, 225, 225);
  Serial.println("10");
  motor_move(0, 1, 1, 0, 225, 225);
  Serial.println("11");
  motor_move(1, 0, 0, 1, 225, 225);
  Serial.println("12");

  motor_took(0, 1, 225);
  motor_took(1, 0, 225);
}
