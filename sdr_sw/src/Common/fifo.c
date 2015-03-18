/*
 * filename: fifo.c
 * author: gpark and dcollins3
 * date: Jan 28, 2015
 * brief: AD9122 DAC FIFO functions
 */

#include <stdint.h>
#include <xparameters.h>
#include <xil_io.h>
#include "ad9122.h"
#include "timer.h"
#include "fifo.h"

#define PCORE_VERSION_MAJOR(version)	(version >> 16)

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
* @return None
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
* @return None
******************************************************************************/
void fifo_setup(uint32_t sel)
{
	uint32_t baddr = ((sel == IICSEL_B1HPC_AXI)||(sel == IICSEL_B1HPC_PS7)) ? CFAD9122_1_BASEADDR : CFAD9122_0_BASEADDR;
	u32 rdata;
	u32 dac_clk_int;
	u32 dac_clk_frac;
	float dac_clk;

	xil_printf("Initializing DAC FIFO for radio %d...", sel);

	Xil_Out32((baddr + 0x4040), 0x3); // reset DAC core
	delay_ms(10);
	if (Xil_In32(baddr + 0x405c) == 0x0)
	{
		xil_printf(" Failed!\n\r");
	}
	else
	{
		xil_printf(" OK!\n\r");
	}
	rdata = Xil_In32(baddr + 0x4054);
	dac_clk = (float) rdata;
	rdata = Xil_In32(baddr + 0x4058);
	dac_clk = dac_clk * (float) rdata * (float) 100.0;
	dac_clk = dac_clk / (float) 65536.0;
	dac_clk_int = (u32) dac_clk;
	dac_clk_frac = (dac_clk - (float) dac_clk_int) * 1000;
	xil_printf("dac_setup: dac_clock(%d.%3dMHz)\n\r", dac_clk_int, dac_clk_frac);

	// Set Up DCI delay to 590ps
	delay_ms(10);
	ad9122_write(0x16, 0x01);
	ad9122_read(0x16);

	//dac_fifo_reset(sel);
}

/*****************************************************************************
* @brief Pass Data into if FIFO not full, pass data into fifo data latch,
* 	trigger DCI clockline
*
* @param sel Which radio core is being accessed
* @param s0 I data
* @param s1 Q data
* @return None
*****************************************************************************/
void dac_fifo_insert(uint32_t sel, uint32_t s0, uint32_t s1)
{
		uint32_t baddr;
		//uint32_t rdata;
		uint32_t hdl_version;

		baddr = ((sel == IICSEL_B1HPC_AXI)||(sel == IICSEL_B1HPC_PS7)) ? CFAD9122_1_BASEADDR : CFAD9122_0_BASEADDR;
		hdl_version = Xil_In32(baddr + 0x4000);

		/*
		ad9122_write(0x68, ((s0>> 0) & 0xff));
		ad9122_write(0x69, ((s0>> 8) & 0xff));
		ad9122_write(0x6a, ((s1>> 0) & 0xff));
		ad9122_write(0x6b, ((s1>> 8) & 0xff));
		ad9122_write(0x6c, ((s0>>16) & 0xff));
		ad9122_write(0x6d, ((s0>>24) & 0xff));
		ad9122_write(0x6e, ((s1>>16) & 0xff));
		ad9122_write(0x6f, ((s1>>24) & 0xff));
		*/
		ad9122_write(0x67, 0x00);
		ad9122_write(0x67, 0x80);
		Xil_Out32((baddr + 0x4410), s0); // pattern
		Xil_Out32((baddr + 0x4450), s1); // pattern
		if (PCORE_VERSION_MAJOR(hdl_version) > 7)
		{
			Xil_Out32((baddr + 0x4418), 0x1); // sed sel
			Xil_Out32((baddr + 0x4458), 0x1); // sed sel
			Xil_Out32((baddr + 0x4044), 0x1); // sync
		}
		else
		{
			Xil_Out32((baddr + 0x4048), 0x1); // format, sel
			Xil_Out32((baddr + 0x4044), 0x1); // enable
		}
		delay_ms(10);
		//ad9122_write(0x67, 0xa3);
		//ad9122_write(0x07, 0x1c);
		//delay_ms(100);

		//xil_printf("dac_sed: s0(0x%08x), s1(0x%08x)\n\r", s0, s1);

	return;
}

/*****************************************************************************
* @brief Resets the FIFO 
*
* @param sel Which radio core is being accessed
* @return None
*****************************************************************************/
void dac_fifo_reset(uint32_t sel)
{
	uint8_t depthIn = 0x05;
	int32_t depth;
	int32_t wrdata = 0x0;
	int i=0;
	
	do {
		i++;
		/* fifo init procedure rev. b spec, pg. 34. register definitions found on pg. 26 */
		ad9122_write(AD9122_REG_FIFO_CTRL, depthIn);
		wrdata = ad9122_read(AD9122_REG_FIFO_STATUS_1) | 0x00000001;
		xil_printf("wrdata: 0x%x\n\r", wrdata);
		ad9122_write(AD9122_REG_FIFO_STATUS_1, wrdata);
		while((ad9122_read(AD9122_REG_FIFO_STATUS_1) & 0x00000002) != 2) {
			xil_printf("status_1: 0x%x\n\r", ad9122_read(AD9122_REG_FIFO_STATUS_1));
	        xil_printf("waiting on status 1 soft align ack\n\r");
		}
		ad9122_write(AD9122_REG_FIFO_STATUS_1, ad9122_read(AD9122_REG_FIFO_STATUS_1) & 0xFFFFFFFE);
		while((ad9122_read(AD9122_REG_FIFO_STATUS_1) & 0x00000002) != 0) {
			xil_printf("waiting on status 1 soft align drop\n\r");
		}
		depth = ad9122_read(AD9122_REG_FIFO_STATUS_2);
		if (depth == 3)
			depthIn = 0x06;
		if (depth == 5);
			depthIn = 0x04;
	    xil_printf("end of reset loop\n\r");
	} while (depth != 4);
	xil_printf("finished fifo reset\n\r");
}
