/**
 *******************************************************************************
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    STM32F103xx.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : LIB                                             **
 **                  CPU    : Cortex-M4                                       **
 **                  MCU    : STM32F401CC                                     **
 **                  SWC    : STM32F401xx                                     **
 **                                                                           **
 **===========================================================================**
 **/

#ifndef STM32F401xx_H
#define STM32F401xx_H

#include <stdint.h>

 /**************************************         Various Memories Base Adresses          ******************************************/
#define FLASH_BASEADDR 0x08000000UL
#define SRAM_BASEADDR  0x20000000UL
#define ROM_BASEADDR   0x1FFFF000UL

 /**************************************         AHB Peripheral Base Adresses          ******************************************/
#define GPIOA_BASEADDR 0x40010800UL
#define GPIOB_BASEADDR 0x40010C00UL
#define GPIOC_BASEADDR 0x40011000UL
#define GPIOD_BASEADDR 0x40011400UL
#define GPIOE_BASEADDR 0x40011800UL

#define RCC_BASEADDR   0x4002800UL

#define SYSTIC_BASEADDR 0xE000E010UL

/**************************************         APB1 Peripheral Base Adresses          ******************************************/
/**************************************         APB2 Peripheral Base Adresses          ******************************************/

/**************************************         SYSTIC Peripheral Definitions       *********************************************/

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} SYSTIC_RegDef_t;

#define MSYSTIC ((SYSTIC_RegDef_t *)SYSTIC_BASEADDR)

 /**************************************       GPIO Register Definition Structure       ******************************************/
typedef struct
{
  volatile uint32_t CRL;  /* Port configuration register low  */
  volatile uint32_t CRH;  /* Port configuration register high */
  volatile uint32_t IDR;  /* Port input data register        */
  volatile uint32_t ODR;  /* Port output data register       */
  volatile uint32_t BSRR; /* Port bit set/reset register     */
  volatile uint32_t BRR;  /* Port bit reset register         */
  volatile uint32_t LCKR; /* Port configuration lock register*/
} GPIO_REGDEF_t;

 /**************************************       RCC Register Definitions Structure       ******************************************/
typedef struct
{
  volatile uint32_t CR;       /* Clock control register */
  volatile uint32_t PLLCFGR;  /* PLL Configuration register*/
  volatile uint32_t CFGR;     /* Clock configuration register */
  volatile uint32_t CIR;      /* Clock interrupt register */
  volatile uint32_t AHB1RSTR; /* AHB1 peripheral reset register */
  volatile uint32_t AHB2RSTR; /* AHB2 peripheral reset register */
  volatile uint32_t RESERVED1[2];
  volatile uint32_t APB1RSTR; /* APB1 peripheral reset register */
  volatile uint32_t APB2RSTR; /* APB2 peripheral reset register */
  volatile uint32_t RESERVED2[2];
  volatile uint32_t AHB1ENR;  /* AHB1 peripheral clock enable register */
  volatile uint32_t AHB2ENR;  /* AHB2 peripheral clock enable register */
  volatile uint32_t RESERVED3[2];
  volatile uint32_t APB1ENR;  /* APB1 peripheral clock enable register */
  volatile uint32_t APB2ENR;  /* APB2 peripheral clock enable register */
  volatile uint32_t RESERVED4[2];
  volatile uint32_t AHB1LPENR;  /* AHB1 peripheral clock enable in low power mode register */
  volatile uint32_t AHB2LPENR;  /* AHB2 peripheral clock enable in low power mode register */
  volatile uint32_t RESERVED5[2];
  volatile uint32_t APB1LPENR;  /* APB1 peripheral clock enable in low power mode register */
  volatile uint32_t APB2LPENR;  /* APB2 peripheral clock enable in low power mode register */
  volatile uint32_t RESERVED6[2];
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
  volatile uint32_t RESERVED7[2];
  volatile uint32_t SSCGR;     /* Spread spectrum clock generation register */
  volatile uint32_t PLLI2SCFGR;     /* PLLI2S configuration register */
  volatile uint32_t RESERVED8[1];
  volatile uint32_t DCKCFGR;     /* Dedicated Clock configuration register */
} RCC_RegDef_t;

 /**************************************         GPIO Peripheral Definitions       ******************************************/

 #define MGPIOA ((GPIO_REGDEF_t *)GPIOA_BASEADDR)
 #define MGPIOB ((GPIO_REGDEF_t *)GPIOB_BASEADDR)
 #define MGPIOC ((GPIO_REGDEF_t *)GPIOC_BASEADDR)
 #define MGPIOD ((GPIO_REGDEF_t *)GPIOD_BASEADDR)
 #define MGPIOE ((GPIO_REGDEF_t *)GPIOE_BASEADDR)

 /**************************************         RCC Peripheral Definitions       *********************************************/

 #define MRCC ((RCC_RegDef_t *)RCC_BASEADDR)

 #endif /* STM32F401xx_H */
 