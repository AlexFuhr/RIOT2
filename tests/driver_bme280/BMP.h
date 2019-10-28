/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
NAME:		BMP_DATA 

AUTOR: 		Alex Fuhr

DATUM: 		21.10.2019

SUMMARY: 	Struktur für BME-280 Sensor um die Datenübergabe zu vereinfachen
###################################################################################
*/



 struct BMP_DATA
{
	int16_t temp[10];
	uint32_t press[10];
	uint16_t hum[10];
};