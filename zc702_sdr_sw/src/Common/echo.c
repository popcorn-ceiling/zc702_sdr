/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/tcp.h"
#include "params.h"

#include "xcomm.h"

#define SW_RX_FIFO_SIZE 	131072		/* Num of Bytes in the lwip RX Fifo */
#define SW_TX_FIFO_SIZE		8192		/* Num of Bytes in the lwip TX Fifo */
#define MEM_SIZE			1048576		/* Bytesize of FIFO HEAP MEMORY Available */

struct packet_capture {
	int numPackets;
	int packetLength;
	int packetsRecved;
};

int transfer_data() {
	 return 0;
}

void print_app_header()
{
	xil_printf("\n\r\n\r-----lwIP TCP echo server ------\n\r");
	xil_printf("TCP packets sent to port 8080 will be echoed back\n\r");
}

err_t recv_callback(void *arg, struct tcp_pcb *tpcb,
                               struct pbuf *p, err_t err)
{
	struct radio_params *params = arg;
	int message_recvd = 1;
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}

	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);

	/* in this case, we assume that the payload is < TCP_SND_BUF */
	if (tcp_sndbuf(tpcb) > p->len) {
		char* msg = p->payload;
		char * pch;
		pch = strtok(msg," ");

		// TODO: free memory in packet type 0 regardless
		if (pch[0] == '0') { //Handle setFrequency Function
			if (params->idata_1!=NULL)
				free(params->idata_1);
			if (params->qdata_1!=NULL)
				free(params->qdata_1);
			pch = strtok(NULL," ");
			int radioSelect = atoi(pch);
			pch = strtok(NULL," ");
			int frequency = atoi(pch);
			xil_printf('packet freq: %d\n\r', frequency);
			params->radio_1_freq = frequency;
			int returnFreq = XCOMM_SetTxFrequency((uint64_t)(frequency));
			xil_printf("Frequency: %d\n\r",returnFreq);
		} else if (pch[0] == '1') { // Handle setSamplingRate Function
			pch = strtok(NULL," ");
			int radioSelect = atoi(pch);
			pch = strtok(NULL," ");
			int samplingRate = atoi(pch);
			params->radio_1_samp_rate = samplingRate;
			int returnSamplingRate = XCOMM_SetDacSamplingRate((uint64_t)(samplingRate));
			xil_printf("Sampling Rate: %d\n\r", returnSamplingRate);
		} else if (pch[0] == '2') { // Setup arb memory
			params->radio_1_on=0;
			if (params->idata_1==NULL)
				free(params->idata_1);
			if (params->qdata_1==NULL)
				free(params->qdata_1);

			xil_printf("Setting up arb memory buffer\n\r");
			pch = strtok(NULL," ");
			int radioSelect = atoi(pch);
			pch = strtok(NULL," ");
			params->numPackets = atoi(pch);
			pch = strtok(NULL," ");
			params->packetLength = atoi(pch);
			params->arb1Length = params->packetLength*params->numPackets;

			params->idata_1 = malloc(params->numPackets*params->packetLength*sizeof(int));
			params->qdata_1 = malloc(params->numPackets*params->packetLength*sizeof(int));
			if (params->idata_1==NULL) {
				xil_printf("Error allocating memory for i data \n\r");
				xil_printf("len, num = %d, %d\n\r", params->packetLength, params->numPackets);
				return 1;
			}
			if (params->qdata_1==NULL) {
				xil_printf("Error allocating memory for q data \n\r");
				xil_printf("len, num = %d, %d\n\r", params->packetLength, params->numPackets);
				return 1;
			}
			params->packetsRecved = 0;
			xil_printf("Arb incoming with %d packets of size %d\n\r",params->numPackets, params->packetLength);
		} else if (pch[0] == '3') { // Load partial arb array
			int i,idata,qdata;
			pch = strtok(NULL," ");
			int packetID = atoi(pch);
			xil_printf("Receiving Packet %d, accessing memory address: %d\n\r", packetID, packetID*params->packetLength);
			for (i=0; i<params->packetLength; i++) {
				pch = strtok(NULL," ");
				idata = atoi(pch);
				pch = strtok(NULL," ");
				qdata = atoi(pch);
				params->idata_1[packetID*params->packetLength+i] = idata;
				params->qdata_1[packetID*params->packetLength+i] = qdata;
			} params->packetsRecved++;
			if (params->packetsRecved==params->numPackets){
				params->radio_1_on=1;
				xil_printf("Arb received\n\r");
			}
		} else { // Error, command unrecognized
			message_recvd = 0;
		}
		while (pch != NULL) {
			pch = strtok(NULL," ");
		}
		
		if (message_recvd) { // return success
			err = tcp_write(tpcb, p->payload, p->len, 1);
		} else { // return error
			err = tcp_write(tpcb, p->payload, p->len, 1);
		}	
	} else
		xil_printf("no space in tcp_sndbuf\n\r");

	/* free the received pbuf */
	pbuf_free(p);

	return ERR_OK;
}

err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	static int connection = 1;

	/* set the receive callback for this connection */
	tcp_recv(newpcb, recv_callback);

	tcp_arg(newpcb, arg);

	/* increment for subsequent accepted connections */
	connection++;

	return ERR_OK;
}

int start_application(struct radio_params *params_in) {
	struct tcp_pcb *pcb;
	err_t err;
	unsigned port = 8080;

	/* create new TCP PCB structure */
	pcb = tcp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* hand in array pointers */
	tcp_arg(pcb, &*params_in);

	/* listen for connections */
	pcb = tcp_listen(pcb);
	if (!pcb) {
		xil_printf("Out of memory while tcp_listen\n\r");
		return -3;
	}

	/* specify callback to use for incoming connections */
	tcp_accept(pcb, accept_callback);

	xil_printf("TCP echo server started @ port %d\n\r", port);

	return 0;
}
