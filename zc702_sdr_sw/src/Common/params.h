/*
 * params.h
 *
 *  Created on: Apr 8, 2013
 *      Author: aharris
 */

#ifndef PARAMS_H_
#define PARAMS_H_

struct radio_params {
	/* Radio 1 Info */
	int radio_1_on;
	int radio_1_freq;
	int radio_1_samp_rate;
	int arb1Length;
	int *idata_1;
	int *qdata_1;

	/* Radio 2 Info */
	int radio_2_on;
	int radio_2_freq;
	int radio_2_samp_rate;
	int *idata_2;
	int *qdata_2;

	/* Transfer Info */
	int numPackets;
	int packetLength;
	int packetsRecved;
};

#endif /* PARAMS_H_ */
