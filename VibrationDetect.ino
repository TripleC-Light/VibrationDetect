#include "ExponentialFilter.h"
#include "MoveAverageFilter.h"
#include "KalmanFilter.h"

/*
* BlinkWithInterrupt.pde: 讓一顆燈號閃爍，每隔一秒切換一次燈號，使用 Timer 算時間
*/
   
const int switchPin =  8;         // 微動開關接腳
const int micInPin =  A0;         // 麥克風輸入腳(類比)
const int led_1_Pin =  10;        // LED1 接腳
const int led_2_Pin =  11;        // LED2 接腳
const int led_3_Pin =  12;        // LED3 接腳
const int led_4_Pin =  13;        // LED4 接腳

int valueThreshold = 2200;         // 音量觸發閥值
int valueMic = 0;                 // ADC 讀取的值
int micCounterThreshold = 30;    // 音量持續觸發閥值，超過此時間就做相應動作(單位：ms)
int noMicCounterThreshold = 50;  // 無聲時間閥值，超過此時間就做相應動作(單位：ms)
int micCounter = 0;               // 計算音量觸發時間
int noMicCounter = 0;             // 計算無聲時間
bool ledBlink = false;            // 用以判斷 LED是否要閃爍
int i=0;
int INTGvalueMic, INTGvalueMicOLD = 0;

void setup() {
  pinMode(switchPin, INPUT);      // 把 switchPin 設置成數位輸入
  pinMode(led_1_Pin, OUTPUT);     // 把 led_1_Pin 設置成數位輸出
  pinMode(led_2_Pin, OUTPUT);     // 把 led_2_Pin 設置成數位輸出
  pinMode(led_3_Pin, OUTPUT);     // 把 led_3_Pin 設置成數位輸出
  pinMode(led_4_Pin, OUTPUT);     // 把 led_4_Pin 設置成數位輸出
  pinMode(micInPin, INPUT);       // 把 micInPin 設置成類比輸入

  ADCSRA |=  (1 << ADPS2);   // 1
  ADCSRA &=  ~(1 << ADPS1);  // 0
  ADCSRA &=  ~(1 << ADPS0);  // 0


  /* 設定 LED初始狀態 */
  digitalWrite(led_1_Pin, HIGH);  // 關閉 LED1
  digitalWrite(led_2_Pin, HIGH);  // 關閉 LED2
  digitalWrite(led_3_Pin, HIGH);  // 關閉 LED3
  digitalWrite(led_4_Pin, HIGH);  // 關閉 LED4

  Serial.begin(57600);
  Serial.println(" START ");
  
  /* Timer1 設定，設為 1ms中斷一次 */
  TCCR1A = 0x00;                  // 設定為 Normal mode, 一般的Timer
  TCCR1B |= _BV(CS12);            // 設定中斷頻率(prescaler)= CPU clock/1024
  TCCR1B &= ~_BV(CS11);      
  TCCR1B |= _BV(CS10);   
  TIMSK1 |= _BV(TOIE1);           // 致能 Timer1，溢位時產生中斷(timer overflow interrupt)
  TCNT1 = -1;                  // 設定 Timer1起始值 = (CPU clock/1024)-(中斷時間/(CPU clock/1024))
}

void loop() {
  if( ledBlink==true ){           // 如果 ledBlink 等於 true，則啟動 LED閃爍
    digitalWrite(led_1_Pin, LOW);
    digitalWrite(led_2_Pin, LOW);
    digitalWrite(led_3_Pin, LOW);
    digitalWrite(led_4_Pin, LOW);
    delay(350);
    digitalWrite(led_1_Pin, HIGH);
    digitalWrite(led_2_Pin, HIGH);
    digitalWrite(led_3_Pin, HIGH);
    digitalWrite(led_4_Pin, HIGH);
    delay(350);
  }
}

/* Timer1 中斷副程式 */
ISR (TIMER1_OVF_vect)
{   
  TCNT1 = -1;                        // 重新設定 Timer1起始值
  valueMic = analogRead(micInPin);    // 讀取麥克風音量值
  if( digitalRead(switchPin)==LOW ){    // 判斷微動開關是否按下
    if( i>50 ){
      i = 0;
      Serial.print("$");
//      Serial.print(valueMic);
//      Serial.print(" ");
//      Serial.print(valueMic);
      INTGvalueMic = ExpFilter.start(INTGvalueMic);
//      INTGvalueMic = maFilter.start(INTGvalueMic, INTGvalueMicOLD);
//      INTGvalueMic = maFilter.start(INTGvalueMic, INTGvalueMicOLD);
//      INTGvalueMic = KlmFilter.start(INTGvalueMic, INTGvalueMicOLD);
//      Serial.print(" ");
      Serial.print(INTGvalueMic);
      Serial.println(";");
      if( INTGvalueMic > valueThreshold ){
        micCounter++;                               // 則將觸發時間紀錄在micCounter
        if( micCounter > micCounterThreshold ){    // 如果聲音觸發時間大於 micCounterThreshold 且 無聲時間大於 noMicCounterThreshold
          ledBlink = true;                                                                    // 則啟動 LED閃爍
        }
      }else{
        micCounter = 0;
      }
      INTGvalueMicOLD = INTGvalueMic;
      INTGvalueMic = 0;
    }else{
      i++;
      INTGvalueMic = INTGvalueMic + abs(valueMic-512);
    }
//    valueMic = analogRead(micInPin);    // 讀取麥克風音量值
//    Serial.print(" ");
//    Serial.print(valueMic);
//    Serial.println(";");
//    if( valueMic > valueThreshold ){    // 如果有大於閥值的音量
//      micCounter++;                     // 則將觸發時間紀錄在micCounter
//      noMicCounter = 0;                 // 因為有聲音，所以 noMicCounter 歸零
//    }else{
//      noMicCounter++;                   // 如果沒有聲音，則將無聲時間紀錄在 noMicCounter
//    }
//    if( (micCounter > micCounterThreshold) && (noMicCounter > noMicCounterThreshold) ){   // 如果聲音觸發時間大於 micCounterThreshold 且 無聲時間大於 noMicCounterThreshold
//      ledBlink = true;                                                                    // 則啟動 LED閃爍
//    }
  }else{                                // 微動開關沒被按下，所有變數回到初始值
    micCounter = 0;
    noMicCounter = 0;
    ledBlink = false;
    digitalWrite(led_1_Pin, HIGH);
    digitalWrite(led_2_Pin, HIGH);
    digitalWrite(led_3_Pin, HIGH);
    digitalWrite(led_4_Pin, HIGH);
  }
}

