/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example application for demonstrating the RIOT network stack
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include "bmx280_params.h"
#include "bmx280.h"
#include "xtimer.h"

#include "shell.h"
#include "msg.h"
#include "BMP.h"

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int udp_cmd(int argc, char **argv);

static const shell_command_t shell_commands[] = {
    { "udp", "send data over UDP and listen on UDP ports", udp_cmd },
    { NULL, NULL, NULL }
};

//---------------------------------------------
bmx280_t dev;	

int Abfrage(void) 
{


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
   //   while (1) {
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
printf("Daten In Der Funktion:\n");
    //     xtimer_usleep(MAINLOOP_DELAY);
   //  }

// int dat = temperature;
printf("Daten In Der Funktion:\n");
/*
Data.temp = temperature;
Data.press = pressure;
Data.hum = humidity; 
*/
// return dat;
return 1;
}




//--------------------------------------------
int main(void)
{
    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
	int Antwort = Abfrage();
	printf("Antwort %d\n", Antwort);

    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("RIOT network stack example application");

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
