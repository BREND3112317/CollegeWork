#include "AT89X52.H" 	//�Ȧs���βպA�]�w	
void test1() {  //��Ʀ�1
	// sfr P0=0x80;
	static char i=10; 
	i=i+1; 
	P0=i; 
} 
void test2() { //��Ʀ�2
	// sfr P1=0x90; 
	char j=10; 
	j=j+1; 
	P1=j; 
} 
void test1(void); 
void test2(void); 
void main() { //�D�{��
	loop: 
		test1();//�i�J��Ʀ�1 
		test2();//�i�J��Ʀ�2 
	goto loop; 
} 
