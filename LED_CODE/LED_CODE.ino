// 3색 LED 기본 제어 코드

// 어떤 색깔을 제어하는 핀을 몇번 코드에 꽃을지 설정

int Red_LED=3;    //3번 핀은 빨강
int Green_LED=5;  //5번 핀은 초록
int Blue_LED=6;   //6번 핀은 파랑

void LED_Setup(){
  pinMode(Red_LED, OUTPUT);       //RED LED 핀 출력으로 설정
  pinMode(Green_LED, OUTPUT);     //GREEN LED 핀 출력으로 설정
  pinMode(Blue_LED, OUTPUT);      //BLUE LED 핀 출력으로 설정
  }
  
void setup() {
  LED_Setup();//LED 셋업 함수 실행
}
//예시 
void RainBow_Color()//무지개색느낌과 같은 빛을 차례대로 방출
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
//만약 다른 색깔을 내거나 해당 색깔만 보여주고싶으면 해당 핀만 조정하면됨
void loop() {
  RainBow_Color();     //함수 실행
}
