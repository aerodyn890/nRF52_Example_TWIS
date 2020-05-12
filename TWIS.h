/*
 *  Roverdyn TWIS(Slave) Library
 *  Updated at May 12, 2020
 *  Version : 1.1
 *  Author : Seonguk Jeong
 *  Copyright to 2020 Seonguk Jeong. All rights reserved.
 *  Contact : jswcomkr@roverdyn.com
 */

#ifndef TWIS_H_
#define TWIS_H_

#include <nrf_twis.h>
#include <nrf_twi.h>

class _TWIS{
private:
	static uint8_t rxBuffer0[60], txBuffer0[60], rxBuffer1[60], txBuffer1[60];
public:
	void initTWIS0(uint8_t pinSDA, uint8_t pinSCL, uint8_t addr);
	void initTWIS1(uint8_t pinSDA, uint8_t pinSCL, uint8_t addr);
	void writeByte0(uint8_t *data, uint8_t length);
	void writeByte1(uint8_t *data, uint8_t length);
	void readByte0(uint8_t *readData, uint8_t *length);
	void readByte1(uint8_t *readData, uint8_t *length);
	void stopTWIS0(void);
	void stopTWIS1(void);
};



#endif /* TWIS_H_ */
