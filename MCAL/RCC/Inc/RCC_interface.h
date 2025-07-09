/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<   RCC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M4                                       **
 **                  MCU    : F401CC                                          **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_RCC_INTERFACE_H_
#define MCAL_RCC_INTERFACE_H_

#include <stdint.h>
#include "ErrTypes.h"

/* Define Bus in uC*/
typedef enum
{
  AHB1,
  APB1,
  APB2,
} uC_BUS_t;

/* Define peripheral at AHB BUS */
typedef enum
{
  RCC_GPIOAEN,
  RCC_GPIOBEN,
  RCC_GPIOCEN,
  RCC_GPIODEN,
  RCC_GPIOEEN,
  RCC_GPIOHEN = 7,
  RCC_CRCEN   = 12,
  RCC_DMA1EN  = 21,
  RCC_DMA2EN,
} AHB1_BUS_t;

/* Define peripheral at APB2 BUS */
typedef enum
{
  TIM1EN,
  USART1EN = 4,
  USART6EN,
  ADC1EN = 8,
  SDIOEN = 11,
  SPI1EN,
  SPI4EN,
  SYSCFGEN,
  TIM9EN = 16,
  TIM10EN,
  TIM11EN,
} APB2_BUS_t;

/* Define peripheral at APB1 BUS */
typedef enum
{
  TIM2EN,
  TIM3EN,
  TIM4EN,
  TIM5EN,
  WWDGEN = 11,
  SPI2EN = 14,
  SPI3EN,
  USART2EN = 17,
  I2C1EN   = 21,
  I2C2EN,
  I2C3EN,
  PWREN    = 28,
} APB1_BUS_t;

/* Define Prescaller for USB OTG FS */
typedef enum
{
  USB_PRE_DIV_2 = 2,
  USB_PRE_DIV_3,
  USB_PRE_DIV_4,
  USB_PRE_DIV_5,
  USB_PRE_DIV_6,
  USB_PRE_DIV_7,
  USB_PRE_DIV_8,
  USB_PRE_DIV_9,
  USB_PRE_DIV_10,
  USB_PRE_DIV_11,
  USB_PRE_DIV_12,
  USB_PRE_DIV_13,
  USB_PRE_DIV_14,
  USB_PRE_DIV_15,
} USB_OTG_PRE_t;

/* Define Division Factor To AHP */
typedef enum
{
  AHB_NOT_DIV = 7    ,
  AHB_DIV_2          ,
  AHB_DIV_4          ,
  AHB_DIV_8          ,
  AHB_DIV_16         ,
  AHB_DIV_64         ,
  AHB_DIV_128        ,
  AHB_DIV_256        ,
  AHB_DIV_512        ,
}AHB_BUS_DIV_t;

/* Define Division Factor To APB */
typedef enum
{
  APB_NOT_DIV = 3    ,
  APB_DIV_2          ,
  APB_DIV_4          ,
  APB_DIV_8          ,
  APB_DIV_16         ,
}APB_BUS_DIV_t       ;

/* Define Clock Source To PLL */
typedef enum
{
  PLL_HSI            ,
  PLL_HSE            ,
}PLL_CLK_SRC         ;

/* Define type of CLK source */
typedef enum
{
  HSI_CLK            ,
  HSE_CLK            ,
  PLL_CLK            ,
}CLK_SRC_t           ;

/* Define ON or OFF for CLK */
typedef enum
{
  CLK_ON             ,
  CLK_OFF            ,
}CLK_EN_t            ;

/* Define ON or OFF for Peripheral */
typedef enum
{
  PER_ON             ,
  PER_OFF            ,
}PER_EN_t            ;

typedef struct
{
  uint8_t Copy_u8PLLSource;
  uint8_t Copy_u8PLLMDiv;
  uint8_t Copy_u8PLLNMul;
  uint8_t Copy_u8PLLPDiv;
  uint8_t Copy_u8PLLQDiv;
}PLL_CONFIG_t;


typedef struct
{
  AHB_BUS_DIV_t Copy_u8AHBDiv;
  APB_BUS_DIV_t Copy_u8APB1Div;
  APB_BUS_DIV_t Copy_u8APB2Div;
}BUS_CONFIG_t;

/* functions defination */
ErrorState_t RCC_enumSetClkSts(uint8_t Copy_u8CLK, uint8_t Copy_u8Status);
ErrorState_t RCC_enumSetSysClk  (uint8_t Copy_u8CLK);
ErrorState_t RCC_enumPLLConfig(PLL_CONFIG_t *PLL_Config);
ErrorState_t RCC_enumBusConfig(BUS_CONFIG_t *Bus_Config);
// ErrorState_t RCC_enumAHBConfig(uint8_t Copy_u8AHPDiv);
// ErrorState_t RCC_enumAPB1Config(uint8_t Copy_u8APB1Div);
// ErrorState_t RCC_enumAPB2Config(uint8_t Copy_u8APB2Div);
ErrorState_t RCC_enumAHPPerSts(uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status);
ErrorState_t RCC_enumABPPerSts(uint8_t Copy_u8Bus, uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status);

#endif /* MCAL_RCC_INTERFACE_H_ */
