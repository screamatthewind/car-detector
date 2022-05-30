
#include <Arduino.h>
#include "FreqCountESP.h"

int buzzerOutputPin = 12;
int motionDetectorInputPin = 14;
int timerMs = 1000;
int timerRunning = false;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(buzzerOutputPin, OUTPUT);

  Serial.begin(115200);
  FreqCountESP.begin(motionDetectorInputPin, timerMs);
  timerRunning = true;
}

unsigned char i;

void loop()
{
  if (FreqCountESP.available())
  {
    uint32_t frequency = FreqCountESP.read();

    if (frequency > 10)
    {
      Serial.println("Stop");
      FreqCountESP.end();
      timerRunning = false;

      digitalWrite(LED_BUILTIN, LOW);

      /* output an frequency */
      for (i = 0; i < 80; i++)
      {
        /*When the buzzer is high, it sounds*/
        digitalWrite(buzzerOutputPin, HIGH);
        delay(1); // wait for 1ms
        digitalWrite(buzzerOutputPin, LOW);
        delay(1); // wait for 1ms
      }
      /* output another frequency */
      for (i = 0; i < 100; i++)
      {
        digitalWrite(buzzerOutputPin, HIGH);
        delay(2); // wait for 2ms
        digitalWrite(buzzerOutputPin, LOW);
        delay(2); // wait for 2ms
      }
    }
    else
      digitalWrite(LED_BUILTIN, HIGH);

    Serial.print("Raw ");
    Serial.println(frequency);
  }

  if (!timerRunning)
  {
    Serial.println("Start");
    FreqCountESP.begin(motionDetectorInputPin, timerMs);
    timerRunning = true;
  }
}