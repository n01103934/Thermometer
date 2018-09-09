#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wiringPi.h>
#include "ghcontrol.h"
#include "ghutils.h"

void DisplayName(void)
{
	printf("\n Hello my name is:\t Go\n");
	printf("\n My student number is: N12345678\n");
}

int GetRandom(int range)
{
	return rand() % range;
}

void GhDisplayReadings(time_t *readt, double greads[SENSORS])
{
	*readt = time(NULL);
	printf("\n%s", ctime(readt));
	//printf("Readings\tTemperature: %3.1lfC\tHumidity: %3.1lf%%\tLights: %3.01lflux\tPressure: %5.1lfmB", greads[TEMPERATURE], greads[HUMIDITY], greads[LIGHT], greads[PRESSURE]);
	printf("Readings\tTemperature: %3.1lfC\tLights: %3.01lflux", greads[TEMPERATURE], greads[LIGHT]);
}

void GhDisplaySetpoints(void)
{
	//printf("\nSetpoints\tTemperature: %dC\tHumidity: %d%%\tLights: %d lux", CTEMP, CHUMID, CLIGHT);
	printf("\nSetpoints\tTemperature: %dC\tLights: %d lux", CTEMP, CLIGHT);
}

void GhDisplayControls(int * heater, int * humidifier, int * light)
{
	//printf("\nControls\tHeater: %d\t\tHumidifier: %d\tLights: %d\n", *heater, *humidifier, *light);
	printf("\nControls\tHeater: %d\t\tLights: %d\n", *heater, *light);
}

void GhDelay(int milliseconds)
{
	long wait;
	clock_t now,start;

	wait = milliseconds*(CLOCKS_PER_SEC/1000);
	start = clock();
	now = start;
	while( (now-start) < wait)
	{
		now = clock();
	}
}

void SetLED(int colour)
{
	pinMode(GEN00, OUTPUT);
	pinMode(GEN01, OUTPUT);

    switch(colour) {
        case RED :
        digitalWrite(GEN00, HIGH);
        break;
        case GREEN :
        digitalWrite(GEN01,HIGH);
        break;
        case NOCOLOUR :
        digitalWrite(GEN00, LOW);
        digitalWrite(GEN01, LOW);
        break;
    }

}

int GhLogData(char * fname, reading_s ghdata)
{
    FILE *fp;
    char ltime[25] = "";
    fp = fopen(fname, "a");
    if(fp == NULL)
    {
        printf("\nCan't open file, data not retrieved!\n");
        return 0;
    }
    strcpy(ltime,ctime(&ghdata.rtime));
    ltime[3] = ',';
    ltime[7] = ',';
    ltime[10] = ',';
    ltime[19] = ',';
    fprintf(fp, "\n%.24s,%3.1lf,%3.1lf.%5.1lf,%3.0lf", ltime,ghdata.temperature,ghdata.humidity,ghdata.pressure,ghdata.light);
    fclose(fp);
    return 1;
}

int GhSaveSetpoints(char * fname, struct setpoints spts)
{
    FILE *fp;
    fp = fopen(fname, "w");
    if(fp == NULL)
    {
        return 0;
    }
    fwrite(&spts, sizeof(spts), 1, fp);
    fclose(fp);
    return 1;
}

struct setpoints GhRetrieveSetpoints(char * fname)
{
    struct setpoints spts = {0.0};
    FILE *fp;
    fp = fopen(fname, "r");
    if(fp == NULL)
    {
        return spts;
    }
    fread(&spts, sizeof(spts), 1, fp);
    fclose(fp);
    return spts;
}

double PaTomB(double pa)
{
    return pa / 100.0;
}
