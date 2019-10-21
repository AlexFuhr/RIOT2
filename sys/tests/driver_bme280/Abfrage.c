#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "bmx280_params.h"
#include "bmx280.h"
#include "xtimer.h"
#include "BMP.h"

#define MAINLOOP_DELAY  (2 * 1000 * 1000u)      /* 2 seconds delay between printf's */


double Abfrage(void) 
{

//struct BMP_DATA Data;
	bmx280_t dev;	
	
 
    
printf("\n+--------Starting Measurements--------+\n");
   //  while (1) {
        int16_t temperature;
        uint32_t pressure;
#if defined(MODULE_BME280)
        uint16_t humidity;
#endif

        /* Get temperature in centi degrees Celsius */
        temperature = bmx280_read_temperature(&dev);

        /* Get pressure in Pa */
        pressure = bmx280_read_pressure(&dev);

#if defined(MODULE_BME280)
        /* Get pressure in %rH */
        humidity = bme280_read_humidity(&dev);
#endif

        printf("Temperature [°C]: %d.%d\n"
               "Pressure [Pa]: %lu\n"
#if defined(MODULE_BME280)
               "Humidity [%%rH]: %u.%02u\n"
#endif
               "\n+-------------------------------------+\n",
               temperature / 100, abs(temperature % 100) / 10,
#if defined(MODULE_BME280)
               (unsigned long)pressure,
               (unsigned int)(humidity / 100), (unsigned int)(humidity % 100)
#else
               (unsigned long)pressure
#endif
               );

        // xtimer_usleep(MAINLOOP_DELAY);
   // }

double dat = temperature;
/*
Data.temp = temperature;
Data.press = pressure;
Data.hum = humidity; 
*/
return dat;
}