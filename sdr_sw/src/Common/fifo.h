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

#define IICSEL_B0LPC_PS7        0x20
#define IICSEL_B1HPC_PS7        0x20
#define IICSEL_B0LPC_PS7_ZC706  0x40
#define IICSEL_B1HPC_PS7_ZC706  0x40
#define IICSEL_B0LPC_AXI        0x04
#define IICSEL_B1HPC_AXI        0x02
#define IICSEL_B0PIC            0x59
#define IICSEL_B1PIC            0x58

#define AXI_DMAC_REG_IRQ_MASK			0x80
#define AXI_DMAC_REG_IRQ_PENDING		0x84
#define AXI_DMAC_REG_IRQ_SOURCE			0x88

#define AXI_DMAC_REG_CTRL				0x400
#define AXI_DMAC_REG_TRANSFER_ID		0x404
#define AXI_DMAC_REG_START_TRANSFER		0x408
#define AXI_DMAC_REG_FLAGS				0x40c
#define AXI_DMAC_REG_DEST_ADDRESS		0x410
#define AXI_DMAC_REG_SRC_ADDRESS		0x414
#define AXI_DMAC_REG_X_LENGTH			0x418
#define AXI_DMAC_REG_Y_LENGTH			0x41c
#define AXI_DMAC_REG_DEST_STRIDE		0x420
#define AXI_DMAC_REG_SRC_STRIDE			0x424
#define AXI_DMAC_REG_TRANSFER_DONE		0x428
#define AXI_DMAC_REG_ACTIVE_TRANSFER_ID 0x42c
#define AXI_DMAC_REG_STATUS				0x430
#define AXI_DMAC_REG_CURRENT_DEST_ADDR	0x434
#define AXI_DMAC_REG_CURRENT_SRC_ADDR	0x438
#define AXI_DMAC_REG_DBG0				0x43c
#define AXI_DMAC_REG_DBG1				0x440

#define AXI_DMAC_CTRL_ENABLE			(1 << 0)
#define AXI_DMAC_CTRL_PAUSE				(1 << 1)

#define AXI_DMAC_IRQ_SOT				(1 << 0)
#define AXI_DMAC_IRQ_EOT				(1 << 1)


/*****************************************************************************/
/************************ Functions Declarations *****************************/
/*****************************************************************************/
/** Initializes the FIFO core */
void fifo_setup(uint32_t sel);
/** Pass Data into if FIFO not full, pass data into Data clock, trigger DCI line, s0 is I and s1 is Q Data*/
void dac_fifo_insert(uint32_t sel, uint32_t s0, uint32_t s1);
/** Resets the FIFO */
void dac_fifo_reset(uint32_t sel);

#endif /* FIFO_H_ */
