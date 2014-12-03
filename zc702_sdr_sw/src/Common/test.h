/**************************************************************************//**
*   @file   i2c.h
*   @brief  I2C header file.
*   @author acozma (andrei.cozma@analog.com)
*
*******************************************************************************
* Copyright 2011(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************
*   SVN Revision: $WCREV$
******************************************************************************/
#ifndef __TEST_H__
#define __TEST_H__

/*****************************************************************************/
/******************* Constants ***********************************************/
/*****************************************************************************/
#ifdef _XPARAMETERS_PS_H_
	#ifdef XPAR_AXI_AD9122_0_BASEADDR
		#define CFAD9122_0_BASEADDR     XPAR_AXI_AD9122_0_BASEADDR
	#else
		#define CFAD9122_0_BASEADDR     XPAR_AXI_AD9122_BASEADDR
	#endif
	#ifdef XPAR_AXI_AD9643_0_BASEADDR
		#define CFAD9643_0_BASEADDR     XPAR_AXI_AD9643_0_BASEADDR
	#else
		#define CFAD9643_0_BASEADDR     XPAR_AXI_AD9643_BASEADDR
	#endif
	#ifdef XPAR_AXI_DMAC_1_BASEADDR
		#define DMA9122_0_BASEADDR      XPAR_AXI_DMAC_1_BASEADDR
	#else
		#define DMA9122_0_BASEADDR      XPAR_AXI_AD9122_DMA_BASEADDR
	#endif
	#ifdef XPAR_AXI_DMAC_0_BASEADDR
		#define DMA9643_0_BASEADDR      XPAR_AXI_DMAC_0_BASEADDR
	#else
		#define DMA9643_0_BASEADDR      XPAR_AXI_AD9643_DMA_BASEADDR
	#endif
	#ifdef XPAR_AXI_AD9122_0_BASEADDR
		#define CFAD9122_1_BASEADDR     XPAR_AXI_AD9122_0_BASEADDR
	#else
		#define CFAD9122_1_BASEADDR     XPAR_AXI_AD9122_BASEADDR
	#endif
	#ifdef XPAR_AXI_AD9643_0_BASEADDR
		#define CFAD9643_1_BASEADDR     XPAR_AXI_AD9643_0_BASEADDR
	#else
		#define CFAD9643_1_BASEADDR     XPAR_AXI_AD9643_BASEADDR
	#endif
	#ifdef XPAR_AXI_DMAC_1_BASEADDR
		#define DMA9122_1_BASEADDR      XPAR_AXI_DMAC_1_BASEADDR
	#else
		#define DMA9122_1_BASEADDR      XPAR_AXI_AD9122_DMA_BASEADDR
	#endif
	#ifdef XPAR_AXI_DMAC_0_BASEADDR
		#define DMA9643_1_BASEADDR      XPAR_AXI_DMAC_0_BASEADDR
	#else
		#define DMA9643_1_BASEADDR      XPAR_AXI_AD9643_DMA_BASEADDR
	#endif
	#define DDR_BASEADDR          	XPAR_DDR_MEM_BASEADDR + 128*1024*1024
	#define UART_BASEADDR         	XPS_UART1_BASEADDR
	#define CFFFT_BASEADDR        	DDR_BASEADDR
	#define DMAFFT_BASEADDR       	DDR_BASEADDR
	#define DDRDAC_BASEADDR       	DDR_BASEADDR + 0x6000000
