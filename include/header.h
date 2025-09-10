#ifndef HEADER_H
#define HEADER_H

#include "MeEncoderOnBoard.h"
#include "MeRGBLed.h"
#include "MeUltrasonicSensor.h"
#include "Arduino_FreeRTOS.h"

//------------------------------------------
extern unsigned long globalMillis(void);
extern unsigned long globalMicros(void);
void safePrint(const char* message);
void safePrintln(const char* message);
uint8_t zRobotGetLineSensor();
void zInitialize();
void zStart();
void zScheduleTask(void *func, TickType_t interval, TickType_t runtime);
void zTaskSetTrace(int trace);
//-------------------------------------------


#define MAX_OBS_DST 20 // in cm
#define ON_LINE_CIRCLE_RADIUS 60
#define OFF_LINE_CIRCLE_RADIUS 40 //should be a little less than radius of track turn + car width

enum main_state { ON_LINE, OFF_LINE, ENTRY_GOOD, ENTRY_BAD, ENTRY_OVER };
enum on_line_state { ON_LEFT, ON_MIDDLE_FROM_RIGHT, ON_MIDDLE_FROM_LEFT, ON_RIGHT };
enum off_line_state { OFF_LEFT, OFF_RIGHT, OFF_UNKNOWN };
enum entry_good_state { ENTRY_GOOD_LEFT, ENTRY_GOOD_RIGHT, ENTRY_GOOD_UNKNOWN };
enum entry_bad_state { ENTRY_BAD_LEFT, ENTRY_BAD_RIGHT, ENTRY_BAD_UNKNOWN };
enum entry_over_state { ENTRY_OVER_LEFT, ENTRY_OVER_RIGHT };
enum obs_state { OBS_ON_LEFT, OBS_ON_RIGHT, OBS_CLEAR };
struct car_state {
    main_state main;
    on_line_state on_line;
    off_line_state off_line;
    entry_good_state good_entry;
    entry_bad_state bad_entry;
    entry_over_state over_entry;
    obs_state obs;
    double last_obs_dst;
    unsigned long last_obs_avoid_time; //us
};
struct motor_speeds {
    int16_t right;  // Speed for the right motor (-255 to 255)
    int16_t left; // Speed for the left motor (-255 to 255)
};

struct color {
    uint8_t r,g,b;
};

//robot
void updateRobot(const car_state* state);

//line
void handleLineValue(const uint8_t lineValue, car_state* state);

//movement
void stop();
void turn_right();
void turn_left();
void forward(uint8_t speed);
void reverse(uint8_t speed);
void circle_right(uint8_t radius);
void circle_left(uint8_t radius);

//utils
obs_state where_obs(const car_state *state);

//leds
const color OFF_C = {0,0,0};
const color NEON_C = {0,255,255};
const color GREEN_C = {0,255,0};
const color BLUE_C = {0,0,255};
const color RED_C = {255,0,0};
const color ORANGE_C = {255,165,0};
void loadingAnimationsLeds(color c);
void ledRight(color c);
void ledLeft(color c);
void ledFront(color c);
void ledBack(color c);

#endif // HEADER_H