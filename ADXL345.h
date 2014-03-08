/*
 * ADXL345.h

 *
 *  Created on: 2014年2月20日
 *      Author: MOVING
 */

#include <inttypes.h>
#include <Wire.h>
#include <inttypes.h>
#include <Arduino.h>

#define	m_Address   (0x53)	  // 定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改)
#define Register_DataFormat 0x31
#define Register_PowerControl 0x2D
#define Register_DataX 0x32
#define Register_DataY 0x34
#define Register_DataZ 0x36
#define FIFO_CTL 0x38
#define FIFO_STATUS 0x39
#define Ratio_2G 0.0039
#define DATA_FROMAT 0x31
#define BW_RATE 0x2C
#define v_TurnOnDevice (0x08)
#define INT_MAP (0x2F)
#define TAP_AXES (0x2A)
#define THRESH_TAP (0x1D)
#define DURATION (0x21)
#define LATENT (0x22)
#define WINDOW (0x23)
#define INT_ENABLE (0x2E)

#ifndef ADXL345_H_
#define ADXL345_H_

struct GData{
	float Data_X,Data_Y,Data_Z;
};

class ADXL345{
public:
	ADXL345(uint8_t adress, float scale):my_adress(adress), scale(scale){}
	ADXL345(){my_adress = m_Address ; scale = Ratio_2G;}
	void Write(uint8_t adress, uint8_t command);
	uint8_t* Read(uint8_t adress, int length);
	GData GetData();
	GData GetReliableData();
	
	bool Ensureconnected();
	void EnableMeasurement();
	void EnableTabDetaction();
	void DeviceStandBy();
private:
	uint8_t my_adress;
	float scale;

};




#endif /* ADXL345_H_ */
