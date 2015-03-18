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

/* This is where the magic happens */
err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct radio_params *params = arg;
	int message_recvd = 1;
	int arb_mem_size = -1;
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

		if (pch[0] == '0') { // Init packet
			params->radio_on = 0;
			if (params->idata!=NULL)
				free(params->idata);
			if (params->qdata!=NULL)
				free(params->qdata);

			/* Radio select */
			pch = strtok(NULL," ");
			int radioSelect = atoi(pch);
			params->radio_num = radioSelect;
			xil_printf("    Arb for radio %d\n\r", radioSelect);
			pch = strtok(NULL," ");

			/* Tx frequency */
			int frequency = atoi(pch);
			params->radio_freq = frequency;
			int returnFreq = XCOMM_SetTxFrequency((uint64_t)(frequency));
			xil_printf("        Frequency: %d\n\r",returnFreq);

			/* Sample rate */
			pch = strtok(NULL," ");
			int samplingRate = atoi(pch);
			params->radio_samp_rate = samplingRate;
			//int returnSamplingRate = XCOMM_SetDacSamplingRate((uint64_t)(samplingRate));
			xil_printf("        Sampling Rate: %d\n\r", samplingRate);

			/* Setup arb memory */
			pch = strtok(NULL," ");
			params->numPackets = atoi(pch);
			pch = strtok(NULL," ");
			params->packetLength = atoi(pch);
			params->arbLength = params->packetLength*params->numPackets;

			arb_mem_size = params->numPackets * params->packetLength*sizeof(int);
			params->idata = malloc(arb_mem_size);
			params->qdata = malloc(arb_mem_size);
			if (params->idata==NULL) {
				xil_printf("Error allocating memory for idata \n\r");
				xil_printf("len, num, mem_size = %d, %d, %d\n\r", params->packetLength, params->numPackets, arb_mem_size);
			}
			if (params->qdata==NULL) {
				xil_printf("Error allocating memory for qdata \n\r");
				xil_printf("len, num, mem_size = %d, %d, %d\n\r", params->packetLength, params->numPackets, arb_mem_size);
			}
			params->packetsRecved = 0;
			xil_printf("    Arb incoming with %d packets of size %d\n\r",params->numPackets, params->packetLength);

		} else if (pch[0] == '1') { // Load partial arb array
			int i,idata,qdata;
			pch = strtok(NULL," ");
			int packetID = atoi(pch);
			xil_printf("        Receiving Packet %d, accessing memory address: %d\n\r", packetID, packetID*params->packetLength);
			if (params->idata==NULL || params->qdata==NULL) {
				xil_printf("    Memory allocation error - skipping data packet\r\n");
				return 1;
			}
			for (i=0; i<params->packetLength; i++) {
				pch = strtok(NULL," ");
				idata = atoi(pch);
				pch = strtok(NULL," ");
				qdata = atoi(pch);
				params->idata[packetID*params->packetLength+i] = idata;
				params->qdata[packetID*params->packetLength+i] = qdata;
			} params->packetsRecved++;
			if (params->packetsRecved==params->numPackets){
				params->radio_on=1; // HACK
				xil_printf("    Arb received. Transmitting on radio %d\n\r\n\r", params->radio_num);
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
