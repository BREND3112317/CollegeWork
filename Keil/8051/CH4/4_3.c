/********** 4_3.c *****************************
*�ʧ@�G�O��zSPEAK��X��i,KEY=0�W�[���ɮɶ�
***********************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sbit   KEY=P3^2;   //�����P32��J
sbit   SPEAK=P2^6; //P26��z��X 
main() 
{
  unsigned char dly=1;  //�����ܼ�
  while(1)        //���_�`������
  {
    SPEAK=!SPEAK;  //SPEAK�Ϭ�,�O��z�o�X�n��
    Delay_ms(dly); //�I�s���ɨ��,��dly�M�w���ɮɶ�
    if(KEY==0) dly++; //�YKEY=0�W�[���ɮɶ�
  }
}