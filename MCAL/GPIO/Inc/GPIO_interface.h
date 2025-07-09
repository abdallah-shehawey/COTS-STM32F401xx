/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : GPIO                                            **
 **                                                                           **
 **===========================================================================**
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "STM32F103xx.h"
#include "ErrTypes.h"

/************************** Port Definitions **************************/
typedef enum
{
  GPIO_PORTA = 0, /* GPIO Port A */
  GPIO_PORTB,     /* GPIO Port B */
  GPIO_PORTC,     /* GPIO Port C */
  GPIO_PORTD,     /* GPIO Port D */
  GPIO_PORTE      /* GPIO Port E */
} GPIO_Port_t;

/************************** Pin Definitions **************************/
typedef enum
{
  GPIO_PIN0 = 0, /* GPIO Pin 0 */
  GPIO_PIN1,     /* GPIO Pin 1 */
  GPIO_PIN2,     /* GPIO Pin 2 */
  GPIO_PIN3,     /* GPIO Pin 3 */
  GPIO_PIN4,     /* GPIO Pin 4 */
  GPIO_PIN5,     /* GPIO Pin 5 */
  GPIO_PIN6,     /* GPIO Pin 6 */
  GPIO_PIN7,     /* GPIO Pin 7 */
  GPIO_PIN8,     /* GPIO Pin 8 */
  GPIO_PIN9,     /* GPIO Pin 9 */
  GPIO_PIN10,    /* GPIO Pin 10 */
  GPIO_PIN11,    /* GPIO Pin 11 */
  GPIO_PIN12,    /* GPIO Pin 12 */
  GPIO_PIN13,    /* GPIO Pin 13 */
  GPIO_PIN14,    /* GPIO Pin 14 */
  GPIO_PIN15     /* GPIO Pin 15 */
} GPIO_Pin_t;

/************************** Mode Definitions **************************/
typedef enum
{
  GPIO_INPUT_ANALOG = 0b0000,       /* Analog Input */
  GPIO_INPUT_FLOATING = 0b0100,     /* Floating Input */
  GPIO_INPUT_PULL_UP_DOWN = 0b1000, /* Input with Pull-up/Pull-down */

  GPIO_OUTPUT_PP_10MHZ = 0b0001,    /* Output Push-pull, 10MHz */
  GPIO_OUTPUT_OD_10MHZ = 0b0101,    /* Output Open-drain, 10MHz */
  GPIO_OUTPUT_AF_PP_10MHZ = 0b1001, /* Alternate Function Output Push-pull, 10MHz */
  GPIO_OUTPUT_AF_OD_10MHZ = 0b1101, /* Alternate Function Output Open-drain, 10MHz */

  GPIO_OUTPUT_PP_2MHZ = 0b0010,    /* Output Push-pull, 2MHz */
  GPIO_OUTPUT_OD_2MHZ = 0b0110,    /* Output Open-drain, 2MHz */
  GPIO_OUTPUT_AF_PP_2MHZ = 0b1010, /* Alternate Function Output Push-pull, 2MHz */
  GPIO_OUTPUT_AF_OD_2MHZ = 0b1110, /* Alternate Function Output Open-drain, 2MHz */

  GPIO_OUTPUT_PP_50MHZ = 0b0011,    /* Output Push-pull, 50MHz */
  GPIO_OUTPUT_OD_50MHZ = 0b0111,    /* Output Open-drain, 50MHz */
  GPIO_OUTPUT_AF_PP_50MHZ = 0b1011, /* Alternate Function Output Push-pull, 50MHz */
  GPIO_OUTPUT_AF_OD_50MHZ = 0b1111  /* Alternate Function Output Open-drain, 50MHz */
} GPIO_Mode_t;

/************************** Pin Value Definitions **************************/
typedef enum
{
  GPIO_PIN_LOW = 0, /* Pin Low Value */
  GPIO_PIN_HIGH     /* Pin High Value */
} GPIO_PinValue_t;

/************************** Pull Type Definitions **************************/
typedef enum
{
  GPIO_PULL_DOWN = 0, /* Pull-down */
  GPIO_PULL_UP        /* Pull-up */
} GPIO_PullType_t;

/************************** Pin Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port;     /* GPIO Port Selection */
  GPIO_Pin_t PinNum;    /* GPIO Pin Number */
  GPIO_Mode_t Mode;     /* GPIO Mode and Configuration */
  GPIO_PullType_t Pull; /* Pull-up/Pull-down (only used with INPUT_PULL_UP_DOWN) */
} GPIO_PinConfig_t;

/************************** Function Prototypes **************************/

/**
 * @fn     GPIO_enumPinInit
 * @brief  Initializes GPIO pin configuration
 * @param  PinConfig[in]: Pointer to pin configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumPinInit(const GPIO_PinConfig_t *PinConfig);

/**
 * @fn     GPIO_enumSetPinValue
 * @brief  Set GPIO pin value (High/Low)
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @param  PinVal: Pin value (PIN_HIGH or PIN_LOW)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumSetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, GPIO_PinValue_t PinVal);

/**
 * @fn     GPIO_enumGetPinValue
 * @brief  Get GPIO pin value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @param  PinVal[out]: Pointer to store pin value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumGetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, GPIO_PinValue_t *PinVal);

/**
 * @fn     GPIO_enumTogglePinValue
 * @brief  Toggle GPIO pin value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumTogglePinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum);

/**
 * @fn     GPIO_enumSetPortValue
 * @brief  Set entire GPIO port value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  Value: 16-bit value to write to port
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumSetPortValue(GPIO_Port_t Port, uint16_t Value);

/**
 * @fn     GPIO_enumGetPortValue
 * @brief  Get entire GPIO port value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  Value[out]: Pointer to store 16-bit port value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumGetPortValue(GPIO_Port_t Port, uint16_t *Value);

/************************** 8-Bit Access Functions **************************/

/**
 * @fn     GPIO_enumWrite8Bits
 * @brief  Write 8 bits to consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Value: 8-bit value to write
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumWrite8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t Value);

/**
 * @fn     GPIO_enumRead8Bits
 * @brief  Read 8 bits from consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Value[out]: Pointer to store 8-bit value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumRead8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t *Value);

/**
 * @fn     GPIO_enumInit8Bits
 * @brief  Initialize 8 consecutive GPIO pins with the same configuration
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Mode: GPIO mode and configuration for all 8 pins
 * @param  Pull: Pull-up/Pull-down configuration (only used with INPUT_PULL_UP_DOWN)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumInit8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, GPIO_Mode_t Mode, GPIO_PullType_t Pull);

/************************** 4-Bit Access Functions **************************/

/**
 * @fn     GPIO_enumWrite4Bits
 * @brief  Write 4 bits to consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Value: 4-bit value to write (only lower 4 bits are used)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumWrite4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t Value);

/**
 * @fn     GPIO_enumRead4Bits
 * @brief  Read 4 bits from consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Value[out]: Pointer to store 4-bit value (in lower 4 bits)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumRead4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t *Value);

/**
 * @fn     GPIO_enumInit4Bits
 * @brief  Initialize 4 consecutive GPIO pins with the same configuration
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Mode: GPIO mode and configuration for all 4 pins
 * @param  Pull: Pull-up/Pull-down configuration (only used with INPUT_PULL_UP_DOWN)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumInit4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, GPIO_Mode_t Mode, GPIO_PullType_t Pull);

#endif /* GPIO_INTERFACE_H_ */