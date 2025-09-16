#include "header.h"
#include <stdint.h>

static void speedup(car_state* state){
    if(state->stabilizing_iterator < (uint32_t)(MAX_ITERATIONS_PER_SPEEDUP_COUNT * (state->speedup_count+1))){
        if(state->speedup_count < MAX_SPEEDUP_COUNT)
            state->speedup_count++;
    } else {
        state->speedup_count = 0;
    }
    state->stabilizing_iterator = 0;
}

static void handleLineValueOnLine(const uint8_t lineValue, car_state* state){
    switch(state->on_line){
        case ON_LEFT:{
            switch (lineValue) {
                case 0:{
                    speedup(state);
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_LEFT;
                    break;
                }
                case 1:{
                    state->stabilizing_iterator=0;
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                    break;
                }
                case 2:{
                    state->stabilizing_iterator++;
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->stabilizing_iterator=0;
                    state->speedup_count = 0;
                    state->main = OFF_LINE;
                    state->off_line = OFF_LEFT;
                    break;
                }
            }
            break;
        }
        case ON_MIDDLE_FROM_RIGHT:{
            switch (lineValue) {
                case 0:{
                    state->stabilizing_iterator++;
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_RIGHT;
                    break;
                }
                case 1:{
                    speedup(state);
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                    break;
                }
                case 2:{
                    state->stabilizing_iterator = 0;
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->stabilizing_iterator = 0;
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_RIGHT;
                    break;
                }
            }
            break;
        }
        case ON_MIDDLE_FROM_LEFT:{
            switch (lineValue) {
                case 0:{
                    state->stabilizing_iterator++;
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_LEFT;
                    break;
                }
                case 1:{
                    state->stabilizing_iterator=0;
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                    break;
                }
                case 2:{
                    speedup(state);
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->stabilizing_iterator=0;
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_LEFT;
                    break;
                }
            }
            break;
        }
        case ON_RIGHT:{
            switch (lineValue) {
                case 0:{
                    speedup(state);
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_RIGHT;
                    break;
                }
                case 1:{
                    state->stabilizing_iterator++;
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                    break;
                }
                case 2:{
                    state->stabilizing_iterator=0;
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->stabilizing_iterator=0;
                    state->speedup_count = 0;
                    state->main = OFF_LINE;
                    state->off_line = OFF_RIGHT;
                    break;
                }
            }
            break;
        }
    }
}

static void handleLineValueOffLine(const uint8_t lineValue, car_state* state){
    switch (state->off_line) {
        case OFF_LEFT:{
            switch (lineValue) {
                case 0: case 1:{
                    state->obs = OBS_CLEAR;
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_LEFT;
                    break;
                }
                case 2:{
                    state->obs = OBS_CLEAR;
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_LEFT;
                    break;
                }
                case 3:{
                    state->main = OFF_LINE;
                    state->off_line = OFF_LEFT;
                    break;
                }
            }
            break;
        }
        case OFF_RIGHT:{
            switch (lineValue) {
                case 0:case 2:{
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_RIGHT;
                    break;
                }
                case 1:{
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_RIGHT;
                    break;
                }
                case 3:{
                    state->main = OFF_LINE;
                    state->off_line = OFF_RIGHT;
                    break;
                }
            }
            break;
        }
    }
}

static uint16_t good_entry_counter = 0;
static void handleLineValueGoodEntry(const uint8_t lineValue, car_state* state){
    switch(state->good_entry){
        case ENTRY_GOOD_LEFT:{
            switch (lineValue) {
                case 0:{
                    if(good_entry_counter < MIN_ENTRY_COUNT){
                        state->main = ENTRY_BAD;
                        state->bad_entry = ENTRY_BAD_LEFT;
                    } else{
                        state->main = ON_LINE;
                        state->on_line = ON_MIDDLE_FROM_LEFT;
                    }
                    good_entry_counter = 0;

                    break;
                }
                case 1:{
                    good_entry_counter = 0;
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_UNKNOWN;
                    break;
                }
                case 2:{
                    good_entry_counter++;
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_LEFT;
                    break;
                }
                case 3:{
                    good_entry_counter = 0;
                    state->main = OFF_LINE;
                    state->off_line = OFF_LEFT;
                    break;
                }
            }
            break;
        }
        case ENTRY_GOOD_RIGHT:{
            switch (lineValue) {
                case 0:{
                    if(good_entry_counter < MIN_ENTRY_COUNT){
                        state->main = ENTRY_BAD;
                        state->bad_entry = ENTRY_BAD_RIGHT;
                    } else{
                        state->main = ON_LINE;
                        state->on_line = ON_MIDDLE_FROM_RIGHT;
                    }
                    good_entry_counter = 0;
                    break;
                }
                case 1:{
                    good_entry_counter++;
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_RIGHT;
                    break;
                }
                case 2:{
                    good_entry_counter = 0;
                    state->main = ENTRY_GOOD;
                    state->good_entry = ENTRY_GOOD_UNKNOWN;
                    break;
                }
                case 3:{
                    good_entry_counter = 0;
                    state->main = OFF_LINE;
                    state->off_line = OFF_RIGHT;
                    break;
                }
            }
            break;
        }
        case ENTRY_GOOD_UNKNOWN: {
            state->main = ENTRY_GOOD;
            state->good_entry = ENTRY_GOOD_UNKNOWN;
            break;
        }
    }
}

static void handleLineValueBadEntry(const uint8_t lineValue, car_state* state){
    switch(state->bad_entry){
        case ENTRY_BAD_LEFT:{
            switch (lineValue) {
                case 0:case 1:case 2:{
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_LEFT;
                    break;
                }
                case 3:{
                    state->main = ENTRY_OVER;
                    state->over_entry = ENTRY_OVER_LEFT;
                    break;
                }
            }
            break;
        }
        case ENTRY_BAD_RIGHT:{
            switch (lineValue) {
                case 0:case 1:case 2:{
                    state->main = ENTRY_BAD;
                    state->bad_entry = ENTRY_BAD_RIGHT;
                    break;
                }
                case 3:{
                    state->main = ENTRY_OVER;
                    state->over_entry = ENTRY_OVER_RIGHT;
                    break;
                }
            }
            break;
        }
    }
}

static void handleLineValueOverEntry(const uint8_t lineValue, car_state* state){
    switch(state->over_entry){
        case ENTRY_OVER_LEFT:{
            switch (lineValue) {
                case 0:{
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_RIGHT;
                }
                case 1:{
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                }
                case 2:{
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->main = ENTRY_OVER;
                    state->over_entry = ENTRY_OVER_LEFT;
                    break;
                }
            }
            break;
        }
        case ENTRY_OVER_RIGHT:{
            switch (lineValue) {
                case 0:{
                    state->main = ON_LINE;
                    state->on_line = ON_MIDDLE_FROM_LEFT;
                }
                case 1:{
                    state->main = ON_LINE;
                    state->on_line = ON_RIGHT;
                }
                case 2:{
                    state->main = ON_LINE;
                    state->on_line = ON_LEFT;
                    break;
                }
                case 3:{
                    state->main = ENTRY_OVER;
                    state->over_entry = ENTRY_OVER_RIGHT;
                    break;
                }
            }
            break;
        }
    }
}

void handleLineValue(const uint8_t lineValue, car_state* state){
    switch(state->main){
        case ON_LINE:{
            handleLineValueOnLine(lineValue, state);
            break;
        }
        case OFF_LINE:{
            handleLineValueOffLine(lineValue, state);
            break;
        }
        case ENTRY_GOOD:{
            handleLineValueGoodEntry(lineValue, state);
            break;
        }
        case ENTRY_BAD:{
            handleLineValueBadEntry(lineValue, state);
            break;
        }
        case ENTRY_OVER:{
            handleLineValueOverEntry(lineValue, state);
            break;
        }
    }
}

void StateSetup(const uint8_t lineValue, car_state* state){
    state->obs = OBS_CLEAR;
    state->last_obs_dst = MAX_OBS_DST;
    state->stabilizing_iterator = 0;
    state->speedup_count=0;
    switch (lineValue) {
        case 0:{
            state->main = ON_LINE;
            state->on_line = ON_MIDDLE_FROM_LEFT;
        }
        case 1:{
            state->main = ON_LINE;
            state->on_line = ON_RIGHT;
        }
        case 2:{
            state->main = ON_LINE;
            state->on_line = ON_LEFT;
            break;
        }
        case 3:{
            state->main = OFF_LINE;
            state->off_line = OFF_RIGHT;
            break;
        }
    }
}
