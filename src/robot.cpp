#include "header.h"
#include <Arduino.h>

static void updateRobotOnLine(const car_state* state){
    switch(state->on_line){
        case ON_LEFT:{
            speedup_circle_right(state->speedup_count);
            ledRight(GREEN_C, state->speedup_count);
            return;
        }
        case ON_MIDDLE_FROM_LEFT:{
            speedup_circle_left(state->speedup_count);
            ledFront(GREEN_C, state->speedup_count);
            return;
        }
        case ON_MIDDLE_FROM_RIGHT:{
            speedup_circle_right(state->speedup_count);
            ledFront(GREEN_C, state->speedup_count);
        }
        case ON_RIGHT:{
            speedup_circle_left(state->speedup_count);
            ledLeft(GREEN_C, state->speedup_count);
            return;
        }
    }
}

static void updateRobotOffLine(const car_state* state){
    switch (state->off_line) {
        case OFF_LEFT:{
            circle_right(OFF_LINE_CIRCLE_RADIUS);
            ledRight(BLUE_C);
            return;
        }
        case OFF_RIGHT:{
            circle_left(OFF_LINE_CIRCLE_RADIUS);
            ledLeft(BLUE_C);
            return;
        }
    }
}

static void updateRobotGoodEntry(const car_state* state){
    switch(state->good_entry){
        case ENTRY_GOOD_LEFT:{
            circle_left(GOOD_ENTRY_CIRCLE_RADIUS);
            ledRight(NEON_C);
            return;
        }
        case ENTRY_GOOD_RIGHT:{
            circle_right(GOOD_ENTRY_CIRCLE_RADIUS); 
            ledLeft(NEON_C);
            return;
        }
        case ENTRY_GOOD_UNKNOWN: {
            stop();
            loadingAnimationsLeds(NEON_C);
            return;
        }
    }
}

static void updateRobotBadEntry(const car_state* state){
    switch(state->bad_entry){
        case ENTRY_BAD_LEFT:{
            forward(64);
            ledLeft(ORANGE_C);
            return;
        }
        case ENTRY_BAD_RIGHT:{
            forward(64);
            ledRight(ORANGE_C);
            return;
        }
    }
}

static void updateRobotOverEntry(const car_state* state){
    switch(state->over_entry){
        case ENTRY_OVER_LEFT:{
            turn_left();
            ledBack(ORANGE_C);
            return;
        }
        case ENTRY_OVER_RIGHT:{
            turn_right();
            ledBack(ORANGE_C);
            return;
        }
    }
}


static void updateRobotObs(const car_state* state){
    ledRight(RED_C);
    if(xTaskGetTickCount() - state->last_obs_avoid_time < 1350){ //1500 ticks = 150ms for 60 degree turn
        turn_left();
    } else {
        circle_right(state->last_obs_dst + 25);
    }
}

void updateRobot(const car_state* state){
    if(state->obs != OBS_CLEAR){
        return updateRobotObs(state);
    }
    switch(state->main){
        case ON_LINE:{
            return updateRobotOnLine(state);
        }
        case OFF_LINE:{
            return updateRobotOffLine(state);
        }
        case ENTRY_GOOD:{
            return updateRobotGoodEntry(state);
        }
        case ENTRY_BAD:{
            return updateRobotBadEntry(state);
        }
        case ENTRY_OVER:{
            return updateRobotOverEntry(state);
        }
    }
}