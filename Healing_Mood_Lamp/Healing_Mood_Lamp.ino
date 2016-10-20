#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출

int Red_LED=3;
int Green_LED=5;
int Blue_LED=6;
int blueTx=10;        //Tx (보내는핀 설정)
int blueRx=9;         //Rx (받는핀 설정)

//uint8_t vol = 0x0E;     //mp3 볼륨 설정용
//int MPpin1 = 1;
//int MPpin2 = 2;

SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언1(bluetooth모듈)
SoftwareSerial mp3(MPpin1, MPpin2);       //시리얼 통신을 위한 객체선언2(mp3 모듈)
String myString=""; //받는 문자열

void LED_Setup(){
  pinMode(Red_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);}
  
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mp3.begin(9600);       //mp3 플레이어 모듈 시리얼 개방
  mySerial.begin(9600);  //블루투스 시리얼 개방
  delay(100);
  LED_Setup();
}


void RainBow_Color()//무지개빛 빛 방출
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

  boolean SetMusicPlay(uint8_t hbyte, uint8_t lbyte)
{
  mp3.write(0x7E);
  mp3.write(0x04);
  mp3.write(0xA0);
  mp3.write(hbyte);
  mp3.write(lbyte);
  mp3.write(0x7E);
  delay(10);
  while (mp3.available())
  {
    if (0xA0 == mp3.read())
      return true;
    else
      return false;
  }
}
  boolean NextMusicPlay()
{
  mp3.write(0x7E);
  mp3.write(0x04);
  mp3.write(0xA5);
  mp3.write(0x7E);
  delay(10);
  while (mp3.available())
  {
    if (0xA0 == mp3.read())
      return true;
    else
      return false;
  }
}
  boolean PrevMusicPlay()
{
  mp3.write(0x7E);
  mp3.write(0x04);
  mp3.write(0xA6);
  mp3.write(0x7E);
  delay(10);
  while (mp3.available())
  {
    if (0xA0 == mp3.read())
      return true;
    else
      return false;
  }
}
  boolean MusicPause()
{
  mp3.write(0x7E);
  mp3.write(0x04);
  mp3.write(0xA3);
  mp3.write(0x7E);
  delay(10);
  while (mp3.available())
  {
    if (0xA0 == mp3.read())
      return true;
    else
      return false;
  }
}



//Set the volume, the range is 0x00 to 0x1F
boolean SetVolume(uint8_t volume)
{
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0xA7);
    mp3.write(volume);
    mp3.write(0x7E);
    delay(10);
    while(mp3.available())
    {
        if (0xA7==mp3.read())
        return true;
        else
        return false;
    }
}


boolean SetPlayMode(uint8_t playmode)
{
  if (((playmode == 0x00) | (playmode == 0x01) | (playmode == 0x02) | (playmode == 0x03)) == false)
  {
    Serial.println("PlayMode Parameter Error! ");
    return false;
  }
  mp3.write(0x7E);
  mp3.write(0x03);
  mp3.write(0xA9);
  mp3.write(playmode);//올 트랙 반복 재생을 기본으로함
  mp3.write(0x7E);
  delay(10);
  while (mp3.available())
  {
    if (0xA9 == mp3.read())
      return true;
    else
      return false;
  }
}


void loop() {
  while(mySerial.available())              //mySerial에 전송된 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;                     //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);                             //수신 문자열 끊김 방지
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
      pinMode(Blue_LED, LOW);
     }
    
    if(myString == "start" ){
     SetPlayMode(0x02);//전곡 반복 재생모드로
     delay(1000);
     SetMusicPlay(00,00);//0000 파일부터 재생
     delay(1000);}

    if(myString == "next" ){//다음곡 재생
     NextMusicPlay();
      delay(1000);}
      
    if(myString == "prev" ){//이전곡
     PrevMusicPlay();
      delay(1000);}
      
    if(myString == "pause" ){//일시정지
     MusicPause();
      delay(1000);}
      
    if(myString == "volup" ){
      if(vol == 0x1F) break; //최대 볼륨이면 동작하지 않음
      vol += 1;
      SetVolume(vol);//볼륨 범위 0x00 to 0x1F
     }
    
    if(myString == "voldown" ){
      if( vol == 0x00 ) break; //최소 볼륨이면 동작하지 않음
      vol -= 1;
      SetVolume(vol);//볼륨 범위 0x00 to 0x1F
    }

    myString="";  //myString 변수값 초기화 재입력을 받기위함
  }
  }

