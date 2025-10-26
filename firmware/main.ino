/*
 * =============================================
 * Mic Jammer Prototype
 * Author: Ardian Fikri Abdulah
 * Company: Optimasi AI
 * =============================================
 *
 * Deskripsi:
 * Program ini mengendalikan modul AD9833 untuk menghasilkan sinyal ultrasonik
 * (sekitar 25 kHz) yang diperkuat menggunakan amplifier TPA3116D2
 * dan dipancarkan melalui transduser.
 *
 * Komponen:
 * - Arduino Nano (ATmega328P)
 * - AD9833 Signal Generator
 * - TPA3116D2 Audio Amplifier
 * - IRF4115 MOSFET
 * - Ultrasonic Transducer
 */
/*
    microphone jammer
    - Arduino Nano version

    CONNECTION
    --------
    AD9833 PCB to Arduino Nano:
    VCC   --> 5V
    GND   --> GND
    FDATA --> D11 (MOSI)
    SCLK  --> D13 (SCK)
    FSYNC --> D10 (CS - bisa diubah ke pin digital lain, pastikan sesuai di kode)

    AD9833 PCB to TPA3116 AUDIO AMPLIFIER
    AOUT  --> LEFT AUDIO IN + RIGHT AUDIO IN
    AGND  --> AUDIO GND

    REMEMBER TO CONNECT AD9833 TO 5V AND GND PINS OF ARDUINO NANO
    TPA3116 HAS TO BE CONNECTED TO 12V AND GND
*/

#include <Arduino.h>
#include <SPI.h> // Include the SPI library for Arduino Nano

/**
 * SPI pins - definition for Arduino Nano
 */
// We will use standard SPI pins for Arduino Nano (D11-MOSI, D13-SCK)
// FSYNC (Chip Select) can be any digital pin. D10 is often used.
#define FSYNC_PIN 10 // Digital pin 10 for FSYNC/CS

/** \name AD9833 waveform output modes
 * Parameters of \ref ad9833_set_mode()
 * @{
 */
#define AD_OFF      0
#define AD_TRIANGLE 1
#define AD_SQUARE   2
#define AD_SINE     3
/**@}*/

/** \name AD9833 command register bits
 * @{
 */

#define AD_B28     13
#define AD_HLB     12
#define AD_FSELECT 11
#define AD_PSELECT 10
#define AD_RESET   8
#define AD_SLEEP1  7
#define AD_SLEEP12 6
#define AD_OPBITEN 5
#define AD_DIV2    3
#define AD_MODE    1

/** @}*/

/** \name AD9833 register addresses
 * @{
 */
#define AD_FREQ0  (1<<14)
#define AD_FREQ1  (1<<15)
#define AD_PHASE0 (3<<14)
#define AD_PHASE1 ((3<<14)|(1<<13))

/** @}*/

/** \name AD9833 calculation macros
 * @{ */
#define AD_F_MCLK 25000000 ///<Clock speed of the ad9833 reference clock
#define AD_2POW28 268435456 ///<used in calculating output freq

/** Macro that calculates the value for a ad9833 frequency register from a frequency */
#define AD_FREQ_CALC(freq) (uint32_t)(((double)AD_2POW28/(double)AD_F_MCLK*freq))

/** Macro that calculates value for Timer1 output compare from a frequency*/
// #define AD_MOD_FREQ_CALC(freq) (F_CPU/(64*(uint32_t)freq)) // Not used in this context

/** Macro that calculates the value for a ad9833 phase register from a phase in degrees */
#define AD_PHASE_CALC(phase_deg) (uint16_t)((512*phase_deg)/45)
/** @} */

/** Struct that holds all the configuration it's initialized as a global variable
 * in the ad9833.c file */
typedef struct {
    float    freq[2]; ///<Holds the frequencies of
    float    phase[2];
    float    mod_freq; // Not used
    uint8_t  freq_out;
    uint8_t  phase_out;
    uint8_t  mode;
    uint16_t command_reg;
} ad9833_settings_t;


ad9833_settings_t ad_settings; ///<This is used to store all settings.


// randomized infrasound 400 values to swipe between 24kHz - 26kHz
const uint8_t  randomized[] PROGMEM =
  {
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17,16,15,
14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
16,17,18,19,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,
4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17,16,15,14,13,
12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
18,19,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,
6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17,16,15,14,13,12,
11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
18,19,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,
6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17,16,15,14,13,12,
11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
18,19,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,
6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17,16,15,14,13,12,
11,10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
18,19,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,2,3,4,
5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
};


// ***********************************
// ******* SPI SPECIFIC ROUTINES
// ***********************************

