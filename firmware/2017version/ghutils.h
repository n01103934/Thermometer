// Function headers for ghutils.c

#ifndef GHUTILS_H
	#define GHUTILS_H

	// CONSTANTS
	#define TRIALS 1000
	#define SIDES 6

	#define SENSORS 4
	#define TEMPERATURE 0
	#define HUMIDITY 1
	#define PRESSURE 2
	#define LIGHT 3

	#define CTEMP 25
	#define CHUMID 55
	#define CLIGHT 255

    // LED pins
	#define GEN00 0
	#define GEN01 1

    typedef enum {NOCOLOUR, RED, YELLOW, GREEN} ledcolour_e;

    setpoint_s GhRetrieveSetpoints(char * fname);

	// FUNCTIONS
	//old functions

	void DisplayName(void);
	int GetRandom(int range);

	//new functions
	void GhDisplayReadings(time_t *readt, double greads[SENSORS]);
	void GhDisplaySetpoints(void);
	void GhDisplayControls(int * heater, int * humidifier, int * light);
	void GhDelay(int milliseconds);

	//lab05 Functions
	void SetLED(int colour);

	//lab08 functions
    int GhLogData(char * fname, reading_s ghdata);
    int GhSaveSetpoints(char * fname, setpoint_s spts);
    double PaTomB(double pa);
#endif
