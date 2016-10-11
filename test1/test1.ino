#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출

int Red_LED=3;
int Green_LED=5;
int Blue_LED=6;
int blueTx=10;   //Tx (보내는핀 설정)
int blueRx=9;   //Rx (받는핀 설정)

SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열

void LED_Setup(){
  pinMode(Red_LED, LOW);
  pinMode(Green_LED, LOW);
  pinMode(Blue_LED, LOW);}
  
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  LED_Setup();
}


void RainBow_Color()
{
  while(1){
  for( int i = 0 ; i < 255 ; i ++ ) 
  {
    analogWrite( Red_LED, i );
    analogWrite( Blue_LED, 255 - i );
    delay(10);
  }
   for( int i = 0 ; i < 255 ; i ++ ) 
  {
    analogWrite( Green_LED, i );
    analogWrite( Red_LED, 255 - i );
    delay(10);
  }
   for( int i = 0 ; i < 255 ; i ++ ) 
  {
    analogWrite( Blue_LED, i );
    analogWrite( Green_LED, 255 - i );
    delay(10);
  }}
}

void loop() {
  while(mySerial.available())  //mySerial에 전송된 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);           //수신 문자열 끊김 방지
  }
 
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
    
    if(myString == "on" ){//입력받은 값이 on이면
    analogWrite(Red_LED, HIGH);
    analogWrite(Green_LED, HIGH);
    analogWrite(Blue_LED, HIGH);}

    if(myString == "next" ){
      for( int i = 0 ; i < random(0,255) ; i ++ ) 
      {
      analogWrite( Red_LED, i );
      analogWrite( Blue_LED, 255 - i );
      delay(10);
      }
    }
    
    if(myString == "off" ){
    pinMode(Red_LED, LOW);
    pinMode(Green_LED, LOW);
    pinMode(Blue_LED, LOW);}
    myString="";  //myString 변수값 초기화
  }
  }


//http://deneb21.tistory.com/267

