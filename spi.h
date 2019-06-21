/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
    
   This file is part of
   Embedded bootstraps : hal-uC
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/


/**
 * @file hal_uc_spi.h
 * @brief HAL for SPI interfaces
 *
 * This file is the hardware abstraction layer for uC SPI interfaces
 * 
 * @see spi_impl.h 
 * @see spi_impl.c
 */

#ifndef HAL_UC_SPI_H
#define HAL_UC_SPI_H

#include <platform/types.h>
#include "map.h"

#ifdef uC_INCLUDE_SPI_IFACE

/**
 * @name SPI API Setup and Reactor Functions
 */
/**@{*/ 

/**
 * Initialize SPI. Config parameters for the SPI are (currently) defined in UC_MAP.
 * @param intfnum Identifier of the SPI interface
 */
void spi_init(void);

void spi_reactor(void);

/**@}*/ 

/**
 * @name SPI Slave Selection API
 */
/**@{*/ 

typedef enum {
    SPI_SELECTOR_FUNC,
    SPI_SELECTOR_PIO,
}spi_slave_selector_type;

typedef struct SPI_SSFUNC_t{
    void (*const select) (void);
    void (*const deselect) (void);
}spi_ssfunc_t;

typedef struct SPI_SSPIO_t{
    const PORTSELECTOR_t port;
    const PINSELECTOR_t pin;
}spi_sspio_t;

typedef enum SPI_SCLK_CLKPOL_t{
    SPI_CLKPOL_AH,
    SPI_CLKPOL_AL
}spi_sclk_clkpol_t;

typedef enum SPI_SCLK_CLKPHA_t{
    SPI_CLKPHA_CHG_CAP,
    SPI_CLKPHA_CAP_CHG
}spi_sclk_clkpha_t;

typedef enum SPI_DATA_ENDIAN_t{
    SPI_DATA_MSBFIRST,
    SPI_DATA_LSBFIRST
}spi_data_endian_t;

typedef enum SPI_DATA_WIDTH_t{
    SPI_DATA_8BIT,
    SPI_DATA_7BIT
}spi_data_width_t;


typedef union SPI_SCLK_CONF_t{
    struct {
        spi_sclk_clkpha_t clkpha : 1;
        spi_sclk_clkpol_t clkpol : 1;
        spi_data_endian_t endian: 1;
        spi_data_width_t width: 1;
        uint8_t clkdivider : 4;
    };
    uint8_t asint;
}spi_sclk_conf;


typedef struct SPI_SLAVE_t{
    #if APP_SUPPORT_SPI_CTL
    const spi_sclk_conf sclk;
    #endif
    const spi_slave_selector_type sst;
    const union {
        const spi_ssfunc_t func;
        const spi_sspio_t pio;
    } ss;
}spi_slave_t;

void spi_init_slave(uint8_t intfnum, const spi_slave_t * slave);

void spi_select_slave(uint8_t intfnum, const spi_slave_t * slave);

void spi_deselect_slave(uint8_t intfnum, const spi_slave_t * slave);

/**@}*/

/**
 * @name SPI Transaction API
 */
/**@{*/ 

typedef struct SPI_TRANSACTION_t
{
    struct SPI_TRANSACTION_t * next;
    void (* callback) (struct SPI_TRANSACTION_t *);
    volatile uint8_t txlen; 
    volatile uint8_t rxlen;
    volatile uint8_t * txdata;
    volatile uint8_t * rxdata;
    const spi_slave_t * slave;
}spi_transaction_t;

static inline void spi_enqueue_transaction(uint8_t intfnum, spi_transaction_t * transaction);

static inline void spi_enqueue_pirority_transaction(uint8_t intfnum, spi_transaction_t * transaction);

static inline void spi_cancel_transaction(uint8_t intfnum, spi_transaction_t * transaction);

static inline uint8_t spi_queue_empty(uint8_t intfnum);

/**@}*/ 

/**
 * @name Hardware Debug-Only SPI API Functions
 */
/**@{*/ 

/**
 * @brief Send an recieve a single character over the specified SPI interface
 * @param byte The character to be sent
 * @param intfnum Identifier of the SPI interface
 * 
 * This function uses the simplest possible method to send a single 
 * byte of data and returns the character it gets in return at the same time. 
 * It should not use buffers, interrupts, etc.
 * 
 * @warning In a general application, this function would only be used 
 * in special circumstances and with extreme care. Using this alongside 
 * transactions will cause data loss. If you intend to use this interface, 
 * the peripheral initialization may need to be changed to not enable 
 * interrupts.
 * 
 * @return Character recieved
 */
static inline uint8_t spi_txrx_bare(uint8_t intfnum, uint8_t byte);

/**@}*/ 

#endif

// Set up the implentation
#include "uc/spi_impl.h"
#include "uc/spi_handlers.h"
#endif


