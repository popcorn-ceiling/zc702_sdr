/*
 * params.h
 *
 *  Created on: Apr 8, 2013
 *      Author: aharris
 */

#ifndef PARAMS_H_
#define PARAMS_H_

struct radio_params {
	/* Radio info */
	int radio_on;
	int radio_freq;
	int radio_samp_rate;
	int arbLength;
	int *idata;
	int *qdata;

	/* Transfer Info */
	int numPackets;
	int packetLength;
	int packetsRecved;
};

#endif /* PARAMS_H_ */
