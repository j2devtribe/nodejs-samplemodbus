#include <ModbusRTUSlave.h>

u16 _D[100];				//D���� 100��
u8 _M[50];				//M���� 400��
ModbusRTUSlave rtu(1, &Serial1);	//���� 1��, ���:Serial1
u32 prev; 
void setup() {
  pinMode(3, OUTPUT);			//3����Ʈ ��� ����
  pinMode(4, OUTPUT);			//4����Ʈ ��� ����
  pinMode(5, INPUT);			//5����Ʈ �Է� ����
  rtu.addWordArea(0x7000, _D, 100);	//���念�����: 0x7000������ _D�迭 100
  rtu.addBitArea(0x1000, _M, 50);	//��Ʈ�������: 0x1000������ _M�迭 50
  rtu.begin(9600);			//��żӵ� 9600���� ��Ž���
}
 
void loop()
{
  u32 n = millis();			//���α׷������ð��� �����ͼ�
  if(n-prev>=1000 || n<prev)		//�����ð��� �� 1���̻��̸�
  {					
    setBit(_M, 0, !getBit(_M,0));	//M0 ���� (M0=!M0)	
    digitalWrite(3, getBit(_M,0));	//3�� ��Ʈ�� M0���
    prev=n;				//�����ð� ����
  }
  
  digitalWrite(4, getBit(_M, 1));	//4�� ��Ʈ�� M1 ���
  setBit(_M, 2, digitalRead(5));	//M2�� 5����Ʈ�Է°� ����
  _D[0] = analogRead(0);		//D0�� �Ƴ��α�0�� ����

  rtu.process();			//���ó��
}
