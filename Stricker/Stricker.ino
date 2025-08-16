#include <Servo.h>

//Khai báo chân điều khiển động cơ bánh xe
// Motor 1
#define in1_L298N_no1 4
#define in2_L298N_no1 5
// Motor 2
#define in3_L298N_no1 6
#define in4_L298N_no1 7
// Motor 3
#define in1_L298N_no2 8
#define in2_L298N_no2 9
// Motor 4
#define in3_L298N_no2 10
#define in4_L298N_no2 11
// PWM
#define ENA 3
#define ENB 2

//Khai báo chân điều khiển động cơ lấy bóng
#define ball_in1 30
#define ball_in2 32
#define ENC 45

//Khai báo chân điều khiển động cơ bắn bóng
#define shoot_in1 22
#define shoot_in2 24
#define shoot_in3 26
#define shoot_in4 28

//Joystick
#define ANALOG_X_PIN A2
#define ANALOG_Y_PIN A3
#define ANALOG_BUTTON_PIN A4

#define ANALOG_X_CORRECTION 128
#define ANALOG_Y_CORRECTION 128

//Servo
#define Servo_Pin_1 44
#define Servo_Pin_2 46

// ==== Nút bấm ====
const int button_Pin_1 = 23; // Lấy bóng
const int button_Pin_2 = 25; // Bắn bóng
const int button_Pin_3 = 27; // Servo 1
const int button_Pin_4 = 29; // Servo 2
const int button_Pin_5 = 31; // Dự phòng Đi thẳng
const int button_Pin_6 = 33; // Dự phòng Đi phải
const int button_Pin_7 = 35; // Dự phòng Đi trái
const int button_Pin_8 = 37; // Dự phòng Đi lùi
const int button_Pin_9 = 39; // Quay phải
const int button_Pin_10 = 41; // Quay trái

Servo servo1, servo2;

//Hàm tiện ích Joystick
byte readAnalogAxisLevel(int pin) {
  return map(analogRead(pin), 0, 1023, 0, 255);
}

bool isAnalogButtonPressed(int pin) {
  return digitalRead(pin) == 0;
}

//Hàm setup Joystick
void Joystick_Setup() {
  pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP);
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

  digitalWrite(in1_L298N_no2, m2_in1);
  digitalWrite(in2_L298N_no2, m2_in2);
  digitalWrite(in3_L298N_no2, m2_in3);
  digitalWrite(in4_L298N_no2, m2_in4);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

