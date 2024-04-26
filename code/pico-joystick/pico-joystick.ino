#include <Joystick.h>

long lastUpdateTime;

int panelPins[5][4] =
  {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15},
    {16, 17, 18, 19}
  };

void setup() {
  Serial.begin(115200);
  Joystick.begin();
  Joystick.useManualSend(true);

  for (int i = 0; i < 20; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  
}

void loop() {

  // Only send an update every 1ms
  if((micros() - lastUpdateTime) >= 1000)
  {
    for (int i = 0; i < 5; i++)
    {
      bool panelHit = false;
      for (int j = 0; j < 4; j++)
      {
        panelHit |= digitalRead(panelPins[i][j]) == LOW;
      }
      Joystick.button(i + 1, panelHit);
    }

    // Send report
    Joystick.send_now();
    
    lastUpdateTime = micros();
  }

}
