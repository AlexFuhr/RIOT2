/*
 * Copyright (C) 2016 Kees Bakker, SODAQ
 *               2017 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_bmx280
 * @{
 *
 * @file
 * @brief       SAUL adoption for BMX280 sensors (BME280 and BMP280).
 *
 * @author      Kees Bakker <kees@sodaq.com>
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 *
 * @}
 */

#include "saul.h"

#include "bmx280.h"

static int read_temperature(const void *dev, phydat_t *res)
{
    res->val[0] = bmx280_read_temperature((const bmx280_t *)dev);
    res->unit = UNIT_TEMP_C;
    res->scale = -2;

    return 1;
}

#ifdef MODULE_BME280
static int read_pressure(const void *dev, phydat_t *res)
{
	bmx280_read_temperature(dev);
	res->val[0] = bmx280_read_pressure((const bmx280_t *)dev) - PAD_BASE_PRESSURE_PA;
	res->unit = UNIT_PAD;
    res->scale = 0;

    return 1;
}
#endif

/* static int read_pressure(const void *dev, phydat_t *res)
{
    res->val[0] = bmx280_read_pressure((const bmx280_t *)dev) / 100;
    res->unit = UNIT_PA;
    res->scale = 2;

    return 1;
} */

#ifdef MODULE_BME280
static int read_relative_humidity(const void *dev, phydat_t *res)
{
    res->val[0] = bme280_read_humidity((const bmx280_t *)dev);
    res->unit = UNIT_PERCENT;
    res->scale = -2;

    return 1;
}
#endif

const saul_driver_t bmx280_temperature_saul_driver = {
    .read = read_temperature,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};

const saul_driver_t bmx280_pressure_saul_driver = {
    .read = read_pressure,
    .write = saul_notsup,
    .type = SAUL_SENSE_PRESS,
};

#ifdef MODULE_BME280
const saul_driver_t bme280_relative_humidity_saul_driver = {
    .read = read_relative_humidity,
    .write = saul_notsup,
    .type = SAUL_SENSE_HUM,
};
#endif


#ifdef MODULE_BME280
const saul_driver_t bme280_pressure_saul_driver = {
    .read = read_pressure,
    .write = saul_notsup,
    .type = SAUL_SENSE_PRESS,
};
#endif
