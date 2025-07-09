/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_private.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : GPIO                                            **
 **                                                                           **
 **===========================================================================**
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/************************** GPIO PORT COUNT **************************/
#define GPIO_PORT_COUNT 5u

/************************** GPIO Configuration Register Masks **************************/
#define GPIO_MODE_MASK 0b11
#define GPIO_CNF_MASK 0b11
#define GPIO_MODE_CNF_MASK 0b1111

#define GPIO_CRL_SHIFT 4u
#define GPIO_CRH_SHIFT 4u

/* Number of pins per port */
#define GPIO_PIN_COUNT 16u
#define GPIO_PIN_LOW_COUNT 8u
#define GPIO_PIN_HIGH_COUNT 8u

/* Register bit positions */
#define GPIO_CRL_MAX_PIN 7u
#define GPIO_CRH_MIN_PIN 8u
#define GPIO_CRH_MAX_PIN 15u

/* ODR Register Masks */
#define GPIO_ODR_MASK 0x0001u
#define GPIO_ODR_MAX_PIN 15u

/* BSRR and BRR Register Masks */
#define GPIO_BSRR_SET_OFFSET 0u
#define GPIO_BSRR_RESET_OFFSET 16u
#define GPIO_BRR_OFFSET 0u

/* Lock Register Masks */
#define GPIO_LOCK_KEY 0x0001u
#define GPIO_LOCK_SEQUENCE_BIT 16u

#endif /* GPIO_PRIVATE_H_ */