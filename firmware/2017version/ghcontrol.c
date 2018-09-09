#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include "ghcontrol.h"
#include "ghutils.h"
#include "hshbme280.h"
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
        //return GetBME280TempC();
		return analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A1IN)-186.0;
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
