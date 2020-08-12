---
title: "STM32F446RE Driver APIs Part 1 (GPIO, SPI, I2C and USART)"
date: 2020-05-15
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: /images/embedded_projects/stm32f446redriverapi/stm32f446redriverapi_img00.jpg
excerpt: "embedded c, stm32f446re, eclipse, stm32cubdeide, spi, i2c, stm32, nucleo, gpio"
purpose: "Developing bare-metal drivers for STM32 Microcontrollers in Embedded C. Focusing on general purpose input and output (gpio), and simple communication protocols such as SPI, I2C, USART and UART."
toc: true
classes: wide
images:
  - image_path: /images/embedded_projects/stm32f446redriverapi/stm32f446redriverapi_img01.jpg
    title: "Structure of the drivers"
    weight: 1
---


<h2 class="text-underline">Structure</h2>

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 1 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

<h2 class="text-underline">MicroController specific</h2>

```
/*
 * stm32f446xx.h
 *
 *  Created on: Apr 21, 2020
 *  Author: James Jr Nkhata
 */


#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
#include <stddef.h> // NULL macro definition
#define __vo 	  volatile 					/*!< short hand for volatile qualifier >*/
#define __weak 	  __attribute__((weak)) 	/*!< short hand for gcc attribute weak >*/

/**************************************** START:Processor Specific Details **************************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0					((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1					((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2					((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3					((__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0					((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1					((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2					((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3					((__vo uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR			((__vo uint32_t*)0xE000E400)

/*
 *ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED		4

/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR				0x20000000U  						/*!< base address for flash memory >*/
#define SRAM1_BASEADDR				0x08000000U  						/*!< base address for SRAM1 (112KB) memory >*/
#define SRAM2_BASEADDR			 	(0x08000000U + 0x1C000U)			/*!< base address for SRAM2 (16KB) memory -- Auxiliary Internal Memory >*/
#define SRAM_BASEADDR				SRAM1_BASEADDR 						/*!< base address for SRAM memory >*/
#define ROM_BASEADDR				0x1FFF0000U							/*!< base address for ROM memory  -- System Memory >*/

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASE					0x40000000U							/*!< base address for the peripherals >*/
#define APB1PERIPH_BASEADDR			PERIPH_BASE							/*!< base address for APB1 peripherals >*/
#define APB2PERIPH_BASEADDR			0x40010000U 						/*!< base address for APB2 peripherals >*/
#define AHB1PERIPH_BASEADDR			0x40020000U							/*!< base address for AHB1 peripherals >*/
#define AHB2PERIPH_BASEADDR			0x50000000U							/*!< base address for AHB2 peripherals >*/


/*
 *  base addresses for peripheral hanging on the AHB1 bus
 */

#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)	/*!< base address for GPIOA peripherals - (base address + offset) >*/
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)	/*!< base address for GPIOB peripherals - (base address + offset) >*/
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)	/*!< base address for GPIOC peripherals - (base address + offset) >*/
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)	/*!< base address for GPIOD peripherals - (base address + offset) >*/
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)	/*!< base address for GPIOE peripherals - (base address + offset) >*/
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)	/*!< base address for GPIOF peripherals - (base address + offset) >*/
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)	/*!< base address for GPIOG peripherals - (base address + offset) >*/
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)	/*!< base address for GPIOH peripherals - (base address + offset) >*/

#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)	/*!< base address for RCC registers - (base address + offset) >*/

/*
 *  base addresses for peripheral hanging on the APB1 bus
 */

#define I2C1_BASEADDR   			(APB1PERIPH_BASEADDR + 0x5400)		/*!< base address for I2C1 peripheral - (base address + offset) >*/
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)		/*!< base address for I2C2 peripheral - (base address + offset) >*/
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)		/*!< base address for I2C3 peripheral - (base address + offset) >*/

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)		/*!< base address for SPI2 peripheral - (base address + offset) >*/
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)		/*!< base address for SPI3 peripheral - (base address + offset) >*/

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)		/*!< base address for USART4 peripheral - (base address + offset) >*/
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)		/*!< base address for USART3 peripheral - (base address + offset) >*/
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)		/*!< base address for UART4 peripheral - (base address + offset) >*/
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)		/*!< base address for UART5 peripheral - (base address + offset) >*/


/*
 * base addresses for peripheral hanging on the APB2 bus
 */

#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)		/*!< base address for SPI1 peripheral - (base address + offset) >*/
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR + 0x3400)		/*!< base address for SPI4 peripheral - (base address + offset) >*/
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)		/*!< base address for USART1 peripheral - (base address + offset) >*/
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)		/*!< base address for USART6 peripheral - (base address + offset) >*/
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)		/*!< base address for USART6 peripheral - (base address + offset) >*/
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)		/*!< base address for SYSCFG peripheral - (base address + offset) >*/

/*
 * GPIO peripheral Registers
 */

/********************************************** Peripheral Data Structures ******************************************************************/

/*
 *	peripheral register definition structure for GPIO
 */
typedef struct
{
	__vo uint32_t MODER;  	 	/*!< MODE reg offset 0x00 >*/
	__vo uint32_t OTYPER;		/*!< OUTPUT TYPE reg offset 0x04 >*/
	__vo uint32_t OSPEEDR;  	/*!< SPEED reg offset 0x08 >*/
	__vo uint32_t PUPDR;  		/*!< PULL UP/DOWN reg offset 0x0C >*/
	__vo uint32_t IDR;  		/*!< INPUT DATA reg offset 0x10 >*/
	__vo uint32_t ODR; 			/*!< OUTPUT DATA reg offset 0x14 >*/
	__vo uint32_t BSRR;  		/*!< BIT SET/RESET reg offset 0x18 >*/
	__vo uint32_t LCKR;			/*!< BIT CONFIGURATION LOCK reg offset 0x1C >*/
	__vo uint32_t AFR[2];		/*!< ALTERNATE FUNCTION LOW / HIGH reg offset 0x20 and 0x24 -- AFR[0] - LOW REGISTER -- AFR[1] - HIGH REGISTER>*/
	//uint32_t GPIOx_AFRH;		/*!< ALTERNATE FUNCTION HIGH reg offset 0x24 >*/

}GPIO_RegDef_t;


/*
 *	peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t CR; 				/*!< clock control register - Offset 0x00 >*/
	__vo uint32_t PLLCFGR; 			/*!< PLL configuration register - Offset 0x04 >*/
	__vo uint32_t CFGR;				/*!< clock configuration register - Offset 0x08 >*/
	__vo uint32_t CIR; 				/*!< clock interrupt register - Offset 0x0C >*/
	__vo uint32_t AHB1RSTR; 		/*!< AHB1 peripheral reset register - Offset 0x10 >*/
	__vo uint32_t AHB2RSTR;  		/*!< AHB2 peripheral reset register - Offset 0x14 >*/
	__vo uint32_t AHB3RSTR;  		/*!< AHB3 peripheral reset register - Offset 0x18 >*/
	uint32_t RESERVED_0;			/*!< Reserved bit - Offset 0x1C  >*/
	__vo uint32_t APB1RSTR;  		/*!< APB1 peripheral reset register - Offset 0x20 >*/
	__vo uint32_t APB2RSTR;  		/*!< APB2 peripheral reset register - Offset 0x24 >*/
	uint32_t RESERVED_1[2];			/*!< Reserved bit - Offset 0x28 & 0x2C  >*/
	__vo uint32_t AHB1ENR; 			/*!< AHB1 peripheral clock enable register - Offset 0x30 >*/
	__vo uint32_t AHB2ENR; 			/*!< AHB2 peripheral clock enable register - Offset 0x34 >*/
	__vo uint32_t AHB3ENR; 			/*!< AHB3 peripheral clock enable register - Offset 0x38 >*/
	uint32_t RESERVED_2;			/*!< Reserved bit - Offset 0x3C  >*/
	__vo uint32_t APB1ENR; 			/*!< APB1 peripheral clock enable register - Offset 0x40 >*/
	__vo uint32_t APB2ENR; 			/*!< APB2 peripheral clock enable register - Offset 0x44 >*/
	uint32_t RESERVED_3[2];			/*!< Reserved bit - Offset 0x48 & 0x4C  >*/
	__vo uint32_t AHB1LPENR; 		/*!< AHB1 peripheral clock enable in low power mode register - Offset 0x50 >*/
	__vo uint32_t AHB2LPENR;	 	/*!< AHB2 peripheral clock enable in low power mode register - Offset 0x54 >*/
	__vo uint32_t AHB3LPENR; 		/*!< AHB3 peripheral clock enable in low power mode register - Offset 0x58 >*/
	uint32_t RESERVED_4;			/*!< Reserved bit - Offset 0x5C  >*/
	__vo uint32_t APB1LPENR; 		/*!< APB1 peripheral clock enable in low power mode register - Offset 0x60 >*/
	__vo uint32_t APB2LPENR; 		/*!< APB2 peripheral clock enable in low power mode register - Offset 0x64 >*/
	uint32_t RESERVED_5[2];			/*!< Reserved bit - Offset 0x68 & 0x6C  >*/
	__vo uint32_t BDCR; 			/*!< Backup domain control register - Offset 0x70 >*/
	__vo uint32_t CSR; 				/*!< Clock control & status register - Offset 0x74 >*/
	uint32_t RESERVED_6[2];			/*!< Reserved bit - Offset 0x78 & 0x7C  >*/
	__vo uint32_t SSCGR; 			/*!< Spread spectrum clock generation register  - Offset 0x80 >*/
	__vo uint32_t PLLI2SCFGR; 		/*!< PLLI2S configuration register - Offset 0x84 >*/
	__vo uint32_t PLLSAICSFGR; 		/*!< PLL configuration register - Offset 0x88 >*/
	__vo uint32_t DCKCSFGR; 		/*!< Dedicated Clock Configuration Register - Offset 0x8C >*/
	__vo uint32_t CKGATENR; 		/*!< Clocks gated enable register - Offset 0x90 >*/
	__vo uint32_t DCKCSFGR2; 		/*!< Dedicated clocks configuration register 2  - Offset 0x94 >*/
}RCC_RegDef_t;


/*
 *	peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR;				/*!< Interrupt mask register - Offset 0x00 > */
	__vo uint32_t EMR;				/*!< Event mask register - Offset 0x04 > */
	__vo uint32_t RTSR;				/*!< Rising trigger selection register - Offset 0x08 > */
	__vo uint32_t FTSR;				/*!< Falling trigger selection register - Offset 0x0C > */
	__vo uint32_t SWIER;			/*!< Software interrupt event register - Offset 0x10 > */
	__vo uint32_t PR;				/*!< Pending register - Offset 0x14 > */
}EXTI_RegDef_t;


/*
 *	peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP; 			/*!< memory remap register - offset 0x00 >*/
	__vo uint32_t PMC;				/*!< peripheral mode configuration register - offset 0x04 >*/
	__vo uint32_t EXTICR[4]; 		/*!< external interrupt configuration register 1 to 4 - offset 0x08 - 0x14 >*/
	uint32_t RESERVED0;				/*!< Reserved bit - Offset 0x18 >*/
	__vo uint32_t CMPCR; 			/*!< Compensation cell control register - offset 0x20 >*/
	uint32_t RESERVED1[2];			/*!< Reserved bit - Offset 0x24 & 0x28  >*/
	__vo uint32_t CFGR; 			/*!< configuration register - offset 0x2C >*/
}SYSCFG_RegDef_t;


/*
 *	peripheral register definition structure for SPI
 */
typedef struct
{
	__vo uint32_t CR1; 					/*!< control register 1 (Not used in I2S mode) - offset 0x00 >*/
	__vo uint32_t CR2; 					/*!< control register 2 - offset 0x04 >*/
	__vo uint32_t SR; 					/*!< status register - offset 0x08 >*/
	__vo uint32_t DR; 					/*!< data register - offset 0x0C >*/
	__vo uint32_t CRCPR;				/*!< polynomial register (Not used in I2S mode) - offset 0x10 >*/
	__vo uint32_t RXCRCR;				/*!< RX CRC register (Not used in I2S mode) - offset 0x14 >*/
	__vo uint32_t TXCRCR;				/*!< TX CRC register (Not used in I2S mode) - offset 0x18 >*/
	__vo uint32_t I2SCFGR;				/*!< I2S configuration register - offset 0x1C >*/
	__vo uint32_t I2SPR;				/*!< I2S prescaler register - offset 0x20 >*/
}SPI_RegDef_t;

/*
 *	peripheral register definition structure for I2C
 */
typedef struct{
	__vo uint32_t CR1;					/*!< Control register 1	- offset 0x00 >*/
	__vo uint32_t CR2; 					/*!< Control register 2	- offset 0x04 >*/
	__vo uint32_t OAR1;					/*!< Own address register 1 - offset 0x08 >*/
	__vo uint32_t OAR2;					/*!< Own address register 2 - offset 0x0C >*/
	__vo uint32_t DR; 					/*!< Data Register	- offset 0x10 >*/
	__vo uint32_t SR1; 					/*!< Status register 1 - offset 0x14 >*/
	__vo uint32_t SR2; 					/*!< Status register 2 - offset 0x18 >*/
	__vo uint32_t CCR; 					/*!< Clock control register - offset 0x1C >*/
	__vo uint32_t TRISE;				/*!< TRISE register - offset 0x20 >*/
	__vo uint32_t FLTR; 				/*!< FLTR register - offset 0x24 >*/

}I2C_RegDef_t;

/*
* Peripheral definitions (Peripheral base address typecasted to xxx_Reg_Def_t )
*/
#define GPIOA				((GPIO_RegDef_t*) GPIOA_BASEADDR) 		/*!< GPIOA typecasted to GPIO RegDef structure >*/
#define GPIOB				((GPIO_RegDef_t*) GPIOB_BASEADDR) 		/*!< GPIOB typecasted to GPIO RegDef structure >*/
#define GPIOC				((GPIO_RegDef_t*) GPIOC_BASEADDR) 		/*!< GPIOC typecasted to GPIO RegDef structure >*/
#define GPIOD				((GPIO_RegDef_t*) GPIOD_BASEADDR) 		/*!< GPIOD typecasted to GPIO RegDef structure >*/
#define GPIOE				((GPIO_RegDef_t*) GPIOE_BASEADDR) 		/*!< GPIOE typecasted to GPIO RegDef structure >*/
#define GPIOF				((GPIO_RegDef_t*) GPIOF_BASEADDR) 		/*!< GPIOF typecasted to GPIO RegDef structure >*/
#define GPIOG				((GPIO_RegDef_t*) GPIOG_BASEADDR) 		/*!< GPIOG typecasted to GPIO RegDef structure >*/
#define GPIOH				((GPIO_RegDef_t*) GPIOH_BASEADDR) 		/*!< GPIOH typecasted to GPIO RegDef structure >*/

#define RCC					((RCC_RegDef_t*) RCC_BASEADDR) 	 		/*!< RCC typecasted to RCC RegDef structure >*/

#define EXTI				((EXTI_RegDef_t*) EXTI_BASEADDR) 		/*!< EXTI typecasted to EXTI RegDef structure >*/

#define SYSCFG				((SYSCFG_RegDef_t*) SYSCFG_BASEADDR) 	/*!< SYSCFG typecasted to SYSCFG RegDef structure >*/

#define SPI1				((SPI_RegDef_t*) SPI1_BASEADDR)	 	/*!< SPI1 typecasted to SPI RegDef structure >*/
#define SPI2				((SPI_RegDef_t*) SPI2_BASEADDR)	 	/*!< SPI2 typecasted to SPI RegDef structure >*/
#define SPI3				((SPI_RegDef_t*) SPI3_BASEADDR)	 	/*!< SPI3 typecasted to SPI RegDef structure >*/
#define SPI4				((SPI_RegDef_t*) SPI4_BASEADDR)	 	/*!< SPI4 typecasted to SPI RegDef structure >*/

#define I2C1				((I2C_RegDef_t*) I2C1_BASEADDR)	 	/*!< I2C1 typecasted to I2C RegDef structure >*/
#define I2C2				((I2C_RegDef_t*) I2C2_BASEADDR)	 	/*!< I2C2 typecasted to I2C RegDef structure >*/
#define I2C3				((I2C_RegDef_t*) I2C3_BASEADDR)	 	/*!< I2C3 typecasted to I2C RegDef structure >*/

/*   CLOCK ENABLE MACROS */

/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 0))			/*!< Enable AHB1ENR bit 0 GPIOA Enable >*/
#define GPIOB_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 1))			/*!< Enable AHB1ENR bit 1 GPIOB Enable >*/
#define GPIOC_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 2))			/*!< Enable AHB1ENR bit 2 GPIOC Enable >*/
#define GPIOD_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 3))			/*!< Enable AHB1ENR bit 3 GPIOD Enable >*/
#define GPIOE_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 4))			/*!< Enable AHB1ENR bit 4 GPIOE Enable >*/
#define GPIOF_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 5))			/*!< Enable AHB1ENR bit 5 GPIOF Enable >*/
#define GPIOG_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 6))			/*!< Enable AHB1ENR bit 6 GPIOG Enable >*/
#define GPIOH_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 7))			/*!< Enable AHB1ENR bit 7 GPIOH Enable >*/

/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()		(RCC-> APB1ENR |= (1 << 21))		/*!< Enable APB1ENR bit 21 I2C1EN I2C1 clock enable >*/
#define I2C2_PCLK_EN()		(RCC-> APB1ENR |= (1 << 22)) 		/*!< Enable APB1ENR bit 22 I2C2EN I2C2 clock enable >*/
#define I2C3_PCLK_EN()		(RCC-> APB1ENR |= (1 << 23)) 		/*!< Enable APB1ENR bit 23 I2C3EN I2C3 clock enable >*/

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()		(RCC-> APB2ENR |= (1 << 12)) 			/*!< Enable APB2ENR bit 12 SPI1EN SPI1 clock enable >*/
#define SPI4_PCLK_EN()		(RCC-> APB2ENR |= (1 << 13)) 			/*!< Enable APB2ENR bit 13 SPI1EN SPI4 clock enable >*/

#define SPI2_PCLK_EN()		(RCC-> APB1ENR |= (1 << 14)) 			/*!< Enable APB1ENR bit 14 SPI2EN SPI2 clock enable >*/
#define SPI3_PCLK_EN()		(RCC-> APB1ENR |= (1 << 15)) 			/*!< Enable APB1ENR bit 15 SPI3EN SPI3 clock enable >*/


/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN()	(RCC-> APB2ENR |= (1 << 4)) 		/*!< Enable APB2ENR bit 4 USART1EN USART1 clock enable >*/
#define USART6_PCLK_EN()	(RCC-> APB2ENR |= (1 << 5)) 		/*!< Enable APB2ENR bit 5 USART6EN USART6 clock enable >*/

#define USART2_PCLK_EN()	(RCC-> APB1ENR |= (1 << 17)) 		/*!< Enable APB1ENR bit 17 USART2EN USART2 clock enable >*/
#define USART3_PCLK_EN()	(RCC-> APB1ENR |= (1 << 18)) 		/*!< Enable APB1ENR bit 18 USART3EN USART3 clock enable >*/


/*
 * Clock Enable Macros for UARTx peripherals
 */
#define UART4_PCLK_EN()		(RCC-> APB1ENR |= (1 << 19)) 		/*!< Enable APB1ENR bit 19 USART2EN USART4 clock enable >*/
#define UART5_PCLK_EN()		(RCC-> APB1ENR |= (1 << 20)) 		/*!< Enable APB1ENR bit 20 USART3EN USART5 clock enable >*/

/*
 * Clock Enable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN() 	(RCC-> APB2ENR |= (1 << 14))		/*!< Enable APB2ENR bit 14 System configuration controller clock enable >*/


/* CLOCK DISABLE MACROS */

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 0))		/*!< Disable AHB1ENR bit 0 GPIOA Disable >*/
#define GPIOB_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 1))		/*!< Disable AHB1ENR bit 1 GPIOB Disable >*/
#define GPIOC_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 2))		/*!< Disable AHB1ENR bit 2 GPIOC Disable >*/
#define GPIOD_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 3))		/*!< Disable AHB1ENR bit 3 GPIOD Disable >*/
#define GPIOE_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 4))		/*!< Disable AHB1ENR bit 4 GPIOE Disable >*/
#define GPIOF_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 5))		/*!< Disable AHB1ENR bit 5 GPIOF Disable >*/
#define GPIOG_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 6))		/*!< Disable AHB1ENR bit 6 GPIOG Disable >*/
#define GPIOH_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 7))		/*!< Disable AHB1ENR bit 7 GPIOH Disable >*/

/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 21))		/*!< Disable APB1ENR bit 21 I2C1EN I2C1 clock Disable >*/
#define I2C2_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 22)) 		/*!< Disable APB1ENR bit 22 I2C2EN I2C2 clock Disable >*/
#define I2C3_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 23)) 		/*!< Disable APB1ENR bit 23 I2C3EN I2C3 clock Disable >*/

/*
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()		(RCC-> APB2ENR &= ~(1 << 12)) 			/*!< Disable APB2ENR bit 12 SPI1EN SPI1 clock Disable >*/
#define SPI4_PCLK_DI()		(RCC-> APB2ENR &= ~(1 << 13)) 			/*!< Disable APB2ENR bit 13 SPI1EN SPI4 clock Disable >*/
#define SPI2_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 14)) 			/*!< Disable APB1ENR bit 14 SPI2EN SPI2 clock Disable >*/
#define SPI3_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 15)) 			/*!< Disable APB1ENR bit 15 SPI3EN SPI3 clock Disable >*/

/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_PCLK_DI()	(RCC-> APB2ENR &= ~(1 << 4)) 		/*!< Disable APB2ENR bit 4 USART1EN USART1 clock Disable >*/
#define USART6_PCLK_DI()	(RCC-> APB2ENR &= ~(1 << 5)) 		/*!< Disable APB2ENR bit 5 USART6EN USART6 clock Disable >*/

#define USART2_PCLK_DI()	(RCC-> APB1ENR &= ~(1 << 17)) 		/*!< Disable APB1ENR bit 17 USART2EN USART2 clock Disable >*/
#define USART3_PCLK_DI()	(RCC-> APB1ENR &= ~(1 << 18)) 		/*!< Disable APB1ENR bit 18 USART3EN USART3 clock Disable >*/

/*
 * Clock Disable Macros for UARTx peripherals
 */
#define UART4_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 19)) 		/*!< Disable APB1ENR bit 19 USART2EN USART4 clock Disable >*/
#define UART5_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 20)) 		/*!< Disable APB1ENR bit 20 USART3EN USART5 clock Disable >*/

/*
 * Clock Disable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI() 	(RCC-> APB2ENR &= ~(1 << 14))		/*!< Disable APB2ENR bit 14 System configuration controller clock Disable >*/


/*
 * GPIO BASEADDRESS Port to Code Macro
 */
#define GPIO_BASEADDR_TO_CODE(x)			(	(x == GPIOA) ? 0:\
												(x == GPIOB) ? 1:\
												(x == GPIOC) ? 2:\
												(x == GPIOD) ? 3:\
												(x == GPIOE) ? 4:\
												(x == GPIOF) ? 5:\
												(x == GPIOG) ? 6:\
												(x == GPIOH) ? 7:0	 )


/*
 * Macros to reset GPIO peripherals
 */
#define GPIOA_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 0));	(RCC->AHB1RSTR &= ~(1 << 0));	}while(0)
#define GPIOB_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 1));	(RCC->AHB1RSTR &= ~(1 << 1));	}while(0)
#define GPIOC_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 2));	(RCC->AHB1RSTR &= ~(1 << 2));	}while(0)
#define GPIOD_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 3));	(RCC->AHB1RSTR &= ~(1 << 3));	}while(0)
#define GPIOE_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 4));	(RCC->AHB1RSTR &= ~(1 << 4));	}while(0)
#define GPIOF_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 5));	(RCC->AHB1RSTR &= ~(1 << 5));	}while(0)
#define GPIOG_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 6));	(RCC->AHB1RSTR &= ~(1 << 6));	}while(0)
#define GPIOH_REG_RESET()	do{	(RCC->AHB1RSTR |= (1 << 7));	(RCC->AHB1RSTR &= ~(1 << 7));	}while(0)


/*
 * Macros to reset SPI peripherals
 */
#define SPI1_REG_RESET()	do{ (RCC->APB2RSTR |= (1 << 12));   (RCC->APB2RSTR &= ~(1 << 12));	}while(0)
#define SPI2_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 14));   (RCC->APB1RSTR &= ~(1 << 14));	}while(0)
#define SPI3_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 15));   (RCC->APB1RSTR &= ~(1 << 15));	}while(0)
#define SPI4_REG_RESET()	do{ (RCC->APB2RSTR |= (1 << 13));   (RCC->APB2RSTR &= ~(1 << 13));	}while(0)

/*
 *	Macros to reset I2C peripherals
 */
#define I2C1_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 21));	 (RCC->APB1RSTR &= ~(1 << 21));	}while(0)
#define I2C2_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 22));	 (RCC->APB1RSTR &= ~(1 << 22));	}while(0)
#define I2C3_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 23));	 (RCC->APB1RSTR &= ~(1 << 23));	}while(0)

/*
 * IRQ (Interrupt Request) Numbers of the STM32F446xx MCU
 */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

#define IRQ_NO_SPI1					35
#define IRQ_NO_SPI2					36
#define IRQ_NO_SPI3					51
#define IRQ_NO_SPI4					84

/*
 * macros for all the possible priority levels (NVIC IRQ Priorities)
 */
#define NVIC_IRQ_PRI0				0
#define NVIC_IRQ_PRI1				1
#define NVIC_IRQ_PRI2				2
#define NVIC_IRQ_PRI3				3
#define NVIC_IRQ_PRI4				4
#define NVIC_IRQ_PRI5				5
#define NVIC_IRQ_PRI6				6
#define NVIC_IRQ_PRI7				7
#define NVIC_IRQ_PRI8				8
#define NVIC_IRQ_PRI9				9
#define NVIC_IRQ_PRI10				10
#define NVIC_IRQ_PRI11				11
#define NVIC_IRQ_PRI12				12
#define NVIC_IRQ_PRI13				13
#define NVIC_IRQ_PRI14				14
#define NVIC_IRQ_PRI15				15


/*
 * Some generic Macros
 */

#define ENABLE 					1
#define DISABLE 				0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET
#define FLAG_SET				SET
#define FLAG_RESET				RESET


/***********************************************************************************************************************
 * Bit position definitions of SPI peripheral
 * *********************************************************************************************************************/
/*
 * Bit position definitions SPI_CR1 (control register 1)
 */
#define SPI_CR1_CPHA 			0						/*!< Clock phase 	>*/
#define SPI_CR1_CPOL 			1						/*!< Clock polarity >*/
#define SPI_CR1_MSTER 			2						/*!< Master selection >*/
#define SPI_CR1_BR 				3						/*!< Baud rate control > */
#define SPI_CR1_SPE 			6						/*!< SPI enable > */
#define SPI_CR1_LSB_FIRST		7						/*!< Frame format > */
#define SPI_CR1_SSI 			8						/*!< Internal slave select > */
#define SPI_CR1_SSM 			9						/*!< Software slave management > */
#define SPI_CR1_RXONLY 			10						/*!< Receive only mode enable > */
#define SPI_CR1_DFF 			11						/*!< Data frame format > */
#define SPI_CR1_CRC_NEXT		12						/*!< CRC transfer next > */
#define SPI_CR1_CRC_EN			13						/*!< Hardware CRC calculation enable > */
#define SPI_CR1_BIDI_OE			14						/*!< Output enable in bidirectional mode > */
#define SPI_CR1_BIDI_MODE		15						/*!< Bidirectional data mode enable > */

/*
 * Bit position definitions SPI_CR2 (control register 2)
 */
#define SPI_CR2_RXDMAEN			0						/*!< Rx buffer DMA enable > */
#define SPI_CR2_TXDMAEN			1						/*!< Tx buffer DMA enable > */
#define SPI_CR2_SSOE			2						/*!< SS output enable > */
#define SPI_CR2_FRF				4						/*!< Frame format > */
#define SPI_CR2_ERRIE			5						/*!< Error interrupt enable > */
#define SPI_CR2_RXNEIE			6						/*!< RX buffer not empty interrupt enable > */
#define SPI_CR2_TXEIE			7						/*!< Tx buffer empty interrupt enable> */

/*
 * Bit position definitions SPI_SR (status register)
 */
#define SPI_SR_RXNE				0						/*!< Receive buffer not empty > */
#define SPI_SR_TXE				1						/*!< Transmit buffer empty > */
#define SPI_SR_CHSIDE			2						/*!< Channel side > */
#define SPI_SR_UDR				3						/*!< Underrun flag > */
#define SPI_SR_CRC_ERR			4						/*!< CRC error flag > */
#define SPI_SR_MODF				5						/*!< Mode fault > */
#define SPI_SR_OVR				6						/*!< Overrun flag > */
#define SPI_SR_BSY				7						/*!< Busy flag > */
#define SPI_SR_FRE				8						/*!< Frame Error > */



/***********************************************************************************************************************
 * Bit position definitions of I2C peripheral
 * *********************************************************************************************************************/
/*
 * Bit position definitions I2C_CR1 (control register 1)
 */
#define I2C_CR1_PE				0						/*!< Peripheral enable >*/
#define I2C_CR1_SMBUS			1						/*!< SMBUS mode >*/
#define I2C_CR1_SMBTYPE			3						/*!< SMBus type >*/
#define I2C_CR1_ENARP			4						/*!< ARP enable >*/
#define I2C_CR1_ENPEC			5						/*!< PEC enable >*/
#define I2C_CR1_ENGC			6						/*!< General call enable >*/
#define I2C_CR1_NOSTRETCH		7						/*!< Clock stretching disable (Slave mode) >*/
#define I2C_CR1_START			8						/*!< Start generation >*/
#define I2C_CR1_STOP			9						/*!< Stop generation >*/
#define I2C_CR1_ACK				10						/*!< Acknowledge enable >*/
#define I2C_CR1_POS				11						/*!< Acknowledge/PEC Position (for data reception) >*/
#define I2C_CR1_PEC				12						/*!< Packet error checking >*/
#define I2C_CR1_ALERT			13						/*!< SMBUS alert >*/
#define I2C_CR1_SWRST			15						/*!< Software reset >*/

/*
 * Bit position definitions I2C_CR2 (control register 2)
 */
#define I2C_CR2_FREQ0_5			0						/*!< FREQ[5:0]: Peripheral clock frequency >*/
#define I2C_CR2_ITERREN			8						/*!< Error interrupt enable >*/
#define I2C_CR2_ITEVTEN			9						/*!< Event interrupt enable >*/
#define I2C_CR2_ITBUFFEN		10						/*!< Buffer interrupt enable >*/
#define I2C_CR2_DMAEN			11						/*!< DMA requests enable >*/
#define I2C_CR2_LAST			12						/*!< DMA last transfer >*/

/*
 * Bit position definitions I2C_OAR1 (own address register 1 )
 */
#define I2C_OAR1_ADD0			0						/*!< interface address >*/
#define I2C_OAR1_ADD7_1			1						/*!< interface address >*/
#define I2C_OAR1_ADD9_8			8						/*!< interface address >*/
#define I2C_OAR1_ADDMODE		15						/*!< Addressing mode (slave mode) >*/

/*
 * Bit position definitions I2C_OAR2 (own address register 2 )
 */
#define I2C_OAR2_ENDUAL			0						/*!< Dual addressing mode enable >*/
#define I2C_OAR2_ADD7_1			1						/*!< interface address >*/

/*
 * Bit position definitions I2C_SR1 (status register 1 )
 */
#define I2C_SR1_SB				0						/*!< Start bit (Master mode) >*/
#define I2C_SR1_ADDR			1						/*!< Address sent (master mode)/matched (slave mode) >*/
#define I2C_SR1_BTF				2						/*!< Byte transfer finished >*/
#define I2C_SR1_ADDR10			3						/*!< 10-bit header sent (Master mode) >*/
#define I2C_SR1_STOPF			4						/*!< Stop detection (slave mode) >*/
#define I2C_SR1_RXNE			6						/*!< Data register not empty (receivers) >*/
#define I2C_SR1_TXE				7						/*!< Data register empty (transmitters) >*/
#define I2C_SR1_BERR			8						/*!< Bus error >*/
#define I2C_SR1_ARLO			9						/*!< Arbitration lost (master mode) >*/
#define I2C_SR1_AF				10						/*!< Acknowledge failure >*/
#define I2C_SR1_OVR				11						/*!< Overrun/Underrun >*/
#define I2C_SR1_PECERR			12						/*!< PEC Error in reception >*/
#define I2C_SR1_TIMEOUT			14						/*!< Timeout or Tlow error >*/
#define I2C_SR1_SMBALERT		15						/*!< SMBus alert >*/

/*
 * Bit position definitions I2C_SR2 (status register 2 )
 */
#define I2C_SR2_MSL				0						/*!< Master/slave >*/
#define I2C_SR2_BUSY			1						/*!< Bus busy >*/
#define I2C_SR2_TRA				2						/*!< Transmitter/receiver >*/
#define I2C_SR2_GENCALL			4						/*!< General call address (Slave mode) >*/
#define I2C_SR2_SMBDEFAULT		5						/*!< SMBus device default address (Slave mode) >*/
#define I2C_SR2_SMBHOST			6						/*!< SMBus host header (Slave mode) >*/
#define I2C_SR2_DUALF			7						/*!< Dual flag (Slave mode) >*/
#define I2C_SR2_PEC7_0			8						/*!< Packet error checking register >*/

/*
 * Bit position definitions I2C_CCR (clock control register )
 */
#define I2C_CCR_CCR11_0			0						/*!< Clock control register in Fm/Sm mode (Master mode) >*/
#define I2C_CCR_DUTY			14						/*!< Fm mode duty cycle >*/
#define I2C_CCR_F_S				15						/*!< I2C master mode selection >*/

/*
 * Bit position definitions I2C_FLTR (FLTR register )
 */
#define I2C_FLTR_DNF3_0			0						/*!< Digital noise filter >*/
#define I2C_FLTR_ANOF			4						/*!< Analog noise filter OFF >*/

#include "stm32f446xx_gpio_driver.h" // include GPIO_driver header file to simplify import
#include "stm32f446xx_spi_driver.h" // include spi_driver header file to simplify import
#include "stm32f446xx_i2c_driver.h" // include i2c_driver header file to simplify import

#endif /* INC_STM32F446XX_H_ */
```
<h2 class="text-underline">General Purpose IO (GPIO)</h2>
```
/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: 23 Apr 2020
 *  Author: CJ-PCGAMER-01
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber; 		/*!< possible values from @PIN_NUMBERS >*/
	uint8_t GPIO_PinMode; 			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed; 			/*!< possible values from @GPIO_PIN_SPEEDS >*/
	uint8_t GPIO_PinPuPdControl; 	/*!<  >*/
	uint8_t GPIO_PinOPType;			/*!< >*/
	uint8_t GPIO_PinAltFunMode; 	/*!<  >*/

}GPIO_PinConfig_t ;

typedef struct
{

	GPIO_RegDef_t *pGPIOx; /*!< This holds the base address of the GPIO port to which the pin belongs  >*/
	GPIO_PinConfig_t GPIO_PinConfig; /*!< This holds GPIO pin configurations settings >*/

}GPIO_Handle_t ;

/*
 *@PIN_NUMBERS
 *GPIO possible pin numbers
 */
#define GPIO_PIN_0					0
#define GPIO_PIN_1					1
#define GPIO_PIN_2					2
#define GPIO_PIN_3					3
#define GPIO_PIN_4					4
#define GPIO_PIN_5					5
#define GPIO_PIN_6					6
#define GPIO_PIN_7					7
#define GPIO_PIN_8					8
#define GPIO_PIN_9					9
#define GPIO_PIN_10					10
#define GPIO_PIN_11					11
#define GPIO_PIN_12					12
#define GPIO_PIN_13					13
#define GPIO_PIN_14					14
#define GPIO_PIN_15					15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 				0
#define GPIO_MODE_OUT 				1
#define GPIO_MODE_ALT_FN			2
#define GPIO_MODE_ANALOG			3
#define GPIO_MODE_IT_FT				4
#define GPIO_MODE_IT_RT				5
#define GPIO_MODE_IT_RFT			6

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP				0
#define GPIO_OP_TYPE_OD				1

/*
 *@GPIO_PIN_SPEEDS
 * GPIO possible Speeds
 */
#define GPIO_SPEED_LOW 				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST				2
#define GPIO_SPEED_HIGH				3

/*
 * @GPIO_PIN_PULLUPANDDOWN
 * GPIO pin pull up and pull down configuration macros
 */
#define GPIO_NO_PUPD				0
#define GPIO_PIN_PU					1
#define GPIO_PIN_PD					2

/************************************************************************************************************
 * 										APIs supported by this driver
 * 			For more information about the APIs check the function definitions
 * **********************************************************************************************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ configuration and ISR Handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
```

