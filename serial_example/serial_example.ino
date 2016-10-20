#include <SoftwareSerial.h>
String myString=""; //받는 문자열
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  Serial.println("input, resalt ");
}

void loop() {
  while(Serial.available())              //mySerial에 전송된 값이 있으면
  {
    char myChar = (char)Serial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;                     //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);                             //수신 문자열 끊김 방지
  }
  if(!myString.equals(""))
    Serial.print("on.");
    myString="";
}
