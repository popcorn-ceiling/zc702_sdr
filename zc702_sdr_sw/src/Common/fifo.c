/*
 * fifo.c
 *
 *  Created on: Mar 22, 2013
 *      Author: aharris
 */

#include <stdint.h>
#include <xparameters.h>
#include <xil_io.h>
#include "ad9122.h"
#include "timer.h"
#include "fifo.h"

/*****************************************************************************/
/***************************** External Functions ****************************/
/*****************************************************************************/
extern int32_t ad9122_write(uint8_t registerAddress, uint8_t registerValue);
extern int32_t ad9122_read(uint8_t registerAddress);
extern void xil_printf(const char *ctrl1, ...);

/**************************************************************************//**
* @brief Delays the program execution with the specified number of ms.
*
* @param ns_count Number of ms with which the program must be delayed.
* @return None.
******************************************************************************/
void delay_ms(uint32_t ms_count)
{
#ifdef _XPARAMETERS_PS_H_
	volatile uint32_t i;
	for(i = 0; i < ms_count*1000; i++);
#else
	TIMER0_WAIT(XPAR_AXI_TIMER_0_BASEADDR, ms_count*1000000);
#endif
}

/*****************************************************************************
* @brief Initializes the FIFO core.
*
* @param sel Which radio core is being accessed
* @return None.
******************************************************************************/
void fifo_setup(uint32_t sel)
{
	uint32_t baddr;

	baddr = ((sel == IICSEL_B1HPC_AXI)||(sel == IICSEL_B1HPC_PS7)) ? CFAD9122_1_BASEADDR : CFAD9122_0_BASEADDR;

	Xil_Out32((baddr + 0x04), 0x0);
	Xil_Out32((baddr + 0x04), 0x1);
	Xil_Out32((baddr + 0x20), 0x1111);

	// Set Up DCI delay to 590ps
	ad9122_write(0x16, 0x01);
	ad9122_read(0x16);
	//dac_fifo_reset(sel);
}

/*****************************************************************************
* @brief Verifies the communication with the DAC
*
* @param sel Which radio core is being accessed
* @return None.
******************************************************************************/
void dac_fifo_test(uint32_t sel)
{
	int32_t status;
	status = ad9122_read(AD9122_REG_DATA_REC_STATUS);
	xil_printf("\n\rAD9122_REG_DATA_REC_STATUS: %d\n\r",status);
	status = ad9122_read(AD9122_REG_FIFO_STATUS_1);
	xil_printf("AD9122_REG_FIFO_STATUS_1: %d\n\r",status);
	status = ad9122_read(AD9122_REG_FIFO_STATUS_2);
	xil_printf("AD9122_REG_FIFO_STATUS_2: %d\n\r\n\r",status);
}


/*****************************************************************************
* @brief Pass Data into if FIFO not full, pass data into fifo data latch,
* 	trigger DCI clockline
*
* @param sel Which radio core is being accessed
* @param s0 I data
* @param s1 Q data
* @return None.
*****************************************************************************/
void dac_fifo_insert(uint32_t sel, uint32_t s0, uint32_t s1)
{
	uint32_t baddr = ((sel == IICSEL_B1HPC_AXI)||(sel == IICSEL_B1HPC_PS7)) ? CFAD9122_1_BASEADDR : CFAD9122_0_BASEADDR;
	//ad9122_write(0x68, ((s0>> 0) & 0xff));
	//ad9122_write(0x69, ((s0>> 8) & 0xff));
	//ad9122_write(0x6a, ((s1>> 0) & 0xff));
	//ad9122_write(0x6b, ((s1>> 8) & 0xff));
	//ad9122_write(0x6c, ((s0>>16) & 0xff));
	//ad9122_write(0x6d, ((s0>>24) & 0xff));
	//ad9122_write(0x6e, ((s1>>16) & 0xff));
	//ad9122_write(0x6f, ((s1>>24) & 0xff));
	//ad9122_write(0x67, 0x00);
	//ad9122_write(0x67, 0x80);
	Xil_Out32((baddr + 0x40), s0);
	Xil_Out32((baddr + 0x44), s1);
	Xil_Out32((baddr + 0x04), 0x11);
	Xil_Out32((baddr + 0x04), 0x13);
	return;
}
/*****************************************************************************
* @brief Returns the current phase information stored in the FIFO, 0=EMPTY, 7=FULL
*
* @param sel Which radio core is being accessed
* @return integer phase of FIFO core
*****************************************************************************/
int32_t dac_get_fifo_phase(uint32_t sel)
{
	return ad9122_read(AD9122_REG_FIFO_STATUS_2);
}

/*****************************************************************************
* @brief Resets the FIFO 
*
* @param sel Which radio core is being accessed
* @return integer phase of FIFO core
*****************************************************************************/
void dac_fifo_reset(uint32_t sel)
{
	uint8_t depthIn;
	
	depthIn = 0x05;
	int32_t depth;
	int i=0;
	do {
		i++;
		ad9122_write(AD9122_REG_FIFO_CTRL, depthIn);
		ad9122_write(AD9122_REG_FIFO_STATUS_1, ad9122_read(AD9122_REG_FIFO_STATUS_1)|0x00000001);
		while((ad9122_read(AD9122_REG_FIFO_STATUS_1)&0x00000002)!=2);
		ad9122_write(AD9122_REG_FIFO_STATUS_1, ad9122_read(AD9122_REG_FIFO_STATUS_1)&0xFFFFFFFE);
		while((ad9122_read(AD9122_REG_FIFO_STATUS_1)&0x00000002)!=0);
		depth = ad9122_read(AD9122_REG_FIFO_STATUS_2);
		if (depth==3)
			depthIn = 0x06;
		if (depth==5);
			depthIn = 0x04;
	} while (depth != 4);
}
