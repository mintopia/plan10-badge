#include <tinyNeoPixel_Static.h>
#include <EEPROM.h>

// PA7 = HW Serial RX
// PA6 = HW Serial TX
#define LED_PIN PIN_PA1
#define NUM_PIXELS 5
#define BRIGHTNESS 128
#define LOCKED_RED 0
#define LOCKED_GREEN 170
#define LOCKED_BLUE 217
#define PASSWORD "aquamarine"
#define EEPROM_ADDR 42

byte pixels[NUM_PIXELS * 3];
tinyNeoPixel leds = tinyNeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB, pixels);

bool unlocked = true;
bool nedry = false;
char buffer [80];
int count = 0;
int wrongCount = 0;
uint16_t hue = 0;

void setup() {
  pinModeFast(LED_PIN, OUTPUT);
  leds.begin();
  leds.clear();
  leds.setBrightness(BRIGHTNESS);
  for (int i = 0; i < 5; i++) {
    leds.setPixelColor(i, LOCKED_RED, LOCKED_GREEN, LOCKED_BLUE);
    leds.show();
    delay(200);
  }

  Serial.begin(9600);
  printWelcome();
  if (EEPROM.read(EEPROM_ADDR) == 42) {
    unlocked = true;
    cmdPrompt();
  } else {
    passwordPrompt();
  }
}

void passwordPrompt()
{
  Serial.print("Please enter the vault password:\n> ");
}

void cmdPrompt()
{
  Serial.println("Enter Command:\n> ");
}

void loop() {
  updateLED();
  readFromSerial();
  delay(10);
}

void updateLED() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    if (unlocked) {
      leds.setPixelColor(i, leds.ColorHSV(hue + (i * 16384), 255, 255));
      leds.setBrightness(BRIGHTNESS);
    } else {
      leds.setPixelColor(i, LOCKED_RED, LOCKED_GREEN, LOCKED_BLUE);
    }
  }
  leds.show();
  hue += 128;
}

void readFromSerial() {
  bool ready = false;
  while (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);
    if (c == '\n' || count == sizeof(buffer)-1) {
      buffer[count] = '\0';
      count = 0;
      ready = true;
      break;
    }
    buffer[count++] = c;
  }
  if (!ready) {
    return;
  }
  if (unlocked) {
    if (strcmp(buffer, "logout") == 0) {
      unlocked = false;
      EEPROM.write(EEPROM_ADDR, 0);
      printWelcome();
      passwordPrompt();
    } else if (strcmp(buffer, "north") == 0) {
      Serial.println("You proceed in a direction you believe to be North. How can you be sure? You're in a dark room!\n");
      cmdPrompt();
    } else if (strcmp(buffer, "about") == 0) {
      Serial.println("\nP-LAN #10 Badge\nMade with <3 by Mintopia\ngithub.com/mintopia\n");
      cmdPrompt();
    } else if (strcmp(buffer, "") == 0) {
      printWelcome();
      cmdPrompt();
    } else {
      Serial.println("Unknown command\n");
    }
  } else {
    if (strcmp(buffer, PASSWORD) == 0 || nedry && strcmp(buffer, "please") == 0) {
      Serial.println("Password correct.\n\nYou found the secret! The first person to email jess@mintopia.net with the subject 'Badge' and the codeword 'aquamarine' will get a prize!\n");
      unlocked = true;
      EEPROM.write(EEPROM_ADDR, 42);
      cmdPrompt();
      return;
    } else if (strcmp(buffer, "") == 0) {
        printWelcome();
    } else {
        Serial.println("Incorrect Password\n");
        wrongCount++;
        if (wrongCount >= 10) {
          nedry = true;
          wrongCount = 0;
          Serial.println("               __\n              / _)\n     _.----._/ /\n    /         /\n __/ (  | (  |\n/__.-'|_|--|_|\nAh ah ah, you didn't say the magic word!\n");
        }
    }
    passwordPrompt();
  }
}

void printWelcome() {
  Serial.println("\n     _.-^^---....,,--\n _--                  --_\n<        Vault 99        >)\n|                         |\n \._                   _./\n    ```--. . , ; .--'''\n          | |   |\n       .-=||  | |=-.\n       `-=#$%&%$#=-'\n          | ;  :|\n _____.,-#%&$@%#&#~,._____\n");
}