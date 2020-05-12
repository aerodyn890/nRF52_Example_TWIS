/*
 *  Roverdyn TWIS(Slave) Library
 *  Updated at May 12, 2020
 *  Version : 1.1
 *  Author : Seonguk Jeong
 *  Copyright to 2020 Seonguk Jeong. All rights reserved.
 *  Contact : jswcomkr@roverdyn.com
 */

#include <nrf_twis.h>
#include <stdio.h>
#include "TWIS.h"

#define SDA 11
#define SCL 12
#define SLV_ADDR 0x01

_TWIS TWIS;

int main(void){
	// TWIS 라이브러리 초기화
	TWIS.initTWIS0(SDA, SCL, SLV_ADDR);

	while(1){
		// Read data
		uint8_t recvdata[60], senddata[3] = {0x01, 0x02, 0x03}, length = 0;
		TWIS.readByte0(recvdata, &length);
		if(recvdata[0] == 1){
			// Send Data
			TWIS.writeByte0(senddata, 3);
		}

	}
	return 0;
}
