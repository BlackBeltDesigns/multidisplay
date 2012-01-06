/*
 * RPMBoostController.h
 *
 *  Created on: 05.11.2011
 *      Author: bofh
 */

#ifndef RPMBOOSTCONTROLLER_H_
#define RPMBOOSTCONTROLLER_H_

#include "MultidisplayDefines.h"
#include "PID_v1.h"
#include "util.h"

class Map16x1;
class Map16x1Double;

#define BOOSTLIMIT 1.7
#define PID_ACTIVATION_THRESHOLD 0.2

class RPMBoostController {
public:
	RPMBoostController();
	void myconstructor ();

	void serialSendDutyMap ( uint8_t gear, uint8_t mode, uint8_t serial );
	void serialSendSetpointMap ( uint8_t gear, uint8_t mode, uint8_t serial );

	void setDutyMap ( uint8_t gear, uint8_t mode, uint8_t *data );
	void setSetpointMap ( uint8_t gear, uint8_t mode, uint16_t *data );

	void loadMapsFromEEprom ();
	void writeMapsToEEprom ();
	void loadParamsFromEEprom ();
	void writeParamsToEEprom ();

	void toggleMode (uint8_t nmode);
	void compute ();

	uint8_t mode;
	Map16x1* highboost_duty_cycle[GEARS];
	Map16x1Double* highboost_pid_boost[GEARS];

	Map16x1* lowboost_duty_cycle[GEARS];
	Map16x1Double* lowboost_pid_boost[GEARS];

	//! output which sould be written to N75
	double boostOutput;

	uint8_t cur_gear;
	uint8_t cur_idx;

	//FIXME unused
	uint8_t n75_manual_normal;
	uint8_t n75_manual_race;

	double req_Boost_PWM;
	double req_Boost;

	PID *pid;
	double pidBoostSetPoint;

	bool usePID;

	//! output from PID
	double pidBoostOutput;

	/*
	 * aggressive PID Settings if the gap to the setpoint is greater
	 */
	double aKp, aKi, aKd;
	double apidActivationThresholdFactor;
	/*
	 * conservative PID Settings if we're near to the setpoint setpoint
	 */
	double cKp, cKi, cKd;
	double cpidActivationThresholdFactor;

};

extern RPMBoostController boostController;

#endif /* RPMBOOSTCONTROLLER_H_ */