```c
/*
 * stm32f446xx_gpio_driver.c
 *
 *  Created on: 23 Apr 2020
 *  Author: James Jr Nkhata
 */

#include "stm32f446xx_gpio_driver.h"




/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}

	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}
}




/*********************************************************************
 * @fn      		  -	GPIO_Init
 *
 * @brief             - Used to initialise GPIO
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

	// Enable peripheral clock for GPIO
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	uint32_t temp; // temp value to hold information

	//1. configure the mode of the gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // set the value of Pin Mode shifted 2 * pin number and set to temp
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the value of MODER reg
		pGPIOHandle->pGPIOx->MODER |= temp; // set the value of MODER reg to the value of temp

	}
	else
	{
		// This is an Interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1. Configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 2. Configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// 3. Configure both FTSR and RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. configure the GPIO port selection in SYSCFG_EXTICR

		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t	portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		//3. enable EXTI interrupt delivery through IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}

	temp = 0 ; // reset temp to 0

	//2 . configure the speed

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // set the value of Pin Speed shifted 2 * pin number to temp
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x11); // clearing the value of OSPEED reg
	pGPIOHandle->pGPIOx->OSPEEDR |= temp; // set the value of OSPEED reg to the value of temp

	temp = 0 ; // reset temp to 0

	//3 . configure the pupd settings

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // set the value of Pin Pull up / pull down shifted 2 * pin number to temp
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the value of PUPDR reg
	pGPIOHandle->pGPIOx->PUPDR |= temp; // set the value of PUPDR reg to the value of temp

	temp = 0 ; // reset temp to 0

	//4 . configure the optype

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the value for Output Type pin shifted by pin number to temp
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the value of OTYPER reg
	pGPIOHandle->pGPIOx->OTYPER |= temp; // set the value of OTYPE reg to temp

	temp = 0 ; // reset temp to 0

	//5 . configure the alt functionality

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALT_FN)
	{
		// configure alt function reg

		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << (4 * temp2) ); // clearing the value of AFR[] reg
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); // set the value of the corresponding AFR[] Array
	}
}




/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
}




/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */


uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t Value;
	Value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001) ;
	return Value;
}




/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t Value;
	Value = (uint16_t) pGPIOx->IDR ;
	return Value;
}




/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}




/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}




/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */



void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber); // toggle with XOR operation
}




/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */


void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= 1 << IRQNumber;
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ISER1 register
			*NVIC_ISER1 |= 1 << IRQNumber % 32;
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			// program ISER2 register - 64 to 95
			*NVIC_ISER2 |= 1 << IRQNumber % 64;
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= 1 << IRQNumber;
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ICER1 register
			*NVIC_ICER1 |= 1 << IRQNumber % 32;
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			// program ICER2 register - 64 to 95
			*NVIC_ICER2 |= 1 << IRQNumber % 64;
		}
	}


}




/*********************************************************************
 * @fn      		  - GPIO_IRQPriorityConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQProirity)
{
	//1. First lets find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ((8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED));
	*(NVIC_PR_BASE_ADDR + iprx ) |= (IRQNumber << shift_amount);
}



/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// clear the exti pr register corresponding to the pin number
	if(EXTI->PR & ( 1 << PinNumber))
	{
		//clear
		EXTI->PR |= ( 1 << PinNumber);
	}
}


```

```
<h2 class="text-underline">Serial Peripheral Interface (SPI)</h2>
**inc**
<h2 class="text-underline">Inter-integrated Circuit (I2C)</h2>
**inc**
