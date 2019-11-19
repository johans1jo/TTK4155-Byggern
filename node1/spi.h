/**
 * @file
 * @brief A driver for SPI.
 */

 /**
  * @brief Sets MOSI, SCK and SS to output and all other Port B Pins as input.
  * Enables SPI, sets master SPI mode, and sets the clock rate fosc/16.
  */
void spi_master_init();

/**
 * @brief Sets MISO to output and enables SPI.
 */
void spi_slave_init();

/**
 * @brief Writes data by writing cDato to the SPI Data Register (SPDR),
 * and transmits the data until the SPI interrupt Flag in the SPI Status Register
 * is set upon completion of the transmission.
 */
void spi_write(char cData);

/**
 * @brief Reads data by writing a dummy byte to the
 * Writes data by writing cDato to the SPI Data Register (SPDR), waiting
 * until completion of the transmission and reads the data in the SPDR.
 */
uint8_t spi_read();

/**
 * @brief Sets the Slave Select Pin.
 */
void spi_set_ss();

/**
 * @brief Clears the Slave Select Pin.
 */
void spi_clear_ss();
