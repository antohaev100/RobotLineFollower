#include "header.h"
car_state state;
bool useLeds;
extern MeUltrasonicSensor zUltraSonicSensor;



static void readLineValue() {
    uint8_t lineValue = zRobotGetLineSensor();
    handleLineValue(lineValue, &state);
}

static void readSensorValue(){
	double sensorValue = zUltraSonicSensor.distanceCmFast(MAX_OBS_DST); //max every 23 ms
    if(sensorValue < MAX_OBS_DST-10){
        state.last_obs_dst = sensorValue;
        //state.obs = where_obs(&state);
        state.obs = OBS_ON_RIGHT;
        state.last_obs_avoid_time = xTaskGetTickCount();
    }
}


static void updateRobotState() {
    updateRobot(&state);
}

static void test(){
    double sensorValue = zUltraSonicSensor.distanceCmFast(20);
    cli();
    Serial.println((unsigned long)sensorValue);
    Serial.flush();
    sei();
}


void setup() {
    state.main = OFF_LINE;
    state.off_line = OFF_RIGHT;
    state.obs = OBS_CLEAR;
    state.last_obs_dst = MAX_OBS_DST;
    useLeds = true;
    
    zInitialize();
    zTaskSetTrace(0);
    //tick is at 10kHz, 1 tick = 0.1ms
    zScheduleTask((void*)readLineValue, (TickType_t)30, (TickType_t)3);  
    zScheduleTask((void*)updateRobotState, (TickType_t)10*10, (TickType_t)6);
    zScheduleTask((void*)readSensorValue, (TickType_t)30, (TickType_t)20);  
    zStart();
}

void loop() {
    //EMPTY
}