//Chuyển động bánh xe đa hướng
#if 0 
// Serial.println(" -> Dừng");
moveMotors(
  0, 0, 0, 0,  // L298N_no1
  0, 0, 0, 0,  // L298N_no2
  0, 0       // Speeds
);
// Serial.println(" -> Đi Thẳng");
moveMotors(
  1, 0, 1, 0,  // L298N_no1
  1, 0, 1, 0,  // L298N_no2
  80, 80       // Speeds
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
// Serial.println(" -> Đi Lùi");
moveMotors(
  0, 1, 0, 1,  // L298N_no1
  0, 1, 0, 1,  // L298N_no2
  80, 80       // Speeds
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
#endif

//Lấy bóng
void Ball_Took(bool m1_in1, bool m1_in2, int speed) {
  digitalWrite(ball_in1, m1_in1);
  digitalWrite(ball_in2, m1_in2);
  analogWrite(ENC, speed);
}

//Bắn bóng
void Ball_Shoot(bool m1_in1, bool m1_in2, bool m1_in3, bool m1_in4) {
  digitalWrite(shoot_in1, m1_in1);
  digitalWrite(shoot_in2, m1_in2);
  digitalWrite(shoot_in3, m1_in3);
  digitalWrite(shoot_in4, m1_in4);
}

//Setup
void setup() {
  Serial.begin(115200);

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

  // Ball
  pinMode(ball_in1, OUTPUT);
  pinMode(ball_in2, OUTPUT);
  pinMode(ENC, OUTPUT);

  // Shoot
  pinMode(shoot_in1, OUTPUT);
  pinMode(shoot_in2, OUTPUT);
  pinMode(shoot_in3, OUTPUT);
  pinMode(shoot_in4, OUTPUT);

  // Buttons
  pinMode(button_Pin_1, INPUT_PULLUP);
  pinMode(button_Pin_2, INPUT_PULLUP);
  pinMode(button_Pin_3, INPUT_PULLUP);
  pinMode(button_Pin_4, INPUT_PULLUP);
  pinMode(button_Pin_5, INPUT_PULLUP);
  pinMode(button_Pin_6, INPUT_PULLUP);
  pinMode(button_Pin_7, INPUT_PULLUP);
  pinMode(button_Pin_8, INPUT_PULLUP);
  pinMode(button_Pin_9, INPUT_PULLUP);
  pinMode(button_Pin_10, INPUT_PULLUP);

  // Servo
  servo1.attach(Servo_Pin_1);
  servo2.attach(Servo_Pin_2);

  Joystick_Setup();
}

//Loop chính
void loop() {
  int x = readAnalogAxisLevel(ANALOG_X_PIN) - ANALOG_X_CORRECTION;
  int y = readAnalogAxisLevel(ANALOG_Y_PIN) - ANALOG_Y_CORRECTION;

  Serial.println("Joystick Value: ");
  Serial.println("X = ");
  Serial.println(x);
  Serial.println("Y = ");
  Serial.println(y);

  //Joystick điều khiển robot
  if (abs(x) < 30 && abs(y) < 30) {
    // Dừng
    Serial.println(" -> Dừng");
    moveMotors(
      0, 0, 0, 0,  // L298N_no1
      0, 0, 0, 0,  // L298N_no2
      0, 0       // Speeds
    );
  }
  else if (y > 50) {
    // Đi thẳng
    Serial.println(" -> Đi Thẳng");
    moveMotors(
      1, 0, 1, 0,  // L298N_no1
      1, 0, 1, 0,  // L298N_no2
      80, 80       // Speeds
    );
  }
  else if (y < -50) {
    // Đi lùi
    moveMotors(
      0, 1, 0, 1,  // L298N_no1
      0, 1, 0, 1,  // L298N_no2
      80, 80       // Speeds
    );
  }
  else if (x > 50) {
    // Đi phải
    Serial.println(" -> Đi Sang Phải");
    moveMotors(
      1, 0, 0, 1,  // L298N_no1
      0, 1, 1, 0,  // L298N_no2
      100, 100       // Speeds
    );
  }
  else if (x < -50) {
    // Đi trái
    Serial.println(" -> Đi Sang Trái");
    moveMotors(
      0, 1, 1, 0,  // L298N_no1
      1, 0, 0, 1,  // L298N_no2
      100, 100       // Speeds
    );
  }
  else if (x > 50 && y > 50) {
    // Đi thẳng chéo phải    
    Serial.println(" -> Đi Thẳng Chéo Phải");    
    moveMotors(
      1, 0, 0, 0,  // L298N_no1
      0, 0, 1, 0,  // L298N_no2
      180, 180       // Speeds
    );
  }
  else if (x < -50 && y > 50) {
    // Đi thẳng chéo trái
    Serial.println(" -> Đi Thẳng Chéo Trái");
    moveMotors(
      0, 0, 1, 0,  // L298N_no1
      1, 0, 0, 0,  // L298N_no2
      180, 180       // Speeds
    );
  }
  else if (x > 50 && y < -50) {
    // Đi lùi chéo phải
    Serial.println(" -> Đi Lùi Chéo Phải");  
    moveMotors(
      0, 0, 0, 1,  // L298N_no1
      0, 1, 0, 0,  // L298N_no2
      180, 180       // Speeds
    );
  }
  else if (x < -50 && y < -50) {
    // Đi lùi chéo trái
    Serial.println(" -> Đi Lùi Chéo Trái");
    moveMotors(
      0, 1, 0, 0,  // L298N_no1
      0, 0, 0, 1,  // L298N_no2
      180, 180       // Speeds
    );
  }
  
  //Nút nhấn
  if (!digitalRead(button_Pin_1)) {
    Ball_Took(1, 0, 150); // Lấy bóng
  }
  if (!digitalRead(button_Pin_2)) {
    Ball_Shoot(1, 0, 1, 0); // Bắn bóng
  }
  if (!digitalRead(button_Pin_3)) {
    servo1.write(90);
  }
  if (!digitalRead(button_Pin_4)) {
    servo2.write(90);
  }
  if (!digitalRead(button_Pin_5)) {
    Serial.println(" -> Đi Thẳng");
    moveMotors(1, 0, 1, 0, 1, 0, 1, 0, 80, 80); // Đi thẳng
  }
  if (!digitalRead(button_Pin_6)) {
    Serial.println(" -> Đi Sang Phải");
    moveMotors(1, 0, 0, 1, 0, 1, 1, 0, 100, 100); // Đi phải
  }
  if (!digitalRead(button_Pin_7)) {
    Serial.println(" -> Đi Sang trái");
    moveMotors(0, 1, 1, 0, 1, 0, 0, 1, 100, 100); // Đi trái
  }
  if (!digitalRead(button_Pin_8)) {
    Serial.println(" -> Đi Lùi");
    moveMotors(0, 1, 0, 1, 0, 1, 0, 1, 80, 80); // Đi lùi
  }
  if (!digitalRead(button_Pin_9)) {
    Serial.println(" -> Quay Phải");
    moveMotors(1, 0, 0, 1, 1, 0, 0, 1, 80, 80); // Quay phải
  }
  if (!digitalRead(button_Pin_10)) {
    Serial.println(" -> Quay Trái");
    moveMotors(0, 1, 1, 0, 0, 1, 1, 0, 80, 80); // Quay trái
  }
}