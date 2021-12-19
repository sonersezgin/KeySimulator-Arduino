#define PIN1  12
#define PIN2  14
#define ACTIVEPINS  2

#define DEBOUNCE_DELAY  10

#define ST_BT_IDLE      0
#define ST_BT_1STPRESS  1
#define ST_BT_DEBOUNCE  2
#define ST_BT_PRESSED   3

uint8_t BtPins[8];
uint8_t BtStat[8];
uint8_t BtChecked[8];
uint32_t BtlastTick[8];

void setup() {
  // put your setup code here, to run once:
  BtPins[0] = PIN1;
  BtPins[1] = PIN2;
  
  pinMode(BtPins[0], INPUT_PULLUP);
  pinMode(BtPins[0], INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(checkButton()){
    if(BtStat[0] == ST_BT_PRESSED){
      if(BtChecked[0]!=1){
        Serial.write(0x01);
        BtChecked[0] = 1;
      }
    }
    if(BtStat[1] == ST_BT_PRESSED){
      if(BtChecked[1]!=1){
        Serial.write(0x02);
        BtChecked[1] = 1;
      }
    }
  }
}


uint8_t checkButton(void){
  uint8_t stChanged = 0;
  
  for(int i=0; i<ACTIVEPINS; i++){
    if(digitalRead(BtPins[i]) == LOW){
      if(BtStat[i] == ST_BT_IDLE){
        BtlastTick[i] = millis();
        BtStat[i] = ST_BT_1STPRESS;
      }
      else if(BtStat[i] == ST_BT_1STPRESS){
        BtStat[i] = ST_BT_DEBOUNCE;
      }
      else if(BtStat[i] == ST_BT_DEBOUNCE){
        if((millis()- BtlastTick[i]) > DEBOUNCE_DELAY ){
          BtStat[i] = ST_BT_PRESSED;
          stChanged |= (1<<i);
        }
      }
    }
    else{
        BtStat[i] = ST_BT_IDLE;
        BtChecked[i] = 0;
    }
  }
}
