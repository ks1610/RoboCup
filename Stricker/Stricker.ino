#include <Servo.h>

//Khai báo chân điều khiển động cơ bánh xe
// Motor 1
#define in1_L298N_no1 22
#define in2_L298N_no1 24
// Motor 2
#define in3_L298N_no1 26
#define in4_L298N_no1 28
// Motor 3
#define in1_L298N_no2 30
#define in2_L298N_no2 32
// Motor 4
#define in3_L298N_no2 34
#define in4_L298N_no2 36
// PWM
#define ENA 2
#define ENB 3

//Khai báo chân điều khiển động cơ lấy bóng
#define ball_in1 38
#define ball_in2 40
#define END 4

//Khai báo chân Relay bật tắt động cơ bắn bóng 
const int Relay_Shoot = 42;
const int Relay_Laze = 46;


//Servo đóng mở 1
#define Servo_Pin_1 6

//Servo đóng mở 2
#define Servo_Pin_2 7

void Motor_Move_Setup(){
  // Setup chân motor
  pinMode(in1_L298N_no1, OUTPUT);
  pinMode(in2_L298N_no1, OUTPUT);
  pinMode(in3_L298N_no1, OUTPUT);
  pinMode(in4_L298N_no1, OUTPUT);
  pinMode(in1_L298N_no2, OUTPUT);
  pinMode(in2_L298N_no2, OUTPUT);
  pinMode(in3_L298N_no2, OUTPUT);
  pinMode(in4_L298N_no2, OUTPUT);

  // PWM
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// Setup động cơ bắn bóng 
void Motor_Ball_Shoot_Setup(){
  // Shoot
  pinMode(shoot_in1, OUTPUT);
  pinMode(shoot_in2, OUTPUT);
  pinMode(END, OUTPUT);
}

void Relay_Setup(){
  pinMode(Relay_Shoot, OUTPUT)
  pinMode(Relay_Laze, OUTPUT)
}

//Điều khiển động cơ bánh xe
void moveMotors(
  bool m1_in1, bool m1_in2, bool m1_in3, bool m1_in4,
  bool m2_in1, bool m2_in2, bool m2_in3, bool m2_in4,
  int speedA, int speedB
) {
  digitalWrite(in1_L298N_no1, m1_in1);
  digitalWrite(in2_L298N_no1, m1_in2);
  digitalWrite(in3_L298N_no1, m1_in3);
  digitalWrite(in4_L298N_no1, m1_in4);

  digitalWrite(in2_L298N_no2, m2_in2);
  digitalWrite(in1_L298N_no2, m2_in1);
  digitalWrite(in4_L298N_no2, m2_in4);
  digitalWrite(in3_L298N_no2, m2_in3);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

//Bắn bóng
void Ball_Shoot(bool m1_in1, bool m1_in2, int speed) {
  digitalWrite(shoot_in1, m1_in1);
  digitalWrite(shoot_in2, m1_in2);
  analogWrite(END, speed);
}

//Setup servo
void Servo_Setup(){
  // Servo
  servo1.attach(Servo_Pin_1);
  servo2.attach(Servo_Pin_2);
}

//Setup
void setup() {
  Serial.begin(115200);
  Motor_Move_Setup();
  Motor_Ball_Shoot_Setup();
  Relay_Setup();
}

void loop(){
  //LAY BONG
  Ball_Shoot(0,1,250);

  //Bắn bóng
  digitalWrite(Relay_Shoot, HIGH);

  //Laze 
  digitalWrite(Relay_Laze, HIGH);

  //Đóng mở servo 1
  servo1.write(90); //Servo 1 đóng
  servo1.write(0); //Servo 1 mở
  
  //Đóng mở servo 2
  servo2.write(90); //Servo 2 đóng
  servo2.write(0); //Servo 2 mở

  // Serial.println(" -> Đi thẳng");
  moveMotors(
    1, 0, 1, 0,  // L298N_no1
    1, 0, 1, 0,  // L298N_no2
    80, 80       // Speeds
  );
  // Serial.println(" -> Đi lùi");
  moveMotors(
    0, 1, 0, 1,  // L298N_no1
    0, 1, 0, 1,  // L298N_no2
    50, 50       // Speeds
  );
  // Serial.println(" -> Dừng");
  moveMotors(
    0, 0, 0, 0,  // L298N_no1
    0, 0, 0, 0,  // L298N_no2
    0, 0       // Speeds
  );
  // Serial.println(" -> Đi Sang Phải");
  moveMotors(
    1, 0, 0, 1,  // L298N_no1
    0, 1, 1, 0,  // L298N_no2
    100, 100       // Speeds
  );
  // Serial.println(" -> Đi Sang Trái");
  moveMotors(
    0, 1, 1, 0,  // L298N_no1
    1, 0, 0, 1,  // L298N_no2
    100, 100       // Speeds
  );
  // Serial.println(" -> Đi Thẳng Chéo Trái");
  moveMotors(
    0, 0, 1, 0,  // L298N_no1
    1, 0, 0, 0,  // L298N_no2
    180, 180       // Speeds
  );
  // Serial.println(" -> Đi Thẳng Chéo Phải");
  moveMotors(
    1, 0, 0, 0,  // L298N_no1
    0, 0, 1, 0,  // L298N_no2
    180, 180       // Speeds
  );
  // Serial.println(" -> Đi Lùi Chéo Trái");
  moveMotors(
    0, 1, 0, 0,  // L298N_no1
    0, 0, 0, 1,  // L298N_no2
    180, 180       // Speeds
  );
  // Serial.println(" -> Đi Lùi Chéo Phải");
  moveMotors(
    0, 0, 0, 1,  // L298N_no1
    0, 1, 0, 0,  // L298N_no2
    180, 180       // Speeds
  );
  // Serial.println(" -> Quay Vòng Trái");
  moveMotors(
    0, 1, 1, 0,  // L298N_no1
    0, 1, 1, 0,  // L298N_no2
    80, 80       // Speeds
  );
  // Serial.println(" -> Quay Vòng Phải");
  moveMotors(
    1, 0, 0, 1,  // L298N_no1
    1, 0, 0, 1,  // L298N_no2
    80, 80       // Speeds
  );
  // Serial.println(" -> Dừng Khẩn Cấp");
  moveMotors(
    0, 0, 0, 0,  // L298N_no1
    0, 0, 0, 0,  // L298N_no2
    0, 0       // Speeds
  );
}
