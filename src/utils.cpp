#include "header.h"

obs_state where_obs(const car_state *state) {
    switch (state->main) {
        case ON_LINE:{
            switch (state->on_line) {
                case ON_LEFT:{
                    return OBS_ON_RIGHT;
                }
                case ON_MIDDLE_FROM_LEFT:{
                    return OBS_ON_RIGHT;
                }
                case ON_MIDDLE_FROM_RIGHT:{
                    return OBS_ON_LEFT;
                }
                case ON_RIGHT:{
                    return OBS_ON_LEFT;
                }
            }
        }
        case OFF_LINE:{
            switch(state->off_line){
                case OFF_LEFT:{
                    return OBS_ON_RIGHT;
                }
                case OFF_RIGHT:{
                    return OBS_ON_LEFT;
                }
                case OFF_UNKNOWN:{
                    return OBS_CLEAR;
                }
            }
        }
        case ENTRY_GOOD:{
            switch(state->good_entry){
                case ENTRY_GOOD_LEFT:{
                    return OBS_ON_RIGHT;
                }
                case ENTRY_GOOD_RIGHT:{
                    return OBS_ON_LEFT;
                }
                case ENTRY_GOOD_UNKNOWN:{
                    return OBS_CLEAR;
                }
            }
            
        }
        default:{
            return OBS_CLEAR;
        }
    }
    return OBS_CLEAR;
}