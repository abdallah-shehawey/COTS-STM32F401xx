/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M4                                       **
 **                  MCU    : F401CC                                          **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_RCC_PRIVATE_H_
#define MCAL_RCC_PRIVATE_H_

#define SYS_CLK_MASK 0X3
#define AHB_DIV_MASK (0XF << 4)
#define APB1_DIV_MASK (0X7 << 10)
#define APB2_DIV_MASK (0X7 << 13)

#define PLLM_CONFIG_MASK 0X3F
#define PLLN_CONFIG_MASK (0X1FF << 6)
#define PLLP_CONFIG_MASK (0X3 << 16)
#define PLLQ_CONFIG_MASK (0XF << 24)

#endif /* MCAL_RCC_PRIVATE_H_ */
