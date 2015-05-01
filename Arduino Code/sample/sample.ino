#include <ModbusRTUSlave.h>

u16 _D[100];				//D영역 100개
u8 _M[50];				//M영역 400개
ModbusRTUSlave rtu(1, &Serial1);	//국번 1번, 통신:Serial1
u32 prev; 
void setup() {
  pinMode(3, OUTPUT);			//3번포트 출력 설정
  pinMode(4, OUTPUT);			//4번포트 출력 설정
  pinMode(5, INPUT);			//5번포트 입력 설정
  rtu.addWordArea(0x7000, _D, 100);	//워드영역등록: 0x7000번지에 _D배열 100
  rtu.addBitArea(0x1000, _M, 50);	//비트영역등록: 0x1000번지에 _M배열 50
  rtu.begin(9600);			//통신속도 9600으로 통신시작
}
 
void loop()
{
  u32 n = millis();			//프로그램구동시간을 가져와서
  if(n-prev>=1000 || n<prev)		//이전시간과 비교 1초이상이면
  {					
    setBit(_M, 0, !getBit(_M,0));	//M0 반전 (M0=!M0)	
    digitalWrite(3, getBit(_M,0));	//3번 포트로 M0출력
    prev=n;				//이전시간 갱신
  }
  
  digitalWrite(4, getBit(_M, 1));	//4번 포트로 M1 출력
  setBit(_M, 2, digitalRead(5));	//M2에 5번포트입력값 대입
  _D[0] = analogRead(0);		//D0에 아날로그0값 대입

  rtu.process();			//통신처리
}
