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

int main() {
	//TCPIP STUFF
	struct netif *netif, server_netif;
	struct ip_addr ipaddr, netmask, gw;;
	netif = &server_netif;
	struct radio_params *params = malloc(sizeof(struct radio_params));
	params->radio_1_on=0;
	params->radio_1_freq=909000000;
	params->radio_1_samp_rate=400000000;

	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x02, 0x72, 0xa3 };
	netif = &server_netif;
	init_platform();

	/* initialize IP addresses to be used */
	IP4_ADDR(&ipaddr,147,222,163,30);
	IP4_ADDR(&netmask,255,255,255,0);
	IP4_ADDR(&gw,147,222,163,254);

	xil_printf("\n\rSDR 2014 IS UP AND RUNNING\n\r");
	xil_printf("Initializing LWIP Interface...\n\r");
	//print_app_header();
	lwip_init();

	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
		xil_printf("Error adding N/W interface\n\r");
		return -1;
	}
	netif_set_default(netif);
	platform_enable_interrupts();
	netif_set_up(netif);
	start_application(params);

    int32_t ret;
    int32_t fmcSel;
    XCOMM_DefaultInit defInit = {FMC_LPC,		//fmcPort
    							 XILINX_ZC702,	//carrierBoard
                                 100000000,		//adcSamplingRate
								 400000000,		//dacSamplingRate
								 20000,			//rxGain1000
								 909000000ull, //rxFrequency
								 909000000ull};//txFrequency

    Xil_ICacheEnable();
    Xil_DCacheEnable();

    fmcSel = (defInit.fmcPort == FMC_LPC ? IICSEL_B0LPC_AXI : IICSEL_B1HPC_AXI);

    ret = XCOMM_Init(&defInit);
	if(ret < 0) {
		xil_printf("XCOMM Init Failed!\n\r");
		return 0;
	} else {
		xil_printf("XCOMM Initialized\n\r");
	}

    XCOMM_SetTxFrequency(defInit.txFrequency);

    //xil_printf("\n\rSetting up the FIFO... \n\r");
    //dds_setup(fmcSel, 5, 5);
    fifo_setup(fmcSel);

    xil_printf("\n\rEntering Main Loop.. \n\r");

    // System Main Loop
    int i=0;
    uint32_t time;
    int arb_length=0;
    while(1)
    {
    	// Ethernet Communication
    	xemacif_input(netif);

    	/*xil_printf("packet info:\n\r");
    	xil_printf("   radio on: %d\r\n", params->radio_1_on);
    	xil_printf("   freq: %d\r\n", params->radio_1_freq);
    	xil_printf("   sample rate: %d\r\n", params->radio_1_samp_rate);
    	xil_printf("   arb length: %d\r\n", params->arb1Length);
    	xil_printf("   i dat: %d\r\n", params->idata_1);
    	xil_printf("   q dat: %d\r\n", params->qdata_1);
    	xil_printf("   num packets: %d\r\n", params->numPackets);
    	xil_printf("   packet len: %d\r\n", params->packetLength);
    	xil_printf("   packet recvd: %d\r\n", params->packetsRecved);
		*/

    	// Radio Output
    	if (params->radio_1_on) {
    		if (i==0)
    			//xil_printf("Start of ARB\n\r");
    		time = 1000*((double)1/(double)params->radio_1_samp_rate);
    		delay_ms(time);
    		arb_length = params->arb1Length;
    		dac_fifo_insert(fmcSel, params->idata_1[i], params->qdata_1[i]);
    	}
    	i = (i+1)%arb_length;
    }

    xil_printf("\n\rFinished XCOMM Test Program\n\r");
    cleanup_platform();
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    return 0;
}
