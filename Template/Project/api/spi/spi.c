//
// Created by joey on 2024-06-18.
//

#include "spi.h"

/* SPI instance. */
static const nrf_drv_spi_t SPI1 = NRF_DRV_SPI_INSTANCE(1); 

static volatile bool spi_xfer_done = false;

void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
    spi_xfer_done = true;
}

void initSPI(void)
{
		nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
	
//		spi_config.ss_pin    = 28;	//SPI Sensor CS Pin
    spi_config.miso_pin  = 13;		//comoPin_AD7171_DOUT 13, nRF52_DK Board Pin_MISO 28
//    spi_config.mosi_pin  = 29;		//nRF52_DK Board Pin_MOSI
    spi_config.sck_pin   = 12;		//comoPin_AD7171_SCLK 12, nRF52_DK Board Pin_SCLK 26
		spi_config.frequency = NRF_DRV_SPI_FREQ_1M;
		spi_config.mode      = NRF_DRV_SPI_MODE_0;
		spi_config.irq_priority = APP_IRQ_PRIORITY_HIGH;
    APP_ERROR_CHECK(nrf_drv_spi_init(&SPI1, &spi_config, NULL, NULL));
}

void writeReadSPI(void* txData, size_t txLength, void* rxData, size_t rxLength)
{
    spi_xfer_done = false;
	
		APP_ERROR_CHECK(nrf_drv_spi_transfer(&SPI1, txData, txLength, NULL, 0));
	
//		while (!spi_xfer_done)
//		{
//		}

	  APP_ERROR_CHECK(nrf_drv_spi_transfer(&SPI1, NULL, 0, rxData, rxLength));
		
//		while (!spi_xfer_done)
//    {
//    }
	
}

void writeSPI(void* txData, size_t txLength)
{
    spi_xfer_done = false;

    APP_ERROR_CHECK(nrf_drv_spi_transfer(&SPI1, txData, txLength, NULL, 0));
    
//		while (!spi_xfer_done)
//    {
//    }
}

void readSPI(void* rxData, size_t rxLength)
{
    spi_xfer_done = false;

    APP_ERROR_CHECK(nrf_drv_spi_transfer(&SPI1, NULL, 0, rxData, rxLength));
   
//	 while (!spi_xfer_done)
//    {
//    }
}
