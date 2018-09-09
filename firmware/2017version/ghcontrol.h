// Function headers for ghcontrol.c

#ifndef GHCONTROL_H
	#define GHCONTROL_H

	// CONSTANTS
	#define UPDATE 1000
	#define SENSORS 4
	#define TEMPERATURE 0
	#define HUMIDITY 1
	#define PRESSURE 2
	#define LIGHT 3

	#define NALARMS 9
    #define NOALARMS 0
    #define ALARMNMSZ 18

	// Sense Hat pinbase
	#define HSH_RTC_I2CADR 0x68
	#define HSH_MCP23017_I2CADR 0x20
	#define HSH_PCF8591_I2CADR 0x48
	#define HSH_BME280_I2CADR 0x76
	#define HSH_MCP23017_PINBASE 100
	#define HSH_PCF8591_PINBASE 200
	#define HSH_BME280_PINBASE 300
	//#define HSH_PCF8591_A0IN 3 //A0 = LDR
	#define HSH_PCF8591_A0IN 0  // AIN0 = PHOTORESISTOR
	#define HSH_PCF8591_A1IN 1  // AIN1 = THERMISTOR
	#define HSH_PCF8591_A2IN 2  // AIN2
	#define HSH_PCF8591_A3IN 3  // AIN3 = POT
	//Aout = D1, VCC=D2
	//printf("Photoresistor: %d\t",analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A0IN));
	//printf("Thermistor: %d\n",analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A1IN));
	//printf("AIN2: %d\t",analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A2IN));
	//printf("Potentiometer: %d\n",analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A3IN));


	// Controls
	#define CTEMP 25
	#define CHUMID 55
	#define CLIGHT 255
	#define HEATERON	0
	#define HUMIDIFIERON	1
	#define GHCOFF 2
	#define NORMAL 1
	#define ABNORMAL 0


    // constants
	#define UPPERATEMP 30
	#define LOWERATEMP 10
	#define UPPERAHUMID 70
	#define LOWERAHUMID 25
	#define UPPERAPRESS 1016
	#define LOWERAPRESS 985
	#define UPPERALIGHT 255
	#define LOWERALIGHT 0


    // simulation constants
    #define SIMTEMPERATURE 0
    #define SIMHUMIDITY 0
    #define SIMPRESSURE 0
    #define SIMLIGHT 0

    //reading structure
    typedef struct readings
    {
        time_t rtime;
        double temperature;
        double humidity;
        double pressure;
        double light;
    }reading_s;

    typedef struct setpoints
    {
        double temperature;
        double humidity;
        double light;
    }setpoint_s;

    typedef struct controls
    {
        int heater;
        int humidifier;
        int light;
    }control_s;

    typedef enum { NOALARM, HTEMP, LTEMP, HHUMID, LHUMID, HLIGHT, LLIGHT, HPRESS, LPRESS } alarm_e;

    typedef struct alarmlimits
    {
        double hight;
        double lowt;
        double highh;
        double lowh;
        double highl;
        double lowl;
        double highp;
        double lowp;
    }alarmlimit_s;

    typedef struct alarms
    {
        alarm_e code;
        time_t atime;
        double value;
        struct alarms * next;
    }alarm_s;

	// Function Prototypes
    int GhControllerInit(void);
	double GhGetTemperature(void);
	double GhGetHumidity(void);
	double GhGetPressure(void);
	double GhGetLight(void);
    reading_s GhGetReadings(void);
    setpoint_s GhSetSetpoint(void);
    control_s GhSetControls(setpoint_s target, reading_s rdata);
    alarmlimit_s GhSetAlarmLimits(void);
	alarm_s * GhSetAlarms(alarm_s * head, alarmlimit_s alarmpt, reading_s rdata);
	int GhSetOneAlarm(alarm_e code, time_t atime, double value, alarm_s * head);
    alarm_s * GhClearOneAlarm(alarm_e code, alarm_s * head);
#endif
