/********** 4_5.C ****************************
*�ʧ@�G�C���@��KEY����A����LED���[��X�ΰ���
***********************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr    LED=0x80; //P0��LED��X
sbit   KEY=P3^2; //����}����P32��J
bit flag=1;    //�]�wbit�ܼ� 
 
main() 
{
  LED=0;   //LED��X 
  while(1)       //���а��� 
   {		     //�Yflag=0�A�������즹�B
     if(KEY==0)      //�Y������Aflag�Ϭ�
	  {
	   flag=!flag;    //flag�Ϭ�
	   while(KEY==0); //�Y����}��A���� 
	  }
	 if(flag==0) continue;//�Yflag=0�A��������j��̫e��
 	 LED++;		    //�Yflag=1,LED���[��X
	 Delay_ms(100); //����             
   }
}