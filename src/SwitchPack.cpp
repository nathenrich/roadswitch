#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

class SwitchPack {
  public:
    static int & getProgramingId ()
    {
       static int programingId = 0;
       return programingId;
    }

    Adafruit_NeoPixel pixels;

    SwitchPack() {};

    SwitchPack(int i, int rp, int bp, bool bos){
      index = i;
      relay_pin = rp;
      button_pin = bp;
      debouncer = Bounce();
      debouncer.attach(bp);
      debouncer.interval(10);
      button_on_state = bos;
      isOn = false;
      actionable = true;
      getProgramingId() = -1;
      isLinked = false;
      if(i == 1){
        linkedId = 0;
      }
    };

    bool update() {
      bool state = false;
      debouncer.update();
      if (debouncer.read() == button_on_state && actionable) {
        actionable = false;
        if(!isOn){
          turnOn(COLOR_1);
          state = true;
          timeSince = millis();
        }else{
          turnOff();
        }
      }else if(debouncer.read() == button_on_state && !actionable){
          if(millis() - timeSince > 2000 && isOn){
            pixels.setPixelColor(index, COLOR_3);
            pixels.show();
          }
      }else if (debouncer.read() != button_on_state && !actionable) {
        actionable = true;
        if(getProgramingId() == index){
          getProgramingId() = -1;
        }
      }
      return state;
    }

    void switchDown(int id) {
      if(id == linkedId){
        //turnOn(COLOR_2);
      }
    }

  private:
    Bounce debouncer;
    bool actionable;
    bool isOn;
    bool isLinked;
    int linkList[7];
    int excludeList[7];
    int index;
    int button_pin;
    int relay_pin;
    bool button_on_state;
    int linkedId;
    int timeSince;

    uint32_t COLOR_OFF = pixels.Color(0,0,0);
    uint32_t COLOR_1 = pixels.Color(0,80,80);
    uint32_t COLOR_2 = pixels.Color(70,90,0);
    uint32_t COLOR_3 = pixels.Color(80,0,0);

    void turnOn(){}

    void turnOn(uint32_t color){
      isOn = true;
      pixels.setPixelColor(index, color);
      pixels.show();
      digitalWrite(relay_pin, HIGH);
    }

    void turnOff(){
      isOn = false;
      pixels.setPixelColor(index, COLOR_OFF);
      pixels.show();
      digitalWrite(relay_pin, LOW);
    }

    // void addLink(int i){
    //   for(int i=0; i < sizeof(linkList)/sizeof(linkList[0]); i++){
    //     if(){
    //
    //     }
    //   }
    // }
};
