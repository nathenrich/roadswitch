#include <Adafruit_NeoPixel.h>
#include <SwitchPack.cpp>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SWITCH_PACK_COUNT 4

#define LED_PIN 4

#define BUTTON_PIN_1 14
#define BUTTON_PIN_2 15
#define BUTTON_PIN_3 16
#define BUTTON_PIN_4 17

#define RELAY_PIN_1 5
#define RELAY_PIN_2 6
#define RELAY_PIN_3 7
#define RELAY_PIN_4 8

#define BUTTON_ON_STATE LOW //LOW for nomral off switch

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(SWITCH_PACK_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

SwitchPack switchList [SWITCH_PACK_COUNT];

void setup() {

  int button_pins [SWITCH_PACK_COUNT];
  button_pins[0] = BUTTON_PIN_1;
  button_pins[1] = BUTTON_PIN_2;
  button_pins[2] = BUTTON_PIN_3;
  button_pins[3] = BUTTON_PIN_4;

  int relay_pins [SWITCH_PACK_COUNT];
  relay_pins[0] = RELAY_PIN_1;
  relay_pins[1] = RELAY_PIN_2;
  relay_pins[2] = RELAY_PIN_3;
  relay_pins[3] = RELAY_PIN_4;

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);

  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);

  pixels.begin();
  pixels.clear();
  pixels.show();

  for (int i = 0; i < SWITCH_PACK_COUNT; i++) {
    switchList[i] = SwitchPack(i, relay_pins[i], button_pins[i], BUTTON_ON_STATE);
    switchList[i].pixels = pixels;
  }
}

void loop() {
  for (int i = 0; i < SWITCH_PACK_COUNT; i++) {
    if(switchList[i].update()){
      for(int j = 0; j < SWITCH_PACK_COUNT; j++){
        switchList[j].switchDown(i);
      }
    }
  }
}
