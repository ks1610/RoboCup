// ==== Buttons ====
const int button_Pin_1 = 2;  // Lấy bóng
const int button_Pin_2 = 3;  // Bắn bóng
const int button_Pin_3 = 4;  // Servo 1
const int button_Pin_4 = 5;  // Servo 2
const int button_Pin_5 = 6;  // Dự phòng Đi thẳng
const int button_Pin_6 = 7;  // Dự phòng Đi phải
const int button_Pin_7 = 8;  // Dự phòng Đi trái
const int button_Pin_8 = 9;  // Dự phòng Đi lùi
const int button_Pin_9 = 10; // Quay phải
const int button_Pin_10 = 11;// Quay trái

// Joystick
#define ANALOG_X_PIN A2
#define ANALOG_Y_PIN A3
#define ANALOG_BUTTON_PIN A4

#define ANALOG_X_CORRECTION 128
#define ANALOG_Y_CORRECTION 128

// Mapping characters for each button
char buttonChars[] = {
  'A', // button 1
  'B', // button 2
  'C', // button 3
  'D', // button 4
  'E', // button 5
  'F', // button 6
  'G', // button 7
  'H', // button 8
  'I', // button 9
  'J'  // button 10
};

const int buttonPins[] = {
  button_Pin_1, button_Pin_2, button_Pin_3, button_Pin_4, button_Pin_5,
  button_Pin_6, button_Pin_7, button_Pin_8, button_Pin_9, button_Pin_10
};

int lastButtonState[10];

void setup() {
  Serial.begin(9600);

  // Setup buttons
  for (int i = 0; i < 10; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Using internal pull-up
    lastButtonState[i] = HIGH; // Not pressed
  }

  pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // === Check buttons ===
  for (int i = 0; i < 10; i++) {
    int state = digitalRead(buttonPins[i]);
    if (state == LOW && lastButtonState[i] == HIGH) {
      // Button just pressed
      Serial.write(buttonChars[i]);
    }
    lastButtonState[i] = state;
  }

  // === Joystick ===
  int xVal = analogRead(ANALOG_X_PIN) - ANALOG_X_CORRECTION;
  int yVal = analogRead(ANALOG_Y_PIN) - ANALOG_Y_CORRECTION;
  int buttonJoy = digitalRead(ANALOG_BUTTON_PIN);

  // Send joystick data
  Serial.print("X:");
  Serial.print(xVal);
  Serial.print(",Y:");
  Serial.print(yVal);
  Serial.print(",B:");
  Serial.println(buttonJoy == LOW ? "P" : "R"); // P = pressed, R = released

  delay(100); // adjust refresh rate
}
