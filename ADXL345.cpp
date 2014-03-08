#include "ADXL345.h"
#include <Wire.h>
#include <inttypes.h>
#include <Arduino.h>



uint8_t* ADXL345::Read(uint8_t address, int length){
	Wire.beginTransmission(m_Address);
	Wire.write(address);
	Wire.endTransmission();
	Wire.beginTransmission(m_Address);
	Wire.requestFrom(m_Address,length);

	
	uint8_t buffer[length];
	int i = 0;
	
	while(Wire.available()){
			
			buffer[i] = Wire.read();
			i++;
			
		
	}
	
	
	if(i == length){
	return buffer;
	}
	return NULL;

}

void ADXL345::Write(uint8_t address, uint8_t command){
	Wire.beginTransmission(m_Address);
	Wire.write(address);
	Wire.write(command);
	Wire.endTransmission();


}
void ADXL345::EnableTabDetaction(){

	
	Write(INT_MAP, 0x9F);
	Write(TAP_AXES,0x01);
	Write(THRESH_TAP,0x38);
	Write(DURATION,0x10);
	Write(LATENT, 0x50);
	Write(WINDOW, 0xFF);
  
  //Enable the Single and Double Taps.
	Write(INT_ENABLE, 0xE0);  
}

bool ADXL345::Ensureconnected(){
	if(Read(0x00,1)[0] == 0xE5){
		return true;
	}else
		return false;
}

void ADXL345::EnableMeasurement(){
	Write(Register_PowerControl, 0x08);
}

void ADXL345::DeviceStandBy()
{
	Write(Register_PowerControl, 0x00);
}


GData ADXL345::GetData(){
	GData data = GData();
	int temp;
	uint8_t* buffer = Read(Register_DataX,6);
	temp = buffer[1]<<8|buffer[0];
	data.Data_X = temp * scale;
	temp = buffer[3]<<8|buffer[2];
	data.Data_Y = temp * scale;
	temp = buffer[5]<<8|buffer[4];
	data.Data_Z = temp * scale;
	
	return data;

}

GData ADXL345::GetReliableData(){

	GData data2 = GData();
	GData data = GData();
	do{
	data = GetData();
	delay(20);
	data2 = GetData();
	
	}while(abs(((data.Data_X)-(data2.Data_X)))>0.5 or abs(((data.Data_Y)-(data2.Data_Y)))>0.5 or abs(((data.Data_Z)-(data2.Data_Z)))>0.5 );
	return data2;

}




