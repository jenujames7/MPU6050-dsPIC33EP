/* 
 * File:   i2c_header.h
 * Author: user
 *
 * Created on July 14, 2015, 4:12 PM
 */

#ifndef I2C_HEADER_H
#define	I2C_HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void i2c2_init(void);
    void IdleI2C2(void);
    
    void I2C2Write(uint8_t devAddr,uint16_t regAddr,uint8_t data);
    void I2C2writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
    bool I2C2writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) ;
    void I2C2writeBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr);
    void I2C2writeWord(uint8_t devAddr,uint8_t regAddr,uint16_t data);
    
    uint8_t I2C2Read(uint8_t devAddr,uint16_t regAddr);
    uint8_t I2C2readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    uint8_t I2C2readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
    void I2C2readBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr);
    
    void I2C2_page_Write(unsigned char deviceId,unsigned char address,unsigned char len,unsigned char *dataptr);
    void I2C2_page_Read(unsigned char deviceId,unsigned char address,unsigned char len,unsigned char *dataptr);
    
        #define PAGESIZE	16
    //Low Level Functions
    unsigned int IdleI2C(void);
    unsigned int StartI2C(void);
    unsigned int WriteI2C(unsigned char);
    unsigned int StopI2C(void);
    unsigned int RestartI2C(void);
    unsigned int getsI2C(unsigned char*, unsigned char);
    unsigned int NotAckI2C(void);
    unsigned int InitI2C(void);
    unsigned int ACKStatus(void);
    unsigned int getI2C(void);
    unsigned int AckI2C(void);
    unsigned int EEAckPolling(unsigned char);
    unsigned int putstringI2C(unsigned char *,unsigned char );

    //High Level Functions for Low Density Devices
    unsigned int LDByteReadI2C(unsigned char, unsigned char, unsigned char*, unsigned char);
    unsigned int LDByteWriteI2C(unsigned char, unsigned char, unsigned char);
    unsigned int LDPageWriteI2C(unsigned char, unsigned char , unsigned char *,unsigned char );
    unsigned int LDSequentialReadI2C(unsigned char, unsigned char, unsigned char*, unsigned char);

    //High Level Functions for High Density Devices
    unsigned int HDByteReadI2C(unsigned char, unsigned char, unsigned char, unsigned char*, unsigned char);
    unsigned int HDByteWriteI2C(unsigned char, unsigned char, unsigned char, unsigned char);
    unsigned int HDPageWriteI2C(unsigned char , unsigned char , unsigned char, unsigned char*,unsigned char);
    unsigned int HDSequentialReadI2C(unsigned char, unsigned char, unsigned char, unsigned char*, unsigned char);
    
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_HEADER_H */

