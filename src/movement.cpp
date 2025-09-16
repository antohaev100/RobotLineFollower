#include "header.h"
#include "MeEncoderOnBoard.h"

extern MeEncoderOnBoard zMotor1;
extern MeEncoderOnBoard zMotor2;

static void setMotorSpeed(motor_speeds speeds) {
    zMotor1.setMotorPwm(speeds.right);
    zMotor2.setMotorPwm(speeds.left);
}

void stop(){setMotorSpeed( motor_speeds{0, 0});}
//1 degree per 2.5 ms
void turn_right(){setMotorSpeed( motor_speeds{255, 255});}
//1 degree per 2.5 ms
void turn_left(){setMotorSpeed( motor_speeds{-255, -255});}
//speed from 0 to 255 (1m/s)
void forward(uint8_t speed){setMotorSpeed( motor_speeds{(int16_t)-speed, (int16_t)+speed});}
//speed from 0 to 255 (unknown m/s)
void reverse(uint8_t speed){setMotorSpeed( motor_speeds{(int16_t)+speed, (int16_t)-speed});}
//circling rate from 0 (max 20 cm radius) to 255 (inf radius)
void manual_circle_right(uint8_t rate){setMotorSpeed( motor_speeds{(int16_t)rate, 255});}
//circling rate from 0 (max 20 cm radius) to 255 (inf radius)
void manual_circle_left(uint8_t rate){setMotorSpeed( motor_speeds{-255, (int16_t)-rate});}
void speedup_circle_right(uint8_t speedup_count){setMotorSpeed( motor_speeds{(int16_t)-(START_SPEED+speedup_count*SPEEDUP_PER_COUNT), 255});}
void speedup_circle_left(uint8_t speedup_count){setMotorSpeed( motor_speeds{-255, (int16_t)(START_SPEED+speedup_count*SPEEDUP_PER_COUNT)});}

//radius in cm min 20 max 90
void circle_right(uint8_t radius){
    int x;
    if (radius <= 20) {
        x = 0; //cap at radius 20 (robot width)
    } else if (radius <= 25) {
        // Linear interpolation between (20,0) and (25,-64)
        x = -64 * (radius - 20) / 5;
    } else if (radius <= 40) {
        // Linear interpolation between (25,-64) and (40,-128)
        x = -64 + (-64) * (radius - 25) / 15;
    } else if (radius <= 90) {
        // Linear interpolation between (40,-128) and (90,-191)
        x = -128 + (-63) * (radius - 40) / 50;
    } else {
        // For radius > 90, cap at -191
        x = -191;
    }
    setMotorSpeed( motor_speeds{(int16_t)x, 255});
}
//radius in cm min 20 max 90
void circle_left(uint8_t radius){
    int x;
    if (radius <= 20) {
        x = 0; //cap at radius 20 (robot width)
    } else if (radius <= 25) {
        // Linear interpolation between (20,0) and (25,-64)
        x = -64 * (radius - 20) / 5;
    } else if (radius <= 40) {
        // Linear interpolation between (25,-64) and (40,-128)
        x = -64 + (-64) * (radius - 25) / 15;
    } else if (radius <= 90) {
        // Linear interpolation between (40,-128) and (90,-191)
        x = -128 + (-63) * (radius - 40) / 50;
    } else {
        // For radius > 90, cap at -191
        x = -191;
    }
    setMotorSpeed( motor_speeds{-255, (int16_t)-x});
}
