
#include "../main.h"

/**************************************************************************************/
void i2c2_init()
{
    I2C2BRG  =    141;     //400Khz
    I2C2STAT = 0x0000;
    I2C2CONbits.I2CSIDL  =   0;
    I2C2CONbits.SCLREL   =   0;
    I2C2CONbits.IPMIEN   =   0;
    I2C2CONbits.A10M     =   0;
    I2C2CONbits.DISSLW   =   0;
    I2C2CONbits.SMEN     =   0;
    I2C2CONbits.GCEN     =   0;
    I2C2CONbits.STREN    =   0;
    I2C2CONbits.ACKDT    =   0;
    I2C2CONbits.ACKEN    =   0;
    I2C2CONbits.RCEN     =   0;
    I2C2CONbits.PEN      =   0;
    I2C2CONbits.RSEN     =   0;
    I2C2CONbits.SEN      =   0;
    I2C2CONbits.I2CEN    =   1;
}
/**************************************************************************************/
void IdleI2C2(void)
{
    // Wait until I2C Bus is Inactive
    uint8_t exit;
    while(1)
    {
        exit = 1;
        if(I2C2STATbits.IWCOL) I2C2STATbits.IWCOL=0;
        if(I2C2CONbits.SEN) exit = 0;
        if(I2C2CONbits.PEN) exit = 0;
        if(I2C2CONbits.RCEN) exit = 0;
        if(I2C2CONbits.RSEN) exit = 0;
        if(I2C2CONbits.ACKEN) exit = 0;
        if(I2C2STATbits.TRSTAT) exit = 0;
        if(exit) break;
    }
    Nop();
}
/**************************************************************************************/
void I2C2Write(uint8_t devAddr,uint16_t regAddr,uint8_t data)
{
    IdleI2C2();
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    
    MasterWriteI2C2(devAddr|0);
    MasterWriteI2C2(regAddr&0x00FF);
    MasterWriteI2C2(data);

    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);                     
    IFS3bits.MI2C2IF = 0;
    __delay32(80000);
}
/**************************************************************************************/
void I2C2writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) 
{
    uint8_t b;
    b = I2C2Read(devAddr, regAddr);
    
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    I2C2Write(devAddr, regAddr, b);
}
/**************************************************************************************/
bool I2C2writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) 
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b = I2C2Read(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    b &= ~(mask); // zero all important bits in existing byte
    b |= data; // combine data with existing byte
    I2C2Write(devAddr, regAddr, b);
    return true;
}
/**************************************************************************************/
void I2C2writeBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr)
{
    while(len--)
    {
        I2C2Write(devAddr,regAddr,*dptr++);
    }
}
/**************************************************************************************/
void I2C2writeWord(uint8_t devAddr,uint8_t regAddr,uint16_t data)
{
    I2C2Write(devAddr, regAddr++, (data>>8)&0xFF);
    I2C2Write(devAddr, regAddr, data&0xFF);
}
/**************************************************************************************/
uint8_t I2C2Read(uint8_t devAddr,uint16_t regAddr)
{
    uint8_t read_data=0;

    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0; 
    
    MasterWriteI2C2(devAddr|0);
    MasterWriteI2C2(regAddr&0x00FF);
    
    I2C2CONbits.RSEN = 1;
    while(I2C2CONbits.RSEN);
    IFS3bits.MI2C2IF = 0;  
    
    MasterWriteI2C2(devAddr|1);
    read_data = MasterReadI2C2();

    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
    IFS3bits.MI2C2IF = 0;
    return  read_data;
}
/**************************************************************************************/
uint8_t I2C2readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) 
{
    uint8_t b=0;
    uint8_t count = I2C2Read(devAddr, regAddr);
    *data = b & (1 << bitNum);
    return count;
}
/**************************************************************************************/
uint8_t I2C2readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data)
{
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count=0, b=0;
    b = I2C2Read(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    b &= mask;
    b >>= (bitStart - length + 1);
    *data = b;
    return count;
}
/**************************************************************************************/
void I2C2readBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr)
{
    while(len--)
    {
        *dptr = I2C2Read(devAddr,regAddr);
    }
}
/*********************************************************************
* Function:        StartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an I2C Start Condition
*
* Note:			None
********************************************************************/
unsigned int StartI2C(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C2CONbits.SEN = 1;		//Generate Start COndition
	while (I2C2CONbits.SEN);	//Wait for Start COndition
	//return(I2C2STATbits.S);	//Optionally return status
    return 0;
}


/*********************************************************************
* Function:        RestartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a restart condition and optionally returns status
*
* Note:			None
********************************************************************/
unsigned int RestartI2C(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C2CONbits.RSEN = 1;		//Generate Restart		
	while (I2C2CONbits.RSEN);	//Wait for restart	
	//return(I2C2STATbits.S);	//Optional - return status
    return 0;
}


/*********************************************************************
* Function:        StopI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a bus stop condition
*
* Note:			None
********************************************************************/
unsigned int StopI2C(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C2CONbits.PEN = 1;		//Generate Stop Condition
	while (I2C2CONbits.PEN);	//Wait for Stop
	//return(I2C2STATbits.P);	//Optional - return status
    return 0;
}


/*********************************************************************
* Function:        WriteI2C()
*
* Input:		Byte to write.
*
* Output:		None.
*
* Overview:		Writes a byte out to the bus
*
* Note:			None
********************************************************************/
unsigned int WriteI2C(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C2STATbits.TRSTAT);	//Wait for bus to be idle
	I2C2TRN = byte;					//Load byte to I2C2 Transmit buffer
	while (I2C2STATbits.TBF);		//wait for data transmission
    return 0;
}


/*********************************************************************
* Function:        IdleI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Waits for bus to become Idle
*
* Note:			None
********************************************************************/
unsigned int IdleI2C(void)
{
	while (I2C2STATbits.TRSTAT);		//Wait for bus Idle
    return 0;
}


/*********************************************************************
* Function:        LDByteWriteI2C()
*
* Input:		Control Byte, 8 - bit address, data.
*
* Output:		None.
*
* Overview:		Write a byte to low density device at address LowAdd
*
* Note:			None
********************************************************************/
unsigned int LDByteWriteI2C(unsigned char ControlByte, unsigned char LowAdd, unsigned char data)
{
	unsigned int ErrorCode;

	IdleI2C();						//Ensure Module is Idle
	StartI2C();						//Generate Start COndition
	WriteI2C(ControlByte);			//Write Control byte
	IdleI2C();

	ErrorCode = ACKStatus();		//Return ACK Status
	
	WriteI2C(LowAdd);				//Write Low Address
	IdleI2C();

	ErrorCode = ACKStatus();		//Return ACK Status

	WriteI2C(data);					//Write Data
	IdleI2C();
	StopI2C();						//Initiate Stop Condition
//	EEAckPolling(ControlByte);		//Perform ACK polling
	return(ErrorCode);
}


/*********************************************************************
* Function:        LDByteReadI2C()
*
* Input:		Control Byte, Address, *Data, Length.
*
* Output:		None.
*
* Overview:		Performs a low density read of Length bytes and stores in *Data array
*				starting at Address.
*
* Note:			None
********************************************************************/
unsigned int LDByteReadI2C(unsigned char ControlByte, unsigned char Address, unsigned char *Data, unsigned char Length)
{
	IdleI2C();					//wait for bus Idle
	StartI2C();					//Generate Start Condition
	WriteI2C(ControlByte);		//Write Control Byte
	IdleI2C();					//wait for bus Idle
	WriteI2C(Address);			//Write start address
	IdleI2C();					//wait for bus Idle

	RestartI2C();				//Generate restart condition
	WriteI2C(ControlByte | 0x01);	//Write control byte for read
	IdleI2C();					//wait for bus Idle

	getsI2C(Data, Length);		//read Length number of bytes
	NotAckI2C();				//Send Not Ack
	StopI2C();					//Generate Stop
    return 0;
}

/*********************************************************************
* Function:        LDPageWriteI2C()
*
* Input:		ControlByte, LowAdd, *wrptr.
*
* Output:		None.
*
* Overview:		Write a page of data from array pointed to be wrptr
*				starting at LowAdd
*
* Note:			LowAdd must start on a page boundary
********************************************************************/
unsigned int LDPageWriteI2C(unsigned char ControlByte, unsigned char LowAdd, unsigned char *wrptr,unsigned char len)
{
	IdleI2C();					//wait for bus Idle
	StartI2C();					//Generate Start condition
	WriteI2C(ControlByte);		//send controlbyte for a write
	IdleI2C();					//wait for bus Idle
	WriteI2C(LowAdd);			//send low address
	IdleI2C();					//wait for bus Idle
	putstringI2C(wrptr,len);		//send data
	IdleI2C();					//wait for bus Idle
	StopI2C();					//Generate Stop
	return(0);
}

