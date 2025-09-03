#include <Arduino.h>
#include "kaulab.h"

#define OBSDIST 20
#define OBSDELAY 50
#define RIGHTTURNSPEED 0.3
#define LEFTTURNSPEED 0.2
#define LINEDETECTDELAY 10
#define SPEED 0.4

enum Direction {
	left,
	right
};

static const Direction in = Direction::left;
static const Direction out = Direction::right;
static Direction current_dir = left;
static void movement(Direction dir);



void setup() {
	zInitialize();
	movement(in);
}

void loop() {
	if(zRobotGetUltraSensor() < OBSDIST) {
		//obstacle detected
		Serial.println("Obstacle detected");
		movement(out);
		delay(OBSDELAY);
		//delay(OBSDELAY);
	} else if(zRobotGetLineSensor() == 0){
		//line detected
		Serial.println("Line detected");
		movement(out);
		delay(LINEDETECTDELAY);
	} else {
		Serial.println("No line or obstacle detected");
		movement(in);
		delay(10);
	}
}

static void movement(Direction dir){
	//if(dir == current_dir) return;
	current_dir = dir;
	switch(dir){
		case Direction::left: {
			zRobotSetMotorSpeed(1, (int)(SPEED * -255));
			zRobotSetMotorSpeed(2, (int)(SPEED * (0.5 - LEFTTURNSPEED) * 2 * 255));
			break;
		}
		case Direction::right: {
			zRobotSetMotorSpeed(1, (int)(SPEED * (0.5 - RIGHTTURNSPEED) * 2 * -255));
			zRobotSetMotorSpeed(2, (int)(SPEED * 255));
			break;
		}
	}
}


