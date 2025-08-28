#if 0  
  //LAY BONG
  Ball_Shoot(0,1,250);

  //Bắn bóng
  digitalWrite(Relay_Shoot, HIGH);

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
#endif

#include <Servo.h>

// ===== Pin definitions =====
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

// Ball intake motor
#define ball_in1 38
#define ball_in2 40
#define END 4

// Shooting relay
const int Relay_Shoot = 42;

//Servo đóng mở 1
#define Servo_Pin_1 6
//Servo đóng mở 2
#define Servo_Pin_2 7

Servo servo1, servo2;

// ===== Serial buffer =====
String inputString = "";
bool stringComplete = false;


// ==== Setup functions ====
void Motor_Move_Setup() {
  pinMode(in1_L298N_no1, OUTPUT);
  pinMode(in2_L298N_no1, OUTPUT);
  pinMode(in3_L298N_no1, OUTPUT);
  pinMode(in4_L298N_no1, OUTPUT);
  pinMode(in1_L298N_no2, OUTPUT);
  pinMode(in2_L298N_no2, OUTPUT);
  pinMode(in3_L298N_no2, OUTPUT);
  pinMode(in4_L298N_no2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void Motor_Ball_Shoot_Setup() {
  pinMode(ball_in1, OUTPUT);
  pinMode(ball_in2, OUTPUT);
  pinMode(END, OUTPUT);
}

void Relay_Setup() {
  pinMode(Relay_Shoot, OUTPUT);
}


// ==== Control functions ====
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

void Ball_Shoot(bool in1, bool in2, int speed) {
  digitalWrite(ball_in1, in1);
  digitalWrite(ball_in2, in2);
  analogWrite(END, speed);
}

//Setup servo
void Servo_Setup(){
  // Servo
  servo1.attach(Servo_Pin_1);
  servo2.attach(Servo_Pin_2);
}

// ==== Setup ====
void setup() {
  Serial.begin(115200);
  Motor_Move_Setup();
  Motor_Ball_Shoot_Setup();
  Relay_Setup();
  Servo_Setup();
  Serial.println("Robot Ready with Joystick + Button control...");
}


// ==== Main Loop ====
void loop() {
  // === Handle incoming serial data ===
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
      stringComplete = true;
    } else {
      inputString += c;
    }
  }

  if (stringComplete) {
    if (inputString.startsWith("X:")) {
      // Joystick control
      parseJoystick(inputString);
    } else if (inputString.length() == 1) {
      // Button control
      handleButton(inputString[0]);
    }
    inputString = "";
    stringComplete = false;
  }
}


// ===== Handle Button Characters =====
void handleButton(char cmd) {
  switch (cmd) {
    case 'A':  // Lấy bóng
      Ball_Shoot(0, 1, 200);
      Serial.println("Ball intake");
      break;

    case 'B':  // Bắn bóng
      digitalWrite(Relay_Shoot, HIGH);
      Serial.println("Shoot ball");
      break;

    case 'C':  // Servo 1
      servo1.write(0); //Servo 1 mở
      servo2.write(90); //Servo 2 đóng
      Serial.println("Servo 1 triggered");
      break;

    case 'D':  // Servo 2
      servo1.write(90); //Servo 1 đóng
      servo2.write(0); //Servo 2 mở
      Serial.println("Servo 2 triggered");
      break;

    case 'E':  // Stop
      moveMotors(0,0,0,0, 0,0,0,0, 0,0);
      Serial.println("Stop");
      break;

    default:
      // ignore unknown
      break;
  }
}


// ===== Parse Joystick Input =====
void parseJoystick(String data) {
  // Example: "X:530,Y:480,B:R"
  int xIndex = data.indexOf("X:");
  int yIndex = data.indexOf("Y:");
  if (xIndex == -1 || yIndex == -1) return;

  int comma1 = data.indexOf(",", xIndex);
  int comma2 = data.indexOf(",", yIndex);

  int xVal = data.substring(xIndex + 2, comma1).toInt();
  int yVal = data.substring(yIndex + 2, comma2).toInt();

  controlFromJoystick(xVal, yVal);
}


// ===== Control Motors Based on Joystick =====
void controlFromJoystick(int x, int y) {
  // Center (joystick neutral ~512)
  int deadzone = 100;
  int center = 512;

  int dx = x - center;
  int dy = y - center;

  // Deadzone
  if (abs(dx) < deadzone) dx = 0;
  if (abs(dy) < deadzone) dy = 0;

  int speed = map(max(abs(dx), abs(dy)), 0, 512, 0, 200); // adjust max speed

  if (dx == 0 && dy == 0) {
    // Stop
    moveMotors(0,0,0,0, 0,0,0,0, 0,0);
    Serial.println("Stop");
  }
  else if (dy > 0 && abs(dy) >= abs(dx)) {
    // Forward
    moveMotors(1,0,1,0, 1,0,1,0, speed, speed);
    Serial.println("Forward");
  }
  else if (dy < 0 && abs(dy) >= abs(dx)) {
    // Backward
    moveMotors(0,1,0,1, 0,1,0,1, speed, speed);
    Serial.println("Backward");
  }
  else if (dx > 0 && abs(dx) > abs(dy)) {
    // Right
    moveMotors(1,0,0,1, 0,1,1,0, speed, speed);
    Serial.println("Right");
  }
  else if (dx < 0 && abs(dx) > abs(dy)) {
    // Left
    moveMotors(0,1,1,0, 1,0,0,1, speed, speed);
    Serial.println("Left");
  }
}
