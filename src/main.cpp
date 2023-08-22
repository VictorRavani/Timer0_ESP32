#include <Arduino.h>

#define PIN_LED 2

hw_timer_t * timer = NULL;
volatile uint8_t led_state = 0;

int i = 0;

void IRAM_ATTR timer_isr(){
  led_state = ! led_state;

  i++;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);

  uint8_t timer_id = 0;
  uint16_t prescaler = 80;
  int threashold = 10000;          // 1000000 = 1s    10000 = 1ms

  timer = timerBegin(timer_id, prescaler, true);
  timerAttachInterrupt(timer, &timer_isr, true);
  timerAlarmWrite(timer, threashold, true);
  timerAlarmEnable(timer);
}



void loop() {


  if(led_state){
    Serial.print(i);
  }

          Serial.println("Reload Timer");
        timerAlarmDisable(timer);		// stop alarm
        timerDetachInterrupt(timer);	// detach interrupt
        timerEnd(timer);			// end timer

timerAlarmDisable(timer);
timerDetachInterrupt(timer);

  
}