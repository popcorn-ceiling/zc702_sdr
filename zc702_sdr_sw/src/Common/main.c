/**************************************************************************//**
*   @file   main.c
*   @brief  XCOMM and TCPIP Main Program Definition.
*   @author Alex Harris (aharris)
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

void lwip_init();
void print_app_header();
int start_application();
extern void xil_printf(const char *ctrl1, ...);
extern void delay_ms(uint32_t ms_count);

extern uint16_t sine_lut_i[32];
extern uint16_t sine_lut_q[32];

int main() {
    int32_t ret;

	/* TCPIP stuff */
	struct netif *netif, server_netif;
	struct ip_addr ipaddr, netmask, gw;;
	netif = &server_netif;
	struct radio_params *params0 = malloc(sizeof(struct radio_params));
	//struct radio_params *params1 = malloc(sizeof(struct radio_params));
	params0->radio_on=0; // TODO: move params defaults to function
	params0->radio_freq=909000000;
	params0->radio_samp_rate=400000000;
	params0->idata = NULL;
	params0->qdata = NULL;

	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x02, 0x72, 0xa3 };
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
	start_application(params0); // why need params?

	XCOMM_Version boardVersion;
    XCOMM_DefaultInit defInit = {FMC_LPC,		//fmcPort0
    							 XILINX_ZC702,	//carrierBoard
                                 100000000,		//adcSamplingRate
								 400000000,		//dacSamplingRate
								 20000,			//rxGain2000
								 909000000ull, 	//rxFrequency
								 909000000ull};	//txFrequency

    Xil_ICacheEnable();
    Xil_DCacheEnable();

    int32_t fmcSelDefault = (defInit.fmcPort == FMC_LPC ? IICSEL_B0LPC_PS7 : IICSEL_B1HPC_PS7);

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

    xil_printf("Getting XCOMM Revision...");
	boardVersion = XCOMM_GetBoardVersion(XCOMM_ReadMode_FromHW);
	if(boardVersion.error == -1)
	{
		xil_printf(" Failed!\n\r");
	}
	else
	{
		xil_printf(" OK!\n\rBoard Revision: %s\n\r", boardVersion.value);
	}

	xil_printf("Initializing XCOMM...");
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

    fifo_setup(IICSEL_B0LPC_PS7); /* FMC0 */
    fifo_setup(IICSEL_B1HPC_PS7); /* FMC1 */

    // System Main Loop
    int i = 0;
    uint32_t time;
    int arb_length = 0;

    xil_printf("Ready to receive packets\n\r");
    while(1)
    {
    	/* Ethernet Communication */
    	xemacif_input(netif);

    	/* Radio Output */
    	if (params0->radio_on) {
    		time = 1000*((double)1/(double)params0->radio_samp_rate);
    		delay_ms(time);
    		arb_length = params0->arbLength;
    		//dac_fifo_insert(params0->fmcSel, params0->idata[i], params0->qdata[i]);
    		dac_fifo_insert(fmcSelDefault, params0->idata[i], params0->qdata[i]);
    		//dac_fifo_insert(fmcSelDefault, sine_lut_i[i], sine_lut_q[i]);
    	}
    	i = (i+1)%arb_length;
    }

    xil_printf("\n\rFinished XCOMM Test Program\n\r");
    cleanup_platform();
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    return 0;
}
