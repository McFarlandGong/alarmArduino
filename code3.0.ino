/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);
int alarm = 8;    //alarmPin
//int serNum[5];
int alarmtimes=2;

int cards[5]={99,89,162,133,28};
bool access = false;
bool flag=true;
void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();
    pinMode(alarm, OUTPUT);
    digitalWrite(alarm, HIGH);
}

void loop(){
    
    if(rfid.isCard()){
         Serial.print("YES\n");
          readRFID();

         if(!flag){
            alarmnow();
            flag=true;
         }
    }else{
      if(flag){
      alarmnow();
      flag=false;
      }
    }
    rfid.halt();
}//loop
void alarmnow(){
  for(int j=0;j<2;j++){
    digitalWrite(alarm,LOW);
    delay(100);
    digitalWrite(alarm,HIGH);
    delay(100);
  }
}

void readRFID(){
          if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
        }//if
}

