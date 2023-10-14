#include <Keyboard.h>

#define PIN_BUTTON_WHITE  7
#define PIN_BUTTON_BLUE   6
#define PIN_BUTTON_RED    5
#define PIN_BUTTON_GREEN  4

#define BUTTON_PRESSED    LOW
#define BUTTON_UNPRESSED  HIGH

#define BUTTON_LONG_PRESS_TIME_MS 2000
#define BUTTON_BOUNCING_TIME_MS   100 

#define KEEPASSXC_APP "C:\\Program Files\\KeePassXC\\KeePassXC.exe"
#define KEEPASSXC_PWD "TODO_SET_PASSWORD"

bool prevStateButtonWhite = BUTTON_UNPRESSED;
bool prevStateButtonBlue  = BUTTON_UNPRESSED;
bool prevStateButtonRed   = BUTTON_UNPRESSED;
bool prevStateButtonGreen = BUTTON_UNPRESSED;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUTTON_WHITE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_BLUE,  INPUT_PULLUP);
  pinMode(PIN_BUTTON_RED,   INPUT_PULLUP);
  pinMode(PIN_BUTTON_GREEN, INPUT_PULLUP);

  Keyboard.begin(KeyboardLayout_fr_FR);
}

void runApp(const char *app) {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(app);
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
}

void enterPassword(const char *pwd) {
  Keyboard.print(pwd);
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
}

void minimizeWindow() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(' ');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press('u');
  delay(100);
  Keyboard.releaseAll();
}

bool isButtonPressed(bool *prevState, bool currentState) {
  if (*prevState != currentState) {
    delay(BUTTON_BOUNCING_TIME_MS);
    if (currentState == BUTTON_PRESSED) {
      return true;
    }
    *prevState = currentState;
  }
  return false;
}

void loop() {

  if (isButtonPressed(&prevStateButtonWhite, digitalRead(PIN_BUTTON_WHITE))) {
      Serial.println("Button White pressed");
      runApp(KEEPASSXC_APP);
  }

  if (isButtonPressed(&prevStateButtonBlue, digitalRead(PIN_BUTTON_BLUE))) {
      Serial.println("Button Blue pressed");
      enterPassword(KEEPASSXC_PWD);
  }

  if (isButtonPressed(&prevStateButtonRed, digitalRead(PIN_BUTTON_RED))) {
    Serial.println("Button Red");
    minimizeWindow();
  }

  if (isButtonPressed(&prevStateButtonGreen, digitalRead(PIN_BUTTON_GREEN))) {
    Serial.println("Button Green");
  }
}
