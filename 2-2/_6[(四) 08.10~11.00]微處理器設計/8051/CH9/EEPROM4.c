/********** EEPROM4.C *****"EEPROM 93C66��ߪO******
*�ʧ@�GŪ��16-bit�}�C��Ƽg�JEEPROM�A�A����Ū����P0/P1��X
*���}�GCS=P27,SK=P26,DI=P25,DO=P24,ORG=�}��
***********************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr LED=0x80;   //LED��P0��X
sbit CS=P2 ^7 ;	//EEPROM 93C66���u
sbit SK=P2 ^6 ;
sbit DI=P2 ^5 ;
sbit DO=P2 ^4 ;

unsigned int code Table[] 
 ={0x1111,0x2222,0x3333,0x4444,0x5555,0x6666,0x7777,0x8888}; 
main()
{
	unsigned char i;//��ƭp��
	DI=1; DO=1; CS=0; SK=0;//�]�w���
    EWEN();             //�P��EEPROM�g�J�βM��
	ERAL();             //EEPROM�M�������O����
	for(i=0;i<8;i++)    //�g�J8�����
   	  WRITE_16(i,Table[i]); //�g�J��}�θ��
    EWDS();    //�T��EEPROM�g�J�βM��
    while(1)   //���_����Ū��EEPROM�����
    {  
      for(i=0;i<8;i++) //Ū��8�����
      {
        LED=READ_16(i);    //Ū��EEPROM��16-bit��ƧC�줸�տ�X
		P1=READ_16(i)>>8; //Ū��EEPROM��16-bit��ư��줸�տ�X
	    Delay_ms(100);    //����
      }
   }
}
/****************************************************
 ��ƦW��: Clock
 �\��y�z:�e�J��CEEPROM�ɯ߫H��
*****************************************************/
void Clock(void)
 {
  SK=1;  SK=0;
 }
/****************************************************
 ��ƦW��: SEND
 �\��y�z:�e�JEEPROM��C1-bit��}�θ��
 ��J�ѼơGflag
*****************************************************/
void SEND(bit flag)
 {
   DI=flag; Clock();
 } 
/*****************************************************
 ��ƦW��: SEND8
 �\��y�z: ��CEEPROM�e�J8-bit
 ��J�ѼơGAddr
******************************************************/
void SEND8(unsigned char Addr) 
{
  char i;   
  for(i=0;i<8;i++)         //bit7~0 
   {
     if(Addr & 0x80) DI=1; //�Ybit7=1�A�hDI=1
       else DI= 0;         //�Ybit7=0�A�hDI=0
     Clock();              //��C�ɯߡAbit�e�JEEPROM
     Addr= Addr << 1;      //��}����
   }
}
/********************************************
 ��ƦW��:WRITE_16
 �\��y�z:93C66��CEEPROM�e�J��}��16-bit���
 ��J�ѼơGAddr,ch
*********************************************/
void WRITE_16(unsigned char Addr,unsigned int ch)
{ 
  CS=1;     //�}��EEPROM����
  SEND(1);          //�ҩl�줸 
  SEND(0); SEND(1);	//�ާ@�X01   
  SEND8(Addr);      //�e�J��}  
  SEND8(ch>>8);     //�g�J���줸�ո��
  SEND8(ch);        //�g�J�C�줸�ո��
  CS=0;             //����EEPROM���� 
  CS=1; while(!DO) Clock(); CS=0;//���ݼg�J����	 
}
/*************************************************
 ��ƦW��: READ_16
 �\��y�z: Ū��93C66��CEEPROM���
 ��J�ѼơGAddr
 ��X�ѼơGch
**************************************************/
unsigned int READ_16(unsigned char Addr)
{
  char i;
  unsigned int ch;   //16-bit���
  CS=1;              //�}��EEPROM����  
  SEND(1);           //�ҩl�줸 
  SEND(1); SEND(0);	 //�ާ@�X10   
  SEND8(Addr);       //�e�J��}  
  
  if(DO==0)
  {
	ch=0;  //���=0
	for(i=0; i < 16; i++)//Ū��16-bit���
	 {
	   Clock();         //��C��ƥ�DO��X
	   ch=ch << 1;      //��Ʀ줸����
	   if(DO== 1) ch++; //�YDO=1�A�hch���bit0=1
	 }
   }
  CS=0;       //����EEPROM���� 
  return ch;  //�N16-bit��ưe�^�D�{��
}
/****************************************************
 ��ƦW��: EWEN
 �\��y�z: 93C66��CEEPROM�g�J�βM���P��
****************************************************/
void EWEN(void)   //EEPROM�g�J�βM���P��
{
  CS=1;             //�}��EEPROM����
  SEND(1);          //�ҩl�줸
  SEND(0); SEND(0);	//�ާ@�X00
  SEND8(0xc0);      //�e�J���O�A�P��ٰ�/�g�J�ʧ@
  CS=0;             //����EEPROM����
}
/************************************************
 ��ƦW��: EWDS
 �\��y�z: 93C66��CEEPROM�g�J�βM���T��
***********************************************/
void EWDS(void)  //EEPROM�g�J�βM���T��
{
  CS=1;             //�}��EEPROM����
  SEND(1);          //�ҩl�줸
  SEND(0); SEND(0);	//�ާ@�X00	    
  SEND8(0x00);      //�e�J���O�A�T��ٰ�/�g�J�ʧ@
  CS=0;             //����EEPROM����
} 
/*************************************************
 ��ƦW��: ERAL
 �\��y�z: 93C66��CEEPROM�M�������O����
**************************************************/
void ERAL(void) //EEPROM�M�������O����
{
  CS=1;        //�}��EEPROM����
  SEND(1);     //�ҩl�줸
  SEND(0); SEND(0);  //�e�J�ާ@�X00
  SEND8(0x80); //�e�J���O�A�T��ٰ�/�g�J�ʧ@
  CS=0;        //����EEPROM����
}