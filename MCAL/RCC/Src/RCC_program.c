/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M4                                       **
 **                  MCU    : F401CC                                          **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#include "ErrTypes.h"
#include "STD_MACROS.h"
#include "STM32F401xx.h"

#include <stdint.h>

#include "../Inc/RCC_interface.h"
#include "../Inc/RCC_config.h"

#include "../Inc/RCC_private.h"

static uint8_t RCC_u8State = IDLE;

  /*=================================================================================================================*/
  /**
 * @brief   Configure the state of a specific clock source (HSI, HSE, or PLL)
 *
  * This function allows enabling or disabling the specified clock source with
  * proper timeout handling and state management.
  *
  * @param   Copy_u8CLK      The clock source to configure:
  *                          - HSI_CLK: Internal 16MHz RC oscillator
  *                          - HSE_CLK: External crystal/clock
  *                          - PLL_CLK: Phase-Locked Loop clock
  * @param   Copy_u8Status   The desired state of the clock:
  *                          - CLK_ON: Enable the clock
  *                          - CLK_OFF: Disable the clock
  *
  * @return  ErrorState_t    Function execution status:
  *                          - OK: Operation completed successfully
  *                          - BUSY_STATE: RCC is busy with another operation
  *                          - TIMEOUT_STATE: Operation timed out
  *                          - NOK: Invalid parameters
  */
ErrorState_t RCC_enumSetClkSts(uint8_t Copy_u8CLK, uint8_t Copy_u8Status)
{
  ErrorState_t Local_ErrorState = OK;
  uint32_t Local_u32TimeoutCounter = 0;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    //for HSI
    if (Copy_u8CLK == HSI_CLK)
    {

      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC->CR, 0);

        while(READ_BIT(MRCC->CR, 1) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }

      }
      else if (Copy_u8Status == CLK_OFF)
      {
        CLR_BIT(MRCC->CR, 0);
        while(READ_BIT(MRCC->CR, 1) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }

      }
      else
      {
        Local_ErrorState = NOK;
      }
    }
 
     //For HSE
    else if (Copy_u8CLK == HSE_CLK)
    {
      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC->CR, 18);
        SET_BIT(MRCC->CR, 16);
        while(READ_BIT(MRCC->CR, 17) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }

      else if (Copy_u8Status == CLK_OFF)
      {
        CLR_BIT(MRCC->CR, 16);
        while(READ_BIT(MRCC->CR, 17) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }
    }

    //For PLL
    else if (Copy_u8CLK == PLL_CLK)
    {
      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC->CR, 24);
        while(READ_BIT(MRCC->CR, 25) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }

      else if (Copy_u8Status == CLK_OFF)
      {
        CLR_BIT(MRCC ->CR, 24);
        while(READ_BIT(MRCC->CR, 25) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }

    }
    else
    {

    }

    RCC_u8State = IDLE;

  }
  else
  {
    Local_ErrorState = BUSY_STATE;
  }

  return Local_ErrorState;
}

/*=================================================================================================================*/
/**
  * @brief   Set the system clock source
  *
  * This function configures the system clock source (HSI, HSE, or PLL) and
  * updates the system clock configuration register.
  *
  * @param   Copy_u8CLK  The clock source to set as system clock:
  *                      - HSI_CLK: Internal 16MHz RC oscillator
  *                      - HSE_CLK: External crystal/clock
  *                      - PLL_CLK: Phase-Locked Loop clock
  *
  * @return  ErrorState_t    Function execution status:
  *                          - OK: Operation completed successfully
  *                          - BUSY_STATE: RCC is busy with another operation
  *                          - TIMEOUT_STATE: Operation timed out
  *                          - NOK: Invalid parameters
  */
ErrorState_t RCC_enumSetSysClk(uint8_t Copy_u8CLK)
{
  ErrorState_t Local_ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8CLK >= 0 && Copy_u8CLK < 3)
    {
      MRCC->CFGR &= ~(SYS_CLK_MASK);
      MRCC->CFGR |= Copy_u8CLK;
    }
    else
    {
      Local_ErrorState = NOK;
    }

    RCC_u8State = IDLE;
  }

  else
  {
    Local_ErrorState = BUSY_STATE;
  }

  return Local_ErrorState;
}


/*=================================================================================================================*/

ErrorState_t RCC_enumPLLConfig(const PLL_CONFIG_t *PLL_Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if ((PLL_Config->Copy_u8PLLSource == PLL_HSI || PLL_Config->Copy_u8PLLSource == PLL_HSE ) &&
        (PLL_Config->Copy_u8PLLMDiv >= 2 || PLL_Config->Copy_u8PLLMDiv <= 63) &&
        (PLL_Config->Copy_u8PLLNMul >= 50 || PLL_Config->Copy_u8PLLNMul <= 432) &&
        (PLL_Config->Copy_u8PLLPDiv >= 2 && PLL_Config->Copy_u8PLLPDiv <= 8) &&
        (PLL_Config->Copy_u8PLLQDiv >= 2 || PLL_Config->Copy_u8PLLQDiv <= 15 ))
    {
      if (PLL_Config->Copy_u8PLLSource == PLL_HSI)
      {
        MRCC->PLLCFGR &= ~(1 << 22);
      }
      else if (PLL_Config->Copy_u8PLLSource == PLL_HSE)
      {
        MRCC->PLLCFGR |= (1 << 22);
      }

      MRCC->PLLCFGR &= ~(PLLM_CONFIG_MASK);
      MRCC->PLLCFGR |= PLL_Config->Copy_u8PLLMDiv;

      MRCC->PLLCFGR &= ~(PLLN_CONFIG_MASK);
      MRCC->PLLCFGR |= (PLL_Config->Copy_u8PLLNMul << 6);

      MRCC->PLLCFGR &= ~(PLLP_CONFIG_MASK);
      MRCC->PLLCFGR |= ((PLL_Config->Copy_u8PLLPDiv / 2) - 1) << 16;

      MRCC->PLLCFGR &= ~(PLLQ_CONFIG_MASK);
      MRCC->PLLCFGR |= (PLL_Config->Copy_u8PLLQDiv << 24);

      RCC_u8State = IDLE;
    }
    return Local_ErrorState;
  }
}

/*=================================================================================================================*/
ErrorState_t RCC_enumBusConfig(BUS_CONFIG_t *Bus_Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if ((Bus_Config->Copy_u8AHBDiv >= AHB_NOT_DIV || Bus_Config->Copy_u8AHBDiv <= AHB_DIV_512)&&
        (Bus_Config->Copy_u8APB1Div>= Apb_NOT_DIV || Bus_Config->Copy_u8APB1Div<= APB_DIV_16)&&
        (Bus_Config->Copy_u8APB2Div>= Apb_NOT_DIV || Bus_Config->Copy_u8APB2Div<= APB_DIV_16))
    {
      MRCC->CFGR &= ~(AHB_DIV_MASK);
      MRCC->CFGR |= (Bus_Config->Copy_u8AHBDiv << 4);
      MRCC->CFGR &= ~(APB1_DIV_MASK);
      MRCC->CFGR |= (Bus_Config->Copy_u8APB1Div << 10);
      
      MRCC->CFGR &= ~(APB2_DIV_MASK);
      MRCC->CFGR |= (Bus_Config->Copy_u8APB2Div << 13);
    }
    else
    {
      Local_ErrorState = NOK;
    }

    RCC_u8State = IDLE;
  }
  else
  {
    Local_ErrorState = BUSY_STATE;
  }

  return Local_ErrorState;
}


/*=================================================================================================================*/

//  /**
//   * @brief   Configure the AHB bus division factor
//   *
//   * This function configures the AHB bus division factor based on the provided
//   * division value. It updates the AHB bus configuration register.
//   *
//   * @param   Copy_u8AHPDiv   The division factor for the AHB bus:
//   *                          - AHB_NOT_DIV: AHB bus not divided
//   *                          - AHB_DIV_2: AHB bus divided by 2
//   *                          - AHB_DIV_4: AHB bus divided by 4
//   *                          - AHB_DIV_8: AHB bus divided by 8
//   *                          - AHB_DIV_16: AHB bus divided by 16
//   *                          - AHB_DIV_64: AHB bus divided by 64
//   *                          - AHB_DIV_128: AHB bus divided by 128
//   *                          - AHB_DIV_256: AHB bus divided by 256
//   *                          - AHB_DIV_512: AHB bus divided by 512
//   *
//   * @return  ErrorState_t    Function execution status:
//   *                          - OK: Operation completed successfully
//   *                          - BUSY_STATE: RCC is busy with another operation
//   *                          - NOK: Invalid parameters
//   */
//  ErrorState_t RCC_enumAHBConfig(uint8_t Copy_u8AHPDiv)
//  {
//    ErrorState_t Local_ErrorState = OK;

//    if (RCC_u8State == IDLE)
//    {
//      RCC_u8State = BUSY;

