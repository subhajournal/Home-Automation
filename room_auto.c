//Room Automation by 8051 & 555
//Developed By: Subhadeep Chakraborty
#include<reg51.h>

sbit INP = P0^0;       
sbit VIP = P1^7;

sbit LDAR1 = P2^0;     

sbit FAN1 = P2^2;       
sbit FAN2 = P2^3;       

sbit CLGST = P2^4;       
sbit CLGLN = P2^5;       
sbit CLGEN = P2^6;       
sbit BELL = P2^7;       
sbit EN = P0^1;         

sbit DRSEC = P3^5;     
sbit ALT = P3^6;       
sbit PWR = P3^7;       

void cct_init(void);
void delay(int a);

void pwrchk()
{
	if(VIP==1)
	      {
		      PWR=1;
		      ALT=0;
        }
	    else if(VIP==0 && INP==1)
	    {
		     PWR=0;
		     ALT=1;
	    }
}

void bell1()
{
	unsigned int i;
	for(i=1;i<=10;i++)
	  {
		  if(EN==0)
		  {
				if(VIP==1)
	      {
		      PWR=1;
		      ALT=0;
        }
	    else if(VIP==0 && INP==1)
	    {
		     PWR=0;
		     ALT=1;
	    }
			  CLGST=1;
			  BELL=1;
			  pwrchk();
			  delay(30000);
			  pwrchk();
			  BELL=0;
			  pwrchk();
			  delay(15000);
			  if(i==5)
	      {
			    CLGLN=1;
					pwrchk();
			    delay(60000);       
				  CLGLN=0;
			  }
				else if(i==10)
				{
					pwrchk();
					CLGEN=1;
	        CLGST=0;
          CLGLN=0;
	        BELL=0;
					pwrchk();
	        delay(75000);
					main();
				}
		  }
	  }
}

int main()
{
   cct_init();   	       
   while(1)
	 {  
     if(VIP==1)
		 {
			 PWR=1;
			 ALT=0;
			 FAN1 = 1;
			 FAN2 = 1;
			 DRSEC = 1;
			 LDAR1=1;
			 if(EN==0)
			 {
			    bell1();
			 }
		 }
		 else if(VIP==0 && INP==1)
		 {
			 PWR=0;
			 ALT=1;
			 FAN1 = 1;
			 FAN2 = 0;
			 DRSEC = 1;
			 LDAR1=1;
			 if(EN==0)
			 {
			    bell1();
			 }
		 }
		 else if(VIP==0 && INP==0)
		 {
	     break;
	   }
	 }
}
void cct_init(void)
{	
	 P1 = 0x00;
   P2 = 0x00;   
   P3 = 0x00;  
}
void delay(long a)
{
   long i;
   for(i=0;i<a;i++)
   {
		 pwrchk();
	 }
	
}