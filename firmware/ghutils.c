#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wiringPi.h>
#include "ghutils.h"
#include "hshbme280.h"

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
	//printf("Readings\tTemperature: %3.1lfC\tLights: %3.01lflux", greads[TEMPERATURE], greads[LIGHT]);
	double light=greads[LIGHT];
	double atemp=greads[ANALOGTEMPE];
	double tempc=greads[TEMPERATURE];
	double humid=greads[HUMIDITY];
	double press=greads[PRESSURE];
	//printf("Readings\tTemperature: %3.1lfC\tLights: %3.01lflux\n", tempc, light);
//345678911234567892123456789312345678941234567895123456789612345678971234567898	
	printf(  "Light:       %5.1flux ", light);
	for (int numbar=49;numbar>=0;numbar--){
		if ((light/5.0)>numbar)
			printf("*");
	}
	printf("\nAnalog Temp: %5.1fC   ", atemp);
	for (int numbar=49;numbar>=0;numbar--){
		if ((atemp*5.0-18.0*5.0)>numbar){
			printf("*");
		}
	}
	printf("\nTemperature: %5.1fC   ", tempc);
	for (int numbar=49;numbar>=0;numbar--){
		if ((tempc*5.0-18.0*5.0)>numbar){
			printf("*");
		}
	}
	printf("\nHumidity:    %5.1f%%   ", humid);
	for (int numbar=49;numbar>=0;numbar--){
		if ((humid/2.0)>numbar)
			printf("*");
	}
	printf("\nPressure:    %5.1fmB  ", press);
	for (int numbar=49;numbar>=0;numbar--){
		if ((press-800.0)>numbar)
			printf("*");
	}
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

const char alarmnames[NALARMS][ALARMNMSZ] = {"No Alarms","High Temperature", "Low Temperature", "High Humidity",
"Low Humidity", "High Light", "High Pressure", "Low Pressure"};

int GhControllerInit(void)
{
	wiringPiSetup();

	mcp23017Setup(HSH_MCP23017_PINBASE, HSH_MCP23017_I2CADR);
	pcf8591Setup(HSH_PCF8591_PINBASE, HSH_PCF8591_I2CADR);
    BME280Setup();
	// Setup Control Indicators
	pinMode(HSH_MCP23017_PINBASE+HEATERON, OUTPUT);
	pinMode(HSH_MCP23017_PINBASE+HUMIDIFIERON, OUTPUT);
	pinMode(HSH_MCP23017_PINBASE+GHCOFF, INPUT);

    SetLED(GREEN);

	return NORMAL;
}

int GhControllerShutdown(int status)
{
	digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
	digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);

	if(!status)
	{
		SetLED(RED);
	} else {
		SetLED(NOCOLOUR);
	}
}

reading_s GhGetReadings(void)
{
    reading_s now = {0};

    now.rtime = time(NULL);
    now.temperature = GhGetTemperature();
    now.analogtempe = GhGetAnalogTempe();
    now.humidity = GhGetHumidity();
    now.pressure = GhGetPressure();
    now.light = GhGetLight();
    return now;
}

setpoint_s GhSetSetpoint(void)
{
    setpoint_s cpoints = {0};
    cpoints = GhRetrieveSetpoints("setpoints.dat");
    if(cpoints.temperature == 0)
    {
        cpoints.temperature = CTEMP;
        cpoints.humidity = CHUMID;
        cpoints.light = CLIGHT;
        GhSaveSetpoints("setpoints.dat", cpoints);
    }
    return cpoints;
}

control_s GhSetControls(setpoint_s target, reading_s rdata)
{
    control_s cset;
    if(rdata.temperature < target.temperature)
    {
        cset.heater = 1;
        digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 1);
    } else {
        cset.heater = 0;
        digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
    }
    if(rdata.humidity < target.humidity)
    {
        cset.humidifier = 1;
        digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 1);
    } else {
        cset.humidifier = 0;
        digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);
    }
    if(rdata.light <= target.light)
    {
        cset.light = target.light - rdata.light;
    }
    return cset;

}

alarmlimit_s GhSetAlarmLimits(void)
{
    alarmlimit_s calarm;
    calarm.hight = UPPERATEMP;
    calarm.lowt = LOWERATEMP;
    calarm.highh = UPPERAHUMID;
    calarm.lowh = LOWERAHUMID;
    calarm.highl = UPPERALIGHT;
    calarm.lowl = LOWERAHUMID;
    calarm.highp = UPPERAPRESS;
    calarm.lowp = LOWERAPRESS;
    return calarm;
}

int GhSetOneAlarm(alarm_e code, time_t atime, double value, alarm_s * head)
{
    alarm_s * last;
    alarm_s * cur;

    cur = head;
    if(cur->code != 0)
    {
        while(cur !=  NULL)
        {
            if(cur->code == code)
            {
                return 0;
            }
            last = cur;
            cur = cur->next;
        }
        cur = (alarm_s *)calloc(1, sizeof(alarm_s));
        last->next = cur;
        if(cur == NULL)
        {
            return 0;
        }
    }
    cur->code = code;
    cur->atime = atime;
    cur->value = value;
    cur->next = NULL;
    return 1;
}

alarm_s * GhClearOneAlarm(alarm_e code, alarm_s * head)
{
    alarm_s * cur;
    alarm_s * last = NULL;
    cur = last = head;

    if(cur->code == code && cur->next == NULL)
    {
        cur->code = NOALARM;
        return head;
    }

    if(cur-> code == code && cur->next != NULL)
    {
        head = cur->next;
        free(cur);
        return head;
    }

    while(cur != NULL)
    {
        if(cur->code == code)
        {
            last->next = cur->next;
            free(cur);
        }
        last = cur;
        cur = cur->next;
    }
    return head;
}

alarm_s * GhSetAlarms(alarm_s * head, alarmlimit_s alarmpt, reading_s rdata)
{

    if(rdata.temperature >= alarmpt.hight)
    {
        GhSetOneAlarm(HTEMP,rdata.rtime,rdata.temperature,head);
    }
    else
    {
        head = GhClearOneAlarm(HTEMP,head);
    }
    return head;
    if(rdata.temperature <= alarmpt.lowt)
    {
        GhSetOneAlarm(LTEMP,rdata.rtime,rdata.temperature,head);
    }
    else
    {
        head = GhClearOneAlarm(LTEMP,head);
    }
    return head;
    if(rdata.humidity >= alarmpt.highh)
    {
        GhSetOneAlarm(HHUMID,rdata.rtime,rdata.humidity,head);
    }
    else
    {
        head = GhClearOneAlarm(HHUMID,head);
    }
    return head;
    if(rdata.humidity <= alarmpt.lowh)
    {
        GhSetOneAlarm(LHUMID,rdata.rtime,rdata.humidity,head);
    }
    else
    {
        head = GhClearOneAlarm(LHUMID, head);
    }

    if(rdata.light >= alarmpt.highl)
    {
        GhSetOneAlarm(HLIGHT,rdata.rtime,rdata.light,head);
    }
    else
    {
        head = GhClearOneAlarm(HLIGHT,head);
    }
    return head;
    if(rdata.light <= alarmpt.lowl)
    {
        GhSetOneAlarm(LLIGHT,rdata.rtime,rdata.light,head);
    }
    else
    {
        head = GhClearOneAlarm(LLIGHT,head);
    }
    return head;
    if(rdata.pressure >= alarmpt.highp)
    {
        GhSetOneAlarm(HPRESS,rdata.rtime,rdata.pressure,head);
    }
    else
    {
        head = GhClearOneAlarm(HPRESS,head);
    }
    return head;
    if(rdata.pressure <= alarmpt.lowp)
    {
        GhSetOneAlarm(LPRESS,rdata.rtime,rdata.pressure,head);
    }
    else
    {
        head = GhClearOneAlarm(HTEMP,head);
    }
    return head;
}

double GhGetTemperature(void)
{
    #if SIMTEMPERATURE
        return GetRandom((UPPERATEMP - LOWERATEMP) + LOWERATEMP);
    #else
        return GetBME280TempC();
    #endif

}

double GhGetAnalogTempe(void)
{
    #if SIMTEMPERATURE
        return GetRandom((UPPERATEMP - LOWERATEMP) + LOWERATEMP);
    #else
	return 230.0-analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A1IN);
    #endif

}

double GhGetHumidity(void)
{
    #if SIMHUMIDITY
        return GetRandom((UPPERAHUMID - LOWERAHUMID) + LOWERAHUMID);
    #else
        return GetBME280Humidity();
    #endif // SIMHUMIDITY
}

double GhGetPressure(void)
{
    #if SIMPRESSURE
        return GetRandom((UPPERAPRESS - LOWERAPRESS) + LOWERAPRESS);
    #else
        return PaTomB(GetBME280Pressure());
    #endif // SIMPRESSURE
}

double GhGetLight(void)
{
    #if SIMLIGHT
        return 125;
    #else
        return 255-analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A0IN);
    #endif // SIMLIGHT
}
