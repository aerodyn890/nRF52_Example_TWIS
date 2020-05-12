/*
 *  Roverdyn TWIS(Slave) Library
 *  Updated at May 12, 2020
 *  Version : 1.1
 *  Author : Seonguk Jeong
 *  Copyright to 2020 Seonguk Jeong. All rights reserved.
 *  Contact : jswcomkr@roverdyn.com
 */

#include "TWIS.h"

uint8_t _TWIS::rxBuffer0[60], _TWIS::txBuffer0[60], _TWIS::rxBuffer1[60], _TWIS::txBuffer1[60];

void _TWIS::initTWIS0(uint8_t pinSDA, uint8_t pinSCL, uint8_t addr0){
	// TWI Slave0 mode 초기화 함수
	// TWI Slave0 비활성화
	NRF_TWIS0->ENABLE = 0;

	// TWIS 핀 설정
	NRF_TWIS0->PSEL.SCL = pinSCL;
	NRF_TWIS0->PSEL.SDA = pinSDA;

	// TWIS 주소 설정
	NRF_TWIS0->ADDRESS[0] = addr0;

	// TWIS 주소 활성화 여부 설정
	NRF_TWIS0->CONFIG = 0x01;	// ADDRESS[0]과 매칭

	// 인터럽트 비활성화
	NRF_TWIS0->INTENCLR = 0xffffffff;

	// 버퍼 설정
	NRF_TWIS0->RXD.PTR = (uint32_t)rxBuffer0;
	NRF_TWIS0->TXD.PTR = (uint32_t)txBuffer0;

	// TWIS 활성화
	NRF_TWIS0->ENABLE = 9;
}

void _TWIS::initTWIS1(uint8_t pinSDA, uint8_t pinSCL, uint8_t addr0){
	// TWI Slave1 mode 초기화 함수
	// TWI Slave1 비활성화
	NRF_TWIS1->ENABLE = 0;

	// TWIS 핀 설정
	NRF_TWIS1->PSEL.SCL = pinSCL;
	NRF_TWIS1->PSEL.SDA = pinSDA;

	// TWIS 주소 설정
	NRF_TWIS1->ADDRESS[0] = addr0;

	// TWIS 주소 활성화 여부 설정
	NRF_TWIS1->CONFIG = 0x01;	// ADDRESS[0]과 매칭

	// 인터럽트 비활성화
	NRF_TWIS1->INTENCLR = 0xffffffff;

	// 버퍼 설정
	NRF_TWIS1->RXD.PTR = (uint32_t)rxBuffer1;
	NRF_TWIS1->TXD.PTR = (uint32_t)txBuffer1;

	// TWIS 활성화
	NRF_TWIS1->ENABLE = 9;
}

void _TWIS::writeByte0(uint8_t *data, uint8_t length){
	// Master에 데이터를 보내는 함수
	// 보낼 데이터의 크기 설정
	NRF_TWIS0->TXD.MAXCNT = length;

	// 데이터 입력
	for(uint8_t i=0;i<length;i++){
		txBuffer0[i] = data[i];
	}

	// PREPARETX 플래그 설정
	NRF_TWIS0->TASKS_PREPARETX = 1;

	// 데이터 전송
	while(!NRF_TWIS0->EVENTS_STOPPED){}
	NRF_TWIS0->EVENTS_STOPPED = 0;
}

void _TWIS::writeByte1(uint8_t *data, uint8_t length){
	// Master에 데이터를 보내는 함수
	// 보낼 데이터의 크기 설정
	NRF_TWIS1->TXD.MAXCNT = length;

	// 데이터 입력
	for(uint8_t i=0;i<length;i++){
		txBuffer1[i] = data[i];
	}

	// PREPARETX 플래그 설정
	NRF_TWIS1->TASKS_PREPARETX = 1;

	// 데이터 전송
	while(!NRF_TWIS1->EVENTS_STOPPED){}
	NRF_TWIS1->EVENTS_STOPPED = 0;
}

void _TWIS::readByte0(uint8_t *readData, uint8_t *length){
	// Master가 보낸 데이터를 읽는 함수
	// 최대 수신 바이트 수 256
	uint8_t *output = readData;
	NRF_TWIS0->RXD.MAXCNT = 256;

	// START RX
	NRF_TWIS0->TASKS_PREPARERX = 0x01;
	while(!NRF_TWIS0->EVENTS_RXSTARTED){}
	NRF_TWIS0->EVENTS_RXSTARTED = 0;
	while(!NRF_TWIS0->EVENTS_STOPPED){}
	NRF_TWIS0->EVENTS_STOPPED = 0;

	// Save data
	uint8_t recvLen = NRF_TWIS0->RXD.AMOUNT;
	length = &recvLen;
	for(uint8_t i=0;i<recvLen;i++){
		output[i] = rxBuffer0[i];
	}
}

void _TWIS::readByte1(uint8_t *readData, uint8_t *length){
	// Master가 보낸 데이터를 읽는 함수
	// 최대 수신 바이트 수 256
	uint8_t *output = readData;
	NRF_TWIS1->RXD.MAXCNT = 256;

	// START RX
	NRF_TWIS1->TASKS_PREPARERX = 0x01;
	while(!NRF_TWIS1->EVENTS_RXSTARTED){}
	NRF_TWIS1->EVENTS_RXSTARTED = 0;
	while(!NRF_TWIS1->EVENTS_STOPPED){}
	NRF_TWIS1->EVENTS_STOPPED = 0;

	// Save data
	uint8_t recvLen = NRF_TWIS1->RXD.AMOUNT;
	length = &recvLen;
	for(uint8_t i=0;i<recvLen;i++){
		output[i] = rxBuffer0[i];
	}
}

void _TWIS::stopTWIS0(void){
	NRF_TWIS0->ENABLE = 0;
}

void _TWIS::stopTWIS1(void){
	NRF_TWIS1->ENABLE = 0;
}
