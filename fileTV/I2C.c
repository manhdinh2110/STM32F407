#include "I2C.h"
	int data1;
void I2Cini(void)
{
GPIO_InitTypeDef GPIOBI2C;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);	
	
I2C_InitTypeDef I2Cinit;
	
GPIOBI2C.GPIO_Mode=GPIO_Mode_AF;
GPIOBI2C.GPIO_OType=GPIO_OType_OD;
GPIOBI2C.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_8;
GPIOBI2C.GPIO_PuPd=GPIO_PuPd_UP;
GPIOBI2C.GPIO_Speed=GPIO_Speed_100MHz;
GPIO_Init(GPIOB,&GPIOBI2C);
GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_I2C1);
GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_I2C1);

I2C_DeInit(I2C1);	
I2Cinit.I2C_Ack=I2C_Ack_Enable ;
I2Cinit.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
I2Cinit.I2C_ClockSpeed=100000;
I2Cinit.I2C_DutyCycle=I2C_DutyCycle_2;
I2Cinit.I2C_Mode=I2C_Mode_I2C;
I2Cinit.I2C_OwnAddress1=0x01;
I2C_Init(I2C1,&I2Cinit);

I2C_Cmd(I2C1,ENABLE);
}

void I2Cini1(void)
{
GPIO_InitTypeDef GPIOBI2C;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);	
	
I2C_InitTypeDef I2Cinit;
	
GPIOBI2C.GPIO_Mode=GPIO_Mode_AF;
GPIOBI2C.GPIO_OType=GPIO_OType_OD;
GPIOBI2C.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
GPIOBI2C.GPIO_PuPd=GPIO_PuPd_UP;
GPIOBI2C.GPIO_Speed=GPIO_Speed_100MHz;
GPIO_Init(GPIOB,&GPIOBI2C);
GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C2);
GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C2);

I2C_DeInit(I2C2);	
I2Cinit.I2C_Ack=I2C_Ack_Enable ;
I2Cinit.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
I2Cinit.I2C_ClockSpeed=100000;
I2Cinit.I2C_DutyCycle=I2C_DutyCycle_2;
I2Cinit.I2C_Mode=I2C_Mode_I2C;
I2Cinit.I2C_OwnAddress1=0x01;
I2C_Init(I2C2,&I2Cinit);

I2C_Cmd(I2C2,ENABLE);
}





void I2CGPIO(void)
{
RCC->AHB1ENR|=(1<<1);//enable GPIOB
GPIOB->MODER|=(2<<14)|(2<<16);//AF mode gpiob 7,8
GPIOB->OTYPER|=(1<<7)|(1<<8);//gpiob 7,8 open drain
GPIOB->OSPEEDR|=(2<<14)|(2<<16);//High speed gpiob 7,8
GPIOB->PUPDR|=(1<<14)|(1<<16);//Pull up gpiob 7,8
GPIOB->AFR[0]|=(4<<28);//AF4 to PB7
GPIOB->AFR[1]|=(4<<0);//AF4 to PB8
}
void I2Cset()
{
RCC->APB1ENR|=(1<<21);//enable I2C1
//I2C1->CR1|=(1<<15);//reset I2C
//I2C1->CR1&=~(1<<15);
I2C1->CR2|=(42<0);//set clock phai bang clock cua ABP1 42Mhz
//I2C1->CCR&=~(1<<15);//normal mod i2c
//I2C1->CCR&=~(1<<14);//duty 50%	
I2C1->CCR|=(420<<0);//100khz
I2C1->TRISE=43;//max rise time 1000ns Trise=(maxrisetime*42Mhz)+1
I2C1->CR1|=(1<<0);
	
}
void I2Cstart()
{
I2C1->CR1|=(1<<8);//bat dau giao tiep
while(~(I2C1->SR1&(1<<0)));//doi khi dieu kien start xuat hien SDA keo xuong 0 truoc sau do toi SCL keo xuong 0
}

