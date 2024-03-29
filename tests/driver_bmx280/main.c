/*
 * Copyright (C) 2016 Kees Bakker, SODAQ
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup tests
 * @{
 *
 * @file
 * @brief       Test application for the BME280 temperature, pressure
 *              and humidity sensor.
 *
 * @author      Kees Bakker <kees@sodaq.com>
 *
 * @}
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "bmx280_params.h"
#include "bmx280.h"
#include "xtimer.h"

#define MM_PER_PASCAL 85	// int 
#define MAINLOOP_DELAY  (1 * 50 * 1000u)      /* 2 seconds delay between printf's */
// delay mitgeben 
uint32_t Middle (bmx280_t *dev, uint32_t time_us, int count)
{

	uint32_t PressureSum = 0;
	/* Get pressure in Pa */
	// For Schleife  
	// Count maximale anzahl ~ 35000
	for (int i=1;i<=count;i++) {        
		bmx280_read_temperature(dev);
		int pressure = bmx280_read_pressure(dev);
		PressureSum += pressure;
		//printf("%d\n", pressure);
		xtimer_usleep(time_us);
	}
	return PressureSum; 
}


int main(void)
{
    bmx280_t dev;
	
    int result;

    puts("BMX280 test application\n");

    printf("+------------Initializing------------+\n");
    result = bmx280_init(&dev, &bmx280_params[0]);
    if (result == -1) {
        puts("[Error] The given i2c is not enabled");
        return 1;
    }

    if (result == -2) {
        printf("[Error] The sensor did not answer correctly at address 0x%02X\n", bmx280_params[0].i2c_addr);
        return 1;
    }

    printf("Initialization successful\n\n");

    printf("+------------Calibration Data------------+\n");
    printf("dig_T1: %u\n", dev.calibration.dig_T1);
    printf("dig_T2: %i\n", dev.calibration.dig_T2);
    printf("dig_T3: %i\n", dev.calibration.dig_T3);

    printf("dig_P1: %u\n", dev.calibration.dig_P1);
    printf("dig_P2: %i\n", dev.calibration.dig_P2);
    printf("dig_P3: %i\n", dev.calibration.dig_P3);
    printf("dig_P4: %i\n", dev.calibration.dig_P4);
    printf("dig_P5: %i\n", dev.calibration.dig_P5);
    printf("dig_P6: %i\n", dev.calibration.dig_P6);
    printf("dig_P7: %i\n", dev.calibration.dig_P7);
    printf("dig_P8: %i\n", dev.calibration.dig_P8);
    printf("dig_P9: %i\n", dev.calibration.dig_P9);

#if defined(MODULE_BME280)
    printf("dig_H1: %u\n", dev.calibration.dig_H1);
    printf("dig_H2: %i\n", dev.calibration.dig_H2);
    printf("dig_H3: %i\n", dev.calibration.dig_H3);
    printf("dig_H4: %i\n", dev.calibration.dig_H4);
    printf("dig_H5: %i\n", dev.calibration.dig_H5);
    printf("dig_H6: %i\n", dev.calibration.dig_H6);
#endif

    printf("\n+--------Starting Measurements--------+\n");

	
	uint32_t startpressure =  Middle(&dev, MAINLOOP_DELAY, 10); 
	printf("Startwert: %d\n", startpressure);
	
    while (1) {
        int16_t temperature;
        uint32_t pressure;
#if defined(MODULE_BME280)
        uint16_t humidity;
#endif

        /* Get temperature in centi degrees Celsius */
        temperature = bmx280_read_temperature(&dev);
		
		pressure = Middle(&dev, MAINLOOP_DELAY, 10);
		int PDiff = startpressure - pressure;  
		int high_mm = (PDiff * MM_PER_PASCAL)/10;  
		
		//_____________
		
#if defined(MODULE_BME280)
        /* Get pressure in %rH */
        humidity = bme280_read_humidity(&dev);
#endif

        printf("Temperature [°C]: %d.%d\n"
               "Pressure [Pa]: %lu\n"
               "Höhe [mm]: %d\n"
#if defined(MODULE_BME280)
               "Humidity [%%rH]: %u.%02u\n"
#endif
               "\n+-------------------------------------+\n",
               temperature / 100, abs(temperature % 100) / 10,
#if defined(MODULE_BME280)
               (unsigned long)pressure,
               high_mm,                                                           //  ------------------------
               (unsigned int)(humidity / 100), (unsigned int)(humidity % 100)
#else
               (unsigned long)pressure
#endif
               );

        xtimer_usleep(MAINLOOP_DELAY);
    }

    return 0;
}