//      if (Copy_u8AHPDiv >= AHB_NOT_DIV || Copy_u8AHPDiv <= AHB_DIV_512)
//      {
//        MRCC->CFGR &= (~(0xF << 4));
//        MRCC->CFGR |= (Copy_u8AHPDiv << 4);
//      }
//      else
//      {
//        Local_ErrorState = NOK;
//      }

//      RCC_u8State = IDLE;
//    }
//    else
//    {
//      Local_ErrorState = BUSY_STATE;
//    }

//    return Local_ErrorState;
//  }


//  /*=================================================================================================================*/
//  /**
//   * @brief   Configure the APB1 bus division factor
//   *
//   * This function configures the APB1 bus division factor based on the provided
//   * division value. It updates the APB1 bus configuration register.
//   *
//   * @param   Copy_u8APB1Div  The division factor for the APB1 bus:
//   *                          - APB_NOT_DIV: APB1 bus not divided
//   *                          - APB_DIV_2: APB1 bus divided by 2
//   *                          - APB_DIV_4: APB1 bus divided by 4
//   *                          - APB_DIV_8: APB1 bus divided by 8
//   *                          - APB_DIV_16: APB1 bus divided by 16
//   *
//   * @return  ErrorState_t    Function execution status:
//   *                          - OK: Operation completed successfully
//   *                          - BUSY_STATE: RCC is busy with another operation
//   *                          - NOK: Invalid parameters
//   */
//  ErrorState_t RCC_enumAPB1Config(uint8_t Copy_u8APB1Div)
//  {
//    ErrorState_t Local_ErrorState = OK;

//    if (RCC_u8State == IDLE)
//    {
//      RCC_u8State = BUSY;

//      if (Copy_u8APB1Div >= APB_NOT_DIV || Copy_u8APB1Div <= APB_DIV_16)
//      {
//        MRCC->CFGR &= (~(0x7 << 8));
//        MRCC->CFGR |= (Copy_u8APB1Div << 8);
//      }
//      else
//      {
//        Local_ErrorState = NOK;
//      }

//      RCC_u8State = IDLE;
//    }
//    else
//    {
//      Local_ErrorState = BUSY_STATE;
//    }

//    return Local_ErrorState;
//  }


//  /*=================================================================================================================*/
//  ErrorState_t RCC_enumAPB2Config(uint8_t Copy_u8APB2Div)
//  {
//    ErrorState_t Local_ErrorState = OK;

//    if (RCC_u8State == IDLE)
//    {
//      RCC_u8State = BUSY;

//      if (Copy_u8APB2Div >= APB_NOT_DIV || Copy_u8APB2Div <= APB_DIV_16)
//      {
//        MRCC->CFGR &= (~(0x7 << 11));
//        MRCC->CFGR |= (Copy_u8APB2Div << 11);
//      }
//      else
//      {
//        Local_ErrorState = NOK;
//      }
//      RCC_u8State = IDLE;
//    }
//    else
//    {
//      Local_ErrorState = BUSY_STATE;
//    }

//    return Local_ErrorState;
//  }


/*=================================================================================================================*/
ErrorState_t RCC_enumAHPPerSts(uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status)
{
  ErrorState_t Local_ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8Status == PER_ON)
    {
      SET_BIT(MRCC->AHB1ENR, Copy_u8AHPPer);
    }
    else if (Copy_u8Status == PER_OFF)
    {
      CLR_BIT(MRCC->AHB1ENR, Copy_u8AHPPer);
    }
    else
    {

    }

    RCC_u8State = IDLE;
  }
  else
  {
    Local_ErrorState = BUSY_STATE;
  }

  return Local_ErrorState;
}

/*=================================================================================================================*/
ErrorState_t RCC_enumABPPerSts(uint8_t Copy_u8Bus, uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status)
{
  ErrorState_t Local_ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;
    switch(Copy_u8Bus)
    {
    case APB1:
      if (Copy_u8Status == PER_ON)
      {
        SET_BIT(MRCC->APB1ENR, Copy_u8AHPPer);
      }
      else if (Copy_u8Status == PER_OFF)
      {
        CLR_BIT(MRCC->APB1ENR, Copy_u8AHPPer);
      }
      else
      {

      }
      break;
    case APB2:
      if (Copy_u8Status == PER_ON)
      {
        SET_BIT(MRCC->APB2ENR, Copy_u8AHPPer);
      }
      else if (Copy_u8Status == PER_OFF)
      {
        CLR_BIT(MRCC->APB2ENR, Copy_u8AHPPer);
      }
      else
      {

      }
      break;

    default:
      break;
    }


    RCC_u8State = IDLE;
  }
  else
  {
    Local_ErrorState = BUSY_STATE;
  }

  return Local_ErrorState;
}
