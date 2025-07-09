/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : GPIO                                            **
 **                                                                           **
 **===========================================================================**
 */

#include <stdint.h>
#include "STM32F103xx.h"
#include "ErrTypes.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/* Array of GPIO port base addresses */
static GPIO_REGDEF_t *const GPIO_Ports[GPIO_PORT_COUNT] = {
    MGPIOA,
    MGPIOB,
    MGPIOC,
    MGPIOD,
    MGPIOE};

/**
 * @fn     GPIO_enumPinInit
 * @brief  Initializes GPIO pin configuration
 * @param  PinConfig[in]: Pointer to pin configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumPinInit(const GPIO_PinConfig_t *PinConfig)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate input parameters */
  if (PinConfig == NULL || PinConfig->Port >= GPIO_PORT_COUNT ||
      PinConfig->PinNum >= GPIO_PIN_COUNT)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Get the appropriate configuration register (CRL or CRH) */
    volatile uint32_t *ConfigReg = (PinConfig->PinNum <= GPIO_CRL_MAX_PIN) ? &(GPIO_Ports[PinConfig->Port]->CRL) : &(GPIO_Ports[PinConfig->Port]->CRH);

    uint8_t PinPosition = (PinConfig->PinNum <= GPIO_CRL_MAX_PIN) ? (PinConfig->PinNum * GPIO_CRL_SHIFT) : ((PinConfig->PinNum - GPIO_CRH_MIN_PIN) * GPIO_CRH_SHIFT);

    /* Clear the current configuration */
    *ConfigReg &= ~(GPIO_MODE_CNF_MASK << PinPosition);

    /* Set the new configuration */
    *ConfigReg |= (PinConfig->Mode << PinPosition);

    /* Handle pull-up/pull-down for input mode with pull-up/pull-down */
    if (PinConfig->Mode == GPIO_INPUT_PULL_UP_DOWN)
    {
      if (PinConfig->Pull == GPIO_PULL_UP)
      {
        GPIO_Ports[PinConfig->Port]->ODR |= (1U << PinConfig->PinNum);
      }
      else
      {
        GPIO_Ports[PinConfig->Port]->ODR &= ~(1U << PinConfig->PinNum);
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumSetPinValue
 * @brief  Set GPIO pin value (High/Low)
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @param  PinVal: Pin value (PIN_HIGH or PIN_LOW)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumSetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, GPIO_PinValue_t PinVal)
{
  ErrorState_t Local_ErrorState = OK;

  if (Port >= GPIO_PORT_COUNT || PinNum >= GPIO_PIN_COUNT)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    if (PinVal == GPIO_PIN_HIGH)
    {
      /* Use BSRR to set the pin */
      GPIO_Ports[Port]->BSRR = (1U << PinNum);
    }
    else
    {
      /* Use BRR to reset the pin */
      GPIO_Ports[Port]->BRR = (1U << PinNum);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumGetPinValue
 * @brief  Get GPIO pin value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @param  PinVal[out]: Pointer to store pin value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumGetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, GPIO_PinValue_t *PinVal)
{
  ErrorState_t Local_ErrorState = OK;

  if (Port >= GPIO_PORT_COUNT || PinNum >= GPIO_PIN_COUNT || PinVal == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Read the input data register */
    *PinVal = (GPIO_Ports[Port]->IDR & (1U << PinNum)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumTogglePinValue
 * @brief  Toggle GPIO pin value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  PinNum: Pin number (PIN0 to PIN15)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumTogglePinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum)
{
  ErrorState_t Local_ErrorState = OK;

  if (Port >= GPIO_PORT_COUNT || PinNum >= GPIO_PIN_COUNT)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Toggle the ODR bit */
    GPIO_Ports[Port]->ODR ^= (1U << PinNum);
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumSetPortValue
 * @brief  Set entire GPIO port value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  Value: 16-bit value to write to port
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumSetPortValue(GPIO_Port_t Port, uint16_t Value)
{
  ErrorState_t Local_ErrorState = OK;

  if (Port >= GPIO_PORT_COUNT)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_Ports[Port]->ODR = Value;
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumGetPortValue
 * @brief  Get entire GPIO port value
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  Value[out]: Pointer to store 16-bit port value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumGetPortValue(GPIO_Port_t Port, uint16_t *Value)
{
  ErrorState_t Local_ErrorState = OK;

  if (Port >= GPIO_PORT_COUNT || Value == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    *Value = (uint16_t)GPIO_Ports[Port]->IDR;
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumWrite8Bits
 * @brief  Write 8 bits to consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Value: 8-bit value to write
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumWrite8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t Value)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN8)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    /* Write each bit to corresponding pin */
    for (Pin = 0; Pin < 8; Pin++)
    {
      if (Value & (1 << Pin))
      {
        GPIO_Ports[Port]->BSRR = (1U << (StartPin + Pin));
      }
      else
      {
        GPIO_Ports[Port]->BRR = (1U << (StartPin + Pin));
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumRead8Bits
 * @brief  Read 8 bits from consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Value[out]: Pointer to store 8-bit value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumRead8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t *Value)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN8 || Value == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    *Value = 0;
    /* Read each pin and construct the byte */
    for (Pin = 0; Pin < 8; Pin++)
    {
      if (GPIO_Ports[Port]->IDR & (1U << (StartPin + Pin)))
      {
        *Value |= (1 << Pin);
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumInit8Bits
 * @brief  Initialize 8 consecutive GPIO pins with the same configuration
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN8)
 * @param  Mode: GPIO mode and configuration for all 8 pins
 * @param  Pull: Pull-up/Pull-down configuration (only used with INPUT_PULL_UP_DOWN)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumInit8Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, GPIO_Mode_t Mode, GPIO_PullType_t Pull)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN8)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    GPIO_PinConfig_t PinConfig;

    /* Initialize configuration structure */
    PinConfig.Port = Port;
    PinConfig.Mode = Mode;
    PinConfig.Pull = Pull;

    /* Configure each pin */
    for (Pin = 0; Pin < 8; Pin++)
    {
      PinConfig.PinNum = StartPin + Pin;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
      if (Local_ErrorState != OK)
      {
        break;
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumWrite4Bits
 * @brief  Write 4 bits to consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Value: 4-bit value to write (only lower 4 bits are used)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumWrite4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t Value)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN12)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    /* Write each bit to corresponding pin */
    for (Pin = 0; Pin < 4; Pin++)
    {
      if (Value & (1 << Pin))
      {
        GPIO_Ports[Port]->BSRR = (1U << (StartPin + Pin));
      }
      else
      {
        GPIO_Ports[Port]->BRR = (1U << (StartPin + Pin));
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumRead4Bits
 * @brief  Read 4 bits from consecutive GPIO pins
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Value[out]: Pointer to store 4-bit value (in lower 4 bits)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumRead4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, uint8_t *Value)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN12 || Value == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    *Value = 0;
    /* Read each pin and construct the nibble */
    for (Pin = 0; Pin < 4; Pin++)
    {
      if (GPIO_Ports[Port]->IDR & (1U << (StartPin + Pin)))
      {
        *Value |= (1 << Pin);
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     GPIO_enumInit4Bits
 * @brief  Initialize 4 consecutive GPIO pins with the same configuration
 * @param  Port: GPIO port index (PORTA to PORTE)
 * @param  StartPin: Starting pin number (PIN0 to PIN12)
 * @param  Mode: GPIO mode and configuration for all 4 pins
 * @param  Pull: Pull-up/Pull-down configuration (only used with INPUT_PULL_UP_DOWN)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t GPIO_enumInit4Bits(GPIO_Port_t Port, GPIO_Pin_t StartPin, GPIO_Mode_t Mode, GPIO_PullType_t Pull)
{
  ErrorState_t Local_ErrorState = OK;

  /* Validate parameters */
  if (Port >= GPIO_PORT_COUNT || StartPin > GPIO_PIN12)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pin;
    GPIO_PinConfig_t PinConfig;

    /* Initialize configuration structure */
    PinConfig.Port = Port;
    PinConfig.Mode = Mode;
    PinConfig.Pull = Pull;

    /* Configure each pin */
    for (Pin = 0; Pin < 4; Pin++)
    {
      PinConfig.PinNum = StartPin + Pin;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
      if (Local_ErrorState != OK)
      {
        break;
      }
    }
  }

  return Local_ErrorState;
}