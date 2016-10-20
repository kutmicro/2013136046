#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출

uint8_t vol = 0x0E;     //mp3 볼륨 설정용
int MPpin1 = 1;
int MPpin2 = 2;
String myString=""; //받는 문자열(블루투스 모듈로)

SoftwareSerial mp3(MPpin1, MPpin2);       //시리얼 통신을 위한 객체선언(mp3 모듈)
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mp3.begin(9600);       //mp3 플레이어 모듈 시리얼 개방
  delay(100);
}
//MP3 모듈로 무슨 동작을 할 것인지 확인 및 설정하는 함수

boolean SetMusicPlay(uint8_t hbyte, uint8_t lbyte)
{//음악 재생을 
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
{//다음 음악을 재생함
  mp3.write(0x7E); 
  mp3.write(0x04);
  mp3.write(0xA5);
  mp3.write(0x7E);
  //위 코드는 MP3 모듈에 시리얼로 명령 형식에 맞추어 전송하는 코드
  delay(10);
  while (mp3.available())//만약 MP3 모듈이 입력가능/사용 가능 상태라면
  {//시리얼을 통해 읽어진 명령이 이와 같다면 해당값 반환
    if (0xA0 == mp3.read())
      return true;
    else
      return false;
  }
}
  boolean PrevMusicPlay()
{//이전 곡 재생
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
{//일시정지
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
{//볼륨 설정 볼륨 범위는 0~31까지 총 32레벨
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
{//음악을 어떤 방식으로 재생할지 설정해주는 코드
  if (((playmode == 0x00) | (playmode == 0x01) | (playmode == 0x02) | (playmode == 0x03)) == false)
  {
    Serial.println("PlayMode Parameter Error! ");
    return false;
  }
  mp3.write(0x7E);
  mp3.write(0x03);
  mp3.write(0xA9);
  mp3.write(playmode);//여기에 입력
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

  //BLUETOOTH 모듈로 입력받은 명령에 따라서 실행되게 됨
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
        
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
      if(vol == 0x1F) {} //최대 볼륨이면 동작하지 않음
      vol += 1;
      SetVolume(vol);//볼륨 범위 0x00 to 0x1F
     }
    
    if(myString == "voldown" ){
      if( vol == 0x00 ) {} //최소 볼륨이면 동작하지 않음
      vol -= 1;
      SetVolume(vol);//볼륨 범위 0x00 to 0x1F
    }

    myString="";  //myString 변수값 초기화 재입력을 받기위함
  }

}