#else
	#ifdef XPAR_AXI_AD9122_0_BASEADDR
		#define CFAD9122_0_BASEADDR   XPAR_AXI_AD9122_0_BASEADDR
	#else
		#define CFAD9122_0_BASEADDR   XPAR_AXI_AD9122_BASEADDR
	#endif
	#ifdef XPAR_AXI_AD9643_0_BASEADDR
		#define CFAD9643_0_BASEADDR   XPAR_AXI_AD9643_0_BASEADDR
	#else
		#define CFAD9643_0_BASEADDR   XPAR_AXI_AD9643_BASEADDR
	#endif
	#ifdef XPAR_AXI_DMAC_2_BASEADDR
		#define DMA9122_0_BASEADDR    XPAR_AXI_DMAC_0_BASEADDR
		#define DMA9643_0_BASEADDR    XPAR_AXI_DMAC_2_BASEADDR
	#else
		#ifdef XPAR_AXI_DMAC_0_BASEADDR
			#define DMA9122_0_BASEADDR    XPAR_AXI_DMAC_0_BASEADDR
		#else
			#define DMA9122_0_BASEADDR		XPAR_AXI_AD9122_DMA_BASEADDR
		#endif
		#ifdef XPAR_AXI_DMAC_1_BASEADDR
			#define DMA9643_0_BASEADDR    XPAR_AXI_DMAC_1_BASEADDR
		#else
			#define DMA9643_0_BASEADDR    XPAR_AXI_AD9643_DMA_BASEADDR
		#endif
	#endif
	#define IIC_0_BASEADDR        XPAR_AXI_IIC_0_BASEADDR
	#ifndef XPAR_AXI_AD9122_1_BASEADDR
		#ifdef XPAR_AXI_AD9122_0_BASEADDR
			#define XPAR_AXI_AD9122_1_BASEADDR XPAR_AXI_AD9122_0_BASEADDR
		#else
			#define XPAR_AXI_AD9122_1_BASEADDR XPAR_AXI_AD9122_BASEADDR
		#endif
	#endif
	#ifndef XPAR_AXI_AD9643_1_BASEADDR
		#ifdef XPAR_AXI_AD9643_0_BASEADDR
			#define XPAR_AXI_AD9643_1_BASEADDR XPAR_AXI_AD9643_0_BASEADDR
		#else
			#define XPAR_AXI_AD9643_1_BASEADDR XPAR_AXI_AD9643_BASEADDR
		#endif
	#endif
	#define CFAD9122_1_BASEADDR   XPAR_AXI_AD9122_1_BASEADDR
	#define CFAD9643_1_BASEADDR   XPAR_AXI_AD9643_1_BASEADDR
	#ifdef XPAR_AXI_DMAC_3_BASEADDR
		#define DMA9122_1_BASEADDR    XPAR_AXI_DMAC_1_BASEADDR
		#define DMA9643_1_BASEADDR    XPAR_AXI_DMAC_3_BASEADDR
	#else
		#ifdef XPAR_AXI_DMAC_0_BASEADDR
				#define DMA9122_1_BASEADDR    XPAR_AXI_DMAC_0_BASEADDR
		#else
				#define DMA9122_1_BASEADDR    XPAR_AXI_AD9122_DMA_BASEADDR
		#endif
		#ifdef XPAR_AXI_DMAC_1_BASEADDR
				#define DMA9643_1_BASEADDR    XPAR_AXI_DMAC_1_BASEADDR
		#else
				#define DMA9643_1_BASEADDR    XPAR_AXI_AD9643_DMA_BASEADDR
		#endif
	#endif
	#define IIC_1_BASEADDR        XPAR_AXI_IIC_1_BASEADDR
	#ifdef XPAR_DDR3_SDRAM_S_AXI_BASEADDR
		#define DDR_BASEADDR          XPAR_DDR3_SDRAM_S_AXI_BASEADDR + 128*1024*1024
	#else
		#define DDR_BASEADDR          XPAR_AXI_DDR_CNTRL_BASEADDR + 128*1024*1024
	#endif
	#define UART_BASEADDR         XPAR_RS232_UART_1_BASEADDR
	#define CFFFT_BASEADDR        XPAR_AXI_FFT_0_BASEADDR
	#define DMAFFT_BASEADDR       XPAR_AXI_DMA_2_BASEADDR
	#define DDRDAC_BASEADDR       DDR_BASEADDR + 0x00010000
#endif

#define IICSEL_B0LPC_PS7      0x20
#define IICSEL_B1HPC_PS7      0x20
#define IICSEL_B0LPC_AXI      0x04
#define IICSEL_B1HPC_AXI      0x02
#define IICSEL_B0PIC          0x59
#define IICSEL_B1PIC          0x58

/*****************************************************************************/
/************************ Functions Declarations *****************************/
/*****************************************************************************/
/** Initializes the DDS core */
void dds_setup(uint32_t sel, uint32_t f1, uint32_t f2);
/** Verifies the communication with the DAC */
void dac_test(uint32_t sel);
/** Set up the DAC for transmit in SED mode */
void dac_init(uint32_t sel);
/** Pass Data into SED Registers, s0 is I and s1 is Q data*/
void dac_sed(uint32_t sel, uint32_t s0, uint32_t s1);
/** Captures data from the ADC */
void adc_capture(uint32_t sel, uint32_t qwcnt, uint32_t sa);
/** Verifies the communication with the ADC */
void adc_test(uint32_t sel, uint32_t mode, uint32_t format);

#endif /*__TEST_H__*/
