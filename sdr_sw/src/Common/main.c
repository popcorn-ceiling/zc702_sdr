/**************************************************************************//**
*   @file   main.c
*   @brief  XCOMM and TCPIP Main Program Definition.
*   @author Dan Collins and Garion Park
*
**************************************************************************/

/*****************************************************************************/
/***************************** Include Files *********************************/
/*****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "xil_cache.h"
#include "xcomm.h"
#include "xparameters.h"
#include "params.h"
#include "fifo.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"

#include "dac_core.h"

void lwip_init();
void print_app_header();
int start_application();
extern void xil_printf(const char *ctrl1, ...);
extern void delay_ms(uint32_t ms_count);

extern uint16_t sine_lut_i[32];
extern uint16_t sine_lut_q[32];

#define FREQ 909000000
#define SAMP 400000000

void radio_param_init(struct radio_params *param)
{
	*param = (struct radio_params){0, 0, FREQ, SAMP, 0, NULL, NULL, 0, 0, 0};
	return;
}

int main() {
    int32_t ret;

	/* TCPIP stuff */
	struct netif *netif, server_netif;
	struct ip_addr ipaddr, netmask, gw;;
	struct radio_params *params0 = malloc(sizeof(struct radio_params));
	//struct radio_params *params1 = malloc(sizeof(struct radio_params));

	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x02, 0x72, 0xa3 };

	radio_param_init(params0);
	//radio_param_init(params1);

	netif = &server_netif;
	init_platform();

	/* initialize IP addresses to be used */
	IP4_ADDR(&ipaddr,147,222,163,30);
	IP4_ADDR(&netmask,255,255,255,0);
	IP4_ADDR(&gw,147,222,163,254);

	xil_printf("\n\rSDR 2015 is alive\n\r");
	lwip_init();

	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
		xil_printf("Error adding network interface\n\r");
		return -1;
	}
	netif_set_default(netif);
	platform_enable_interrupts();
	netif_set_up(netif);
	start_application(params0);

	XCOMM_Version boardVersion;
    XCOMM_DefaultInit defInit = {FMC_LPC,		//fmcPort0
    							 XILINX_ZC702,	//carrierBoard
                                 100000000,		//adcSamplingRate
                                 400000000,		//dacSamplingRate400000000
								 20000,			//rxGain2000
								 909000000ull, 	//rxFrequency
								 909000000ull};	//txFrequency

    Xil_ICacheEnable();
    Xil_DCacheEnable();

    params0->radio_num = (defInit.fmcPort == FMC_LPC ? IICSEL_B0LPC_PS7 : IICSEL_B1HPC_PS7);

    int baddr = ((params0->radio_num == IICSEL_B1HPC_AXI)||(params0->radio_num == IICSEL_B1HPC_PS7)) ? DMA9122_1_BASEADDR : DMA9122_0_BASEADDR;

    xil_printf("\n\rInitializing XCOMM I2C...");
    ret = XCOMM_InitI2C(&defInit);
    if(ret < 0)
    {
    	xil_printf(" Failed!\n\r");
    	return 0;
    }
    else
    {
    	xil_printf(" OK!\n\r");
    }

	xil_printf("Initializing XCOMM radio...");
    ret = XCOMM_Init(&defInit);
	if(ret < 0) {
		xil_printf(" Failed!\n\r");
		return 0;
	} else {
		xil_printf(" OK!\n\r");
	}

	xil_printf("Initializing the Tx path...");
	ret = XCOMM_InitTx(&defInit);
	if(ret < 0)
	{
		xil_printf(" Failed!\n\r");
		return 0;
	}
	else
	{
		xil_printf(" OK!\n\r");
	}

    xil_printf("Getting XCOMM Revision...");
	boardVersion = XCOMM_GetBoardVersion(XCOMM_ReadMode_FromHW);
	if(boardVersion.error == -1)
	{
		xil_printf(" Failed!\n\r");
	}
	else
	{
		xil_printf(" OK!\n\rBoard Rev: %s\n\r", boardVersion.value);
	}

    /* System Main Loop */
    int i = 0;
    int arb_length = 0;
    uint32_t time;

    xil_printf("Ready to receive packets\n\r");
    while(1)
    {
    	/* Ethernet Communication */
    	xemacif_input(netif);

    	/* WARNING! The following is no longer used. It has been repalced with starting the
    	 * DMA engine in echo.c. Leaving it in for posterity.
    	 */

    	/* Radio Output */
    	/*
    	if (params0->radio_on) {
    		time = 1000*((double)1/(double)params0->radio_samp_rate);
    		//time = 1000*((double)1/(double)samp);
    		delay_ms(time);
    		arb_length = params0->arbLength;
    		dac_fifo_insert(params0->radio_num, params0->idata[i], params0->qdata[i]);
    	}
    	i = (i+1)%arb_length;
    	*/
    }

    xil_printf("\n\rFinished XCOMM Test Program\n\r");
    cleanup_platform();
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    return 0;
}