/**
 * init
 *
 * SPI initialization
 */
void spi_init()
{
  // Set FSYNC pin as output
  pinMode(FSYNC_PIN, OUTPUT);
  digitalWrite(FSYNC_PIN, HIGH); // FSYNC/CS is active low, so start high

  // Initialize SPI: Master, MSB first, Clock Polarity (CPOL) 1, Clock Phase (CPHA) 1
  // AD9833 uses SPI Mode 2 or 3. Here we use Mode 2 (CPOL=1, CPHA=1)
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE2);
  // Set clock speed. AD9833 can handle up to 40MHz, Arduino Nano is 16MHz max.
  // SPI_CLOCK_DIV2 (8MHz) or SPI_CLOCK_DIV4 (4MHz) are good starting points.
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}

/**
 *
 * Send uint8_t via SPI
 *
 * 'value'  Value to be sent
 *
 * Return:
 *  Response received from SPI slave
 */
uint8_t spi_send(uint8_t value)
{
    return SPI.transfer(value);
}


// ----------------------------------------------------------------
// AD8933 programmable signal generator specific routines
// ----------------------------------------------------------------

/**
 * a wrapper function for sending 16-bit SPI packets.
 * \param packet 16-bit value to be sent over SPI.
 */
static inline void ad9833_send(uint16_t packet)
{
   digitalWrite(FSYNC_PIN, LOW);   // Set FSYNC/CS LOW to select the AD9833

   //delayMicroseconds(2); // Some delay may be needed, but usually not with SPI library

  // Transmit 16 bits 8 bits at a time
  spi_send((uint8_t)(packet>>8));
  spi_send((uint8_t)packet);

  digitalWrite(FSYNC_PIN, HIGH);   // Set FSYNC/CS HIGH to deselect the AD9833
}



/**
 * Initializes the AD9833 and the relevant variables.
 */

void ad9833_init(void)
    {
    // RESET the AD9833 first
    ad9833_send((1<<AD_RESET));
    // Wait for at least 6 MCLK cycles for the reset to complete (6 * 1/25MHz = 240ns)
    // A small delay is sufficient.
    delayMicroseconds(10);

    // set half awake state (SLEEP12, AD_RESET cleared later)
    ad_settings.command_reg = (1<<AD_B28) | (1<<AD_SLEEP12); // Always set B28 for 28-bit freq registers
    ad9833_send(ad_settings.command_reg);


    //set some nice default values
    ad9833_set_frequency(0, 0);
    ad9833_set_frequency(1, 0);
    ad9833_set_phase(0, 0);
    ad9833_set_phase(1, 0);
    ad9833_set_freq_out(0);
    ad9833_set_phase_out(0);

}


/**
 * Sets the ad9833 output waveform to the one given as a parameter.
 * \param mode possible values:
 *      - AD_OFF
 *      - AD_TRIANGLE
 *      - AD_SQUARE
 *      - AD_SINE
 */
void ad9833_set_mode(uint8_t mode){
    ad_settings.mode = mode;
    // Clear previous mode related bits
    ad_settings.command_reg &= ~((1<<AD_OPBITEN) | (1<<AD_MODE) | (1<<AD_DIV2) | (1<<AD_SLEEP12) | (1<<AD_SLEEP1));
    ad_settings.command_reg |= (1<<AD_B28); // Ensure B28 is always set

    switch (mode){
        case AD_OFF:
            ad_settings.command_reg |= (1<<AD_SLEEP12) | (1<<AD_SLEEP1);
            break;
        case AD_TRIANGLE:
            // AD_MODE (D1) set to 1, OPBITEN (D5) set to 0.
            ad_settings.command_reg |=  (1<<AD_MODE);
            break;
        case AD_SQUARE:
            // OPBITEN (D5) set to 1, AD_MODE (D1) set to 0, DIV2 (D3) set to 1
            ad_settings.command_reg |=  (1<<AD_OPBITEN) | (1<<AD_DIV2);
            break;
        case AD_SINE:
            // OPBITEN (D5) set to 0, AD_MODE (D1) set to 0
            break;
    }
    ad9833_send(ad_settings.command_reg);
}


/**
 * Selects which frequency register is used to generate the output.
 * Also used to select FSK.
 * \param freq_out possible values:
 *      - 0 = use frequency register 0
 *      - 1 = use frequency register 1
 *      - 2 = FSK (not fully implemented in this code)
 */
void    ad9833_set_freq_out(uint8_t freq_out){
    ad_settings.freq_out = freq_out;
    // Clear FSELECT bit
    ad_settings.command_reg &= ~(1<<AD_FSELECT);
    switch (freq_out){
        case 0:
            // FSELECT (D11) set to 0
            break;
        case 1:
            // FSELECT (D11) set to 1
            ad_settings.command_reg |= (1<<AD_FSELECT);
            break;
        case 2:
            // FSK - Not directly handled by just setting FSELECT, requires more.
            break;
    }
    ad9833_send(ad_settings.command_reg);
}


/**
 * sets the desired ad9833 internal phase register to a value that
 * produces the desired phase.
 *
 * \param reg the desired phase register to be manipulated, either 0 or 1
 * \param phase the desired phase in degrees (0-360)
 */
void ad9833_set_phase(uint8_t reg, double phase){
    uint16_t reg_addr;
    if (reg==1)
        reg_addr = AD_PHASE1;
    else
        reg_addr = AD_PHASE0;

    ad_settings.phase[reg] = phase;

    ad9833_send(reg_addr | AD_PHASE_CALC(ad_settings.phase[reg]));

}

/**
 * Selects which phase register is used to generate the output
 * Also used to select PSK
 * \param phase_out possible values:
 *  - 0 = use phase register 0
 *  - 1 = use phase register 1
 *  - 2 = PSK (not fully implemented in this code)
 */
void    ad9833_set_phase_out(uint8_t phase_out){
    ad_settings.phase_out = phase_out;
    // Clear PSELECT bit
    ad_settings.command_reg &= ~(1<<AD_PSELECT);
    switch (phase_out){
        case 0:
            // PSELECT (D10) set to 0
            break;
        case 1:
            // PSELECT (D10) set to 1
            ad_settings.command_reg |= (1<<AD_PSELECT);
            break;
        case 2:
            // PSK - Not directly handled by just setting PSELECT, requires more.
            break;
    }
    ad9833_send(ad_settings.command_reg);
}


/**
 * sets the desired ad9833 internal frequency register to a value that
 * produces the desired frequency.
 *
 * \param reg the desired frequency register to be manipulated, either 0 or 1
 * \param freq the desired frequency in Hz
 */
void ad9833_set_frequency(uint8_t reg, double freq){
    uint32_t freq_word = AD_FREQ_CALC(freq);
    uint16_t reg_addr;

    ad_settings.freq[reg] = freq;

    if (reg==1)
        reg_addr = AD_FREQ1;
    else
        reg_addr = AD_FREQ0;

    // Send the two 14-bit words
    // First, select the 28-bit update mode and current command_reg
    ad9833_send(ad_settings.command_reg | (1<<AD_B28)); // Ensure B28 is set to write 28-bit freq

    // Send lower 14 bits
    ad9833_send(reg_addr | (0x3FFF & (uint16_t)freq_word));
    // Send upper 14 bits
    ad9833_send(reg_addr | (0x3FFF & (uint16_t)(freq_word >> 14)));

    // After updating frequency, send the actual command_reg to exit the 28-bit write mode
    // and apply the frequency change.
    ad9833_send(ad_settings.command_reg);
}




// -----------------------------------------------------------------------
//      MAIN CODE OF THE JAMMER
// -----------------------------------------------------------------------


void setup()
  {
  //initializing SPI and AD9833 generator
  spi_init();

  delay(100);
  ad9833_init();
  delay(15);

  //set gen to SQUARE
  // you may also experiment with AD_SINE or AD_TRIANGLE for better effects
  // AD_SINE is almost not audible for humans
  ad9833_set_mode(AD_SQUARE);
  ad9833_set_frequency(0, 26000); // Start at 26kHz
}

void loop() {

  uint16_t i, sequence_idx;

          // generating RANDOM 5-25Hz INFRASOUND over 25kHZ ULTRASOUND CARRIER

           sequence_idx = 0;

           for(i=26000; i>24000; i=i - pgm_read_byte(randomized + sequence_idx), sequence_idx++)
                  {
                   // Ensure sequence_idx doesn't go out of bounds
                   if (sequence_idx >= sizeof(randomized)) sequence_idx = 0;
                   ad9833_set_frequency(0, (double)i );
                   // delay(1); // Small delay to make frequency sweep more distinct, if needed
                  };

           sequence_idx = 0;

           for(i=24000; i<26000; i=i + pgm_read_byte(randomized + sequence_idx), sequence_idx++ )
                  {
                   // Ensure sequence_idx doesn't go out of bounds
                   if (sequence_idx >= sizeof(randomized)) sequence_idx = 0;
                   ad9833_set_frequency(0, (double)i );
                   // delay(1); // Small delay to make frequency sweep more distinct, if needed
                  };
}