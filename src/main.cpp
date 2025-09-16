#include "header.h"
car_state state;
bool useLeds;
extern MeUltrasonicSensor zUltraSonicSensor;



static void readLineValue() {
    uint8_t lineValue = zRobotGetLineSensor();
    handleLineValue(lineValue, &state);
}

static void readSensorValue(){
	double sensorValue = zUltraSonicSensor.distanceCmFast(MAX_OBS_DST);
    if(sensorValue < MAX_OBS_DST-OBS_DST_WRONG_MARGIN){
        state.last_obs_dst = sensorValue;
        state.obs = OBS_DANGER;
        state.last_obs_avoid_time = xTaskGetTickCount();
    }
}


static void updateRobotState() {
    updateRobot(&state);
}

void setup() {
    useLeds = true;
    
    zInitialize();
    uint8_t lineValue = zRobotGetLineSensor();
    StateSetup(lineValue, &state);
    zTaskSetTrace(0);
    //tick is at 10kHz, 1 tick = 0.1ms
    zScheduleTask((void*)readLineValue, (TickType_t)40, (TickType_t)3);  
    zScheduleTask((void*)updateRobotState, (TickType_t)100, (TickType_t)7);
    zScheduleTask((void*)readSensorValue, (TickType_t)40, (TickType_t)25);  
    zStart();
}

void loop() {
    //EMPTY
}