void I2Ctran(char dulieu[])
{for(int i=0;dulieu[i]!=0x00;i++)
{while(~(I2C1->SR1&(1<<7)));//doi thanh ghi DR trong
I2C1->DR=dulieu[i];
while(~(I2C1->SR1&(1<<2)));//doi du lieu truyen xong
}
}
void I2Cadd(uint8_t diachi)
{while(~(I2C1->SR1&(1<<7)));//doi thanh ghi DR trong
I2C1->DR=diachi;
while(~(I2C1->SR1&(1<<1)));//doi dia chi truyen xong luu y phai co slave phan hoi
int clear=I2C1->SR1|I2C1->SR2;//xoa co ADDR
}	
void I2Cstop()
{	I2C1->CR1|=(1<<9);//stop
}
//void I2Cre(uint8_t Address,uint8_t *buffer,uint8_t size)
//{int remaining = size;
//	
///**** STEP 1 ****/	
//	if (size == 1)
//	{
//		/**** STEP 1-a ****/	
//		I2C1->DR = Address;  //  send the address
//		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
//		
//		/**** STEP 1-b ****/	
//		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit 
//		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
//		I2C1->CR1 |= (1<<9);  // Stop I2C

//		/**** STEP 1-c ****/	
//		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
//		
//		/**** STEP 1-d ****/	
//		buffer[size-remaining] = I2C1->DR;  // Read the data from the DATA REGISTER
//		
//	}

///**** STEP 2 ****/		
//	else 
//	{
//		/**** STEP 2-a ****/
//		I2C1->DR = Address;  //  send the address
//		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
//		
//		/**** STEP 2-b ****/
//		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
//		
//		while (remaining>2)
//		{
//			/**** STEP 2-c ****/
//			while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
//			
//			/**** STEP 2-d ****/
//			buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer			
//			
//			/**** STEP 2-e ****/
//			I2C1->CR1 |= 1<<10;  // Set the ACK bit to Acknowledge the data received
//			
//			remaining--;
//		}
//		
//		// Read the SECOND LAST BYTE
//		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
//		buffer[size-remaining] = I2C1->DR;
//		
//		/**** STEP 2-f ****/
//		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit 
//		
//		/**** STEP 2-g ****/
//		I2C1->CR1 |= (1<<9);  // Stop I2C
//		
//		remaining--;
//		
//		// Read the Last BYTE
//		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
//		buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer
//	}	
//}


void I2C_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t data)
{
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, deviceAddr<<1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, regAddr);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			I2C_AcknowledgeConfig(I2C1,DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Read(uint8_t deviceAddr, uint8_t regAddr,uint16_t *diachi,uint8_t len) 
{ int count;

  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	 I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, deviceAddr<<1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, regAddr);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, (deviceAddr<<1), I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	I2C_AcknowledgeConfig(I2C1,ENABLE);
	while(len>0)
	{
//	I2C_Cmd(I2C1,ENABLE);
		if(len==1)
		{	I2C_AcknowledgeConfig(I2C1,DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);}
		
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)))
		;

  *diachi=I2C_ReceiveData(I2C1);
	len--;
	diachi++;
		I2C_AcknowledgeConfig(I2C1,ENABLE);
	}
} 
void I2C_Read1(uint8_t deviceAddr, uint8_t regAddr,uint16_t *diachi,uint8_t len) 
{while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))
	;
    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C2, (deviceAddr<<1),I2C_Direction_Transmitter)
	;
    while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			;
	    I2C_SendData(I2C2, regAddr);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	  I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C2, (deviceAddr<<1), I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
			I2C_AcknowledgeConfig(I2C2,ENABLE);
//	I2C_Cmd(I2C1,ENABLE);
		while(len>0)
	{
//	I2C_Cmd(I2C1,ENABLE);
		if(len==1)
		{	I2C_AcknowledgeConfig(I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
		}
		
	while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)))
		;

  *diachi=I2C_ReceiveData(I2C2);
	len--;
	diachi++;
		I2C_AcknowledgeConfig(I2C2,ENABLE);
	}
}

void I2C_Write1(uint8_t deviceAddr, uint8_t regAddr, uint8_t data)
{
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, deviceAddr<<1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C2, regAddr);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C2, data);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			I2C_AcknowledgeConfig(I2C2,DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
}