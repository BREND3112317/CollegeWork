/*******************************************
*函數名稱: Delay
*功能描述: 延時以1mS為單位，石英晶體為11.0592MHz
*********************************************/
void Delay(unsigned int dly) 
{  
  unsigned  char dly1; //內循環變數
  while(dly--)         // 外循環，遞減至0
    for(dly1=0;dly1<113;dly1++); //內循環，延時1ms
} 