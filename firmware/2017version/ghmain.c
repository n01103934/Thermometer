// lab05b.c : Defines the entry point for the console application.
#include <stdio.h>
//#include <stdlib.h>
#include <time.h>
#include "ghcontrol.h"
#include "ghutils.h"
#include "hshbme280.h"
#include <wiringPi.h>
//#include <pcf8591.h>

int main(void)
{
	//Initialization Section
	srand((unsigned) time(NULL));
	if(GhControllerInit()==ABNORMAL)
		GhControllerShutdown(ABNORMAL);
	//GhSetSetpoints();
	time_t current;
	double creadings[SENSORS]={0.0,0.0,0.0,0.0};

	reading_s creading_s = {0};
	setpoint_s sets = {0};
	control_s ctrl = {0};
	alarmlimit_s alimits = {0};

	int tempc;
	int humidc;
	int lightc;

	// Control Loop - FIRST SET OF READINGS ARE NOT CORRECT
	while (1)
	{
		pinMode(HSH_PCF8591_PINBASE, OUTPUT);
		analogWrite(HSH_PCF8591_PINBASE,0);
		delay(1000);
		analogWrite(HSH_PCF8591_PINBASE,127);
		pinMode(HSH_PCF8591_PINBASE, INPUT);
		
		printf("Greenhouse Control Loop");

		//GhGetReadings(&current,creadings);
		creading_s = GhGetReadings();
		creadings[TEMPERATURE]=creading_s.temperature;
		creadings[HUMIDITY]=creading_s.humidity;
		creadings[PRESSURE]=creading_s.pressure;
		creadings[LIGHT]=creading_s.light;
		GhDisplayReadings(&current,creadings);

		//logged = GhLogData("ghdata.txt", creadings);
		//alimits = GhSetAlarmLimits();
		//arecord = GhSetAlarms(arecord,alimits,creadings);

		sets = GhSetSetpoint();
		GhDisplaySetpoints();

		//GhSetControls(&tempc,&humidc,&lightc,creadings);
		ctrl = GhSetControls(sets, creading_s);
		//GhDisplayControls(&tempc,&humidc,&lightc);
		GhDisplayControls(&ctrl.heater,&ctrl.humidifier,&ctrl.light);

		printf("Delaying %d seconds prior to repeating\n\n",UPDATE/1000);
		//if(digitalRead (HSH_MCP23017_PINBASE+GHCOFF))
		//	break;
		GhDelay(UPDATE);
	}
	//printf("\nPress enter to exit");
	//getchar();
	return GhControllerShutdown(NORMAL);
}

