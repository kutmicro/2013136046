#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출

/***************핀 설정*****************/
int Red_LED=3;
int Green_LED=5;
int Blue_LED=6;
int blueTx=10;   //Tx (보내는핀 설정)
int blueRx=9;   //Rx (받는핀 설정)
//int mp3tx = 12;
//int mp3rx = 13;
/**************led 설정 ****************/
int red=0;
int blue=0;
int green=0;

//일반 입출력 데이터 핀을 rx,tx로 동작 가능하도록 만들어주는 함수 softwareserial name(핀번호,핀번호)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
//입력받는 문자열을 저장하기위한 변수
String myString=""; //받는 문자열


void setup() {
  //시리얼 통신을 초기화하고 전송속도를 설정하는 함수 name.begin(전송속도)
  Serial.begin(9600);   //시리얼모니터 개방
  mySerial.begin(9600);  //블루투스 시리얼 개방
}

void setRGB(int i){
   red = i;
   blue = 255 - i;
   green = (int)(red + blue)/2; 
}

void resetRGB(){
  red = 0;
  green = 0;
  blue = 0;
}

void turnRGB(){
  analogWrite( Red_LED, red );
  analogWrite( Green_LED, green );
  analogWrite( Blue_LED, blue );
}

void other(){
  int r = random(3);
  switch(r){
  case 0:
  for(int i = 0 ; i < 20 ; i ++){
  red += i;
  turnRGB();
  delay(10);
  }
  if(red > 255)
  red = 0;
  break;
  case 1:
  for(int i = 0 ; i < 20 ; i ++){
  blue += i;
  turnRGB();
  delay(10);
  }
  if(blue > 255)
  blue = 0;
  break;
  case 2:
  for(int i = 0 ; i < 20 ; i ++){
  green += i;
  turnRGB();
  delay(10);
  }
  if(green > 255)
  green = 0;
  break;
  }
}

void RainBow_Color()
{
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
  }
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
    
    if(myString == "onoff" ){//입력받은 값이 on이면
      int s;
      int i = random(255);//0~255까지의 랜덤 숫자 반환
      if(red == 0 && blue == 0 && green == 0 )
      s = 0;
      if(red > 0 || blue > 0 || green >0)
      s = 1;
      switch(s){
        case 0://OFF 상태라면 무작위 색깔로 ON
          setRGB(i);
          turnRGB();
          break;
        case 1://ON 상태라면 OFF
          resetRGB();
          digitalWrite(Red_LED, HIGH);//근데 왜 HIGH로 해야 꺼지지?
          digitalWrite(Green_LED, HIGH);
          digitalWrite(Blue_LED, HIGH);
          break;
      }
     }
     if(myString == "other" ){//다른색깔로바꿔줌
       other();
       //analogWrite( Red_LED, red );
       //analogWrite( Green_LED, green );
       //analogWrite( Blue_LED, blue );
      }
    if(myString == "sleep" ){
      while(!mySerial.available())  //mySerial에 전송된 값이 없다면 반복 있으면 정지
      {
        RainBow_Color();//무지개빛 계속반복
      }
    }
   
    myString="";  //myString 변수값 초기화
  }
  }