/*********************************************************************
* Function:        LDSequentialReadI2C()
*
* Input:		ControlByte, address, *rdptr, length.
*
* Output:		None.
*
* Overview:		Performs a sequential read of length bytes starting at address
*				and places data in array pointed to by *rdptr
*
* Note:			None
********************************************************************/
unsigned int LDSequentialReadI2C(unsigned char ControlByte, unsigned char address, unsigned char *rdptr, unsigned char length)
{
    if(length)
    {
        IdleI2C();						//Ensure Module is Idle
        StartI2C();						//Initiate start condition
        WriteI2C(ControlByte);			//write 1 byte
        IdleI2C();						//Ensure module is Idle
        WriteI2C(address);				//Write word address
        IdleI2C();						//Ensure module is idle
        RestartI2C();					//Generate I2C Restart Condition
        WriteI2C(ControlByte | 0x01);	//Write 1 byte - R/W bit should be 1 for read
        IdleI2C();						//Ensure bus is idle
        getsI2C(rdptr, length);			//Read in multiple bytes
        NotAckI2C();					//Send Not Ack
        StopI2C();						//Send stop condition
    }
	return(0);
}

/*********************************************************************
* Function:        ACKStatus()
*
* Input:		None.
*
* Output:		Acknowledge Status.
*
* Overview:		Return the Acknowledge status on the bus
*
* Note:			None
********************************************************************/
unsigned int ACKStatus(void)
{
	return (!I2C2STATbits.ACKSTAT);		//Return Ack Status
}


/*********************************************************************
* Function:        NotAckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a NO Acknowledge on the Bus
*
* Note:			None
********************************************************************/
unsigned int NotAckI2C(void)
{
	I2C2CONbits.ACKDT = 1;			//Set for NotACk
	I2C2CONbits.ACKEN = 1;
	while(I2C2CONbits.ACKEN);		//wait for ACK to complete
	I2C2CONbits.ACKDT = 0;			//Set for NotACk
    return 0;
}


/*********************************************************************
* Function:        AckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an Acknowledge.
*
* Note:			None
********************************************************************/
unsigned int AckI2C(void)
{
	I2C2CONbits.ACKDT = 0;			//Set for ACk
	I2C2CONbits.ACKEN = 1;
	while(I2C2CONbits.ACKEN);		//wait for ACK to complete
    return 0;
}


/*********************************************************************
* Function:       getsI2C()
*
* Input:		array pointer, Length.
*
* Output:		None.
*
* Overview:		read Length number of Bytes into array
*
* Note:			None
********************************************************************/
unsigned int getsI2C(unsigned char *rdptr, unsigned char Length)
{
	while (Length --)
	{
		*rdptr++ = getI2C();		//get a single byte
		
		if(I2C2STATbits.BCL)		//Test for Bus collision
		{
			return(-1);
		}

		if(Length)
		{
			AckI2C();				//Acknowledge until all read
		}
	}
	return(0);
}


/*********************************************************************
* Function:        getI2C()
*
* Input:		None.
*
* Output:		contents of I2C2 receive buffer.
*
* Overview:		Read a single byte from Bus
*
* Note:			None
********************************************************************/
unsigned int getI2C(void)
{
	I2C2CONbits.RCEN = 1;			//Enable Master receive
	Nop();
	while(!I2C2STATbits.RBF);		//Wait for receive bufer to be full
	return(I2C2RCV);				//Return data in buffer
}


/*********************************************************************
* Function:        putstringI2C()
*
* Input:		pointer to array.
*
* Output:		None.
*
* Overview:		writes a string of data upto PAGESIZE from array
*
* Note:			None
********************************************************************/
unsigned int putstringI2C(unsigned char *wrptr,uint8_t len)
{
	unsigned char x;

	for(x = 0; x < len; x++)		//Transmit Data Until Pagesize
	{	
		if(WriteI2C(*wrptr))			//Write 1 byte
		{
			return(-3);				//Return with Write Collision
		}
		IdleI2C();					//Wait for Idle bus
		if(I2C2STATbits.ACKSTAT)
		{
			return(-2);				//Bus responded with Not ACK
		}
		wrptr++;
	}
	return(0);
}
//------------------------------------------------------------------------------


