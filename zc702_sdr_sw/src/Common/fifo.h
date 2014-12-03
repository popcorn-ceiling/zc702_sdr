/*
 * fifo.h
 *
 *  Created on: Mar 22, 2013
 *      Author: aharris
 */

#ifndef FIFO_H_
#define FIFO_H_

/*****************************************************************************/
/******************* Constants ***********************************************/
/*****************************************************************************/
#ifdef _XPARAMETERS_PS_H_
	#define CFAD9122_0_BASEADDR     XPAR_AXI_AD9122_BASEADDR
	#define CFAD9643_0_BASEADDR     XPAR_AXI_AD9643_BASEADDR
	#define VDMA9122_0_BASEADDR     XPAR_AXI_VDMA_0_BASEADDR
	#define DMA9643_0_BASEADDR      XPAR_AXI_DMAC_0_BASEADDR
	#define CFAD9122_1_BASEADDR     XPAR_AXI_AD9122_BASEADDR
	#define CFAD9643_1_BASEADDR     XPAR_AXI_AD9643_BASEADDR
	#define VDMA9122_1_BASEADDR     XPAR_AXI_VDMA_1_BASEADDR
	#define DMA9643_1_BASEADDR      XPAR_AXI_DMA_1_BASEADDR
	#define DDR_BASEADDR          	XPAR_DDR_MEM_BASEADDR + 128*1024*1024
	#define UART_BASEADDR         	XPS_UART1_BASEADDR
	#define CFFFT_BASEADDR        	DDR_BASEADDR
	#define DMAFFT_BASEADDR       	DDR_BASEADDR
#else
	#define CFAD9122_0_BASEADDR   XPAR_AXI_AD9122_BASEADDR
	#define CFAD9643_0_BASEADDR   XPAR_AXI_AD9643_BASEADDR
	#define VDMA9122_0_BASEADDR   XPAR_AXI_VDMA_0_BASEADDR
	#define DMA9643_0_BASEADDR    XPAR_AXI_DMAC_0_BASEADDR
	#define IIC_0_BASEADDR        XPAR_AXI_IIC_0_BASEADDR

	#ifndef XPAR_AXI_DAC_4D_2C_1_BASEADDR
		#define XPAR_AXI_DAC_4D_2C_1_BASEADDR XPAR_AXI_AD9122_BASEADDR
	#endif
	#ifndef XPAR_AXI_ADC_2C_1_BASEADDR
		#define XPAR_AXI_ADC_2C_1_BASEADDR XPAR_AXI_AD9643_BASEADDR
	#endif
	#define CFAD9122_1_BASEADDR   XPAR_AXI_DAC_4D_2C_1_BASEADDR
	#define CFAD9643_1_BASEADDR   XPAR_AXI_ADC_2C_1_BASEADDR
	#define VDMA9122_1_BASEADDR   XPAR_AXI_VDMA_1_BASEADDR
	#define DMA9643_1_BASEADDR    XPAR_AXI_DMA_0_BASEADDR
	#define IIC_1_BASEADDR        XPAR_AXI_IIC_1_BASEADDR

	#define DDR_BASEADDR          XPAR_DDR3_SDRAM_S_AXI_BASEADDR + 128*1024*1024
	#define UART_BASEADDR         XPAR_RS232_UART_1_BASEADDR
	#define CFFFT_BASEADDR        XPAR_AXI_FFT_0_BASEADDR
	#define DMAFFT_BASEADDR       XPAR_AXI_DMA_2_BASEADDR
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
/** Initializes the FIFO core */
void fifo_setup(uint32_t sel);
/** Verifies the communication with the DAC */
void dac_test(uint32_t sel);
/** Pass Data into if FIFO not full, pass data into Data clock, trigger DCI line, s0 is I and s1 is Q Data*/
void dac_fifo_insert(uint32_t sel, uint32_t s0, uint32_t s1);
/** Returns the current phase information stored in the FIFO, 0=EMPTY, 7=FULL */
int32_t dac_get_fifo_phase(uint32_t sel);
/** Resets the FIFO */
void dac_fifo_reset(uint32_t sel);

#endif /* FIFO_H_ */
