#include "header.h"
#include <Arduino.h>

static void updateRobotOnLine(const car_state* state){
    switch(state->on_line){
        case ON_LEFT:{
            circle_right(ON_LINE_CIRCLE_RADIUS);
            ledRight(GREEN_C);
            return;
        }
        case ON_MIDDLE_FROM_LEFT:case ON_MIDDLE_FROM_RIGHT:{
            forward(255);
            ledFront(GREEN_C);
            return;
        }
        case ON_RIGHT:{
            circle_left(ON_LINE_CIRCLE_RADIUS);
            ledLeft(GREEN_C);
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
        case OFF_UNKNOWN:{
            stop();
            loadingAnimationsLeds(BLUE_C);
            return;
        }
    }
}

static void updateRobotGoodEntry(const car_state* state){
    switch(state->good_entry){
        case ENTRY_GOOD_LEFT:{
            circle_left(OFF_LINE_CIRCLE_RADIUS);
            ledRight(NEON_C);
            return;
        }
        case ENTRY_GOOD_RIGHT:{
            circle_right(OFF_LINE_CIRCLE_RADIUS);
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
            //TODO:turn_left();
            stop();
            ledLeft(ORANGE_C);
            return;
        }
        case ENTRY_BAD_RIGHT:{
            //TODO:turn_right();
            stop();
            ledRight(ORANGE_C);
            return;
        }
        case ENTRY_BAD_UNKNOWN:{
            stop();
            loadingAnimationsLeds(ORANGE_C);
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
    if(micros() - state->last_obs_avoid_time < 150000){ //150000us = 150ms for 60 degree turn
        if(state->obs == OBS_ON_LEFT){
            turn_right();
            ledLeft(RED_C);
        } else {
            turn_left();
            ledRight(RED_C);
        }
        return;
    } else {
        if(state->obs == OBS_ON_LEFT){
            circle_left(state->last_obs_dst + 20);
            ledLeft(RED_C);
        } else {
            circle_right(state->last_obs_dst + 20);
            ledRight(RED_C);
        }
        return;
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