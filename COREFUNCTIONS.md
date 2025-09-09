## kaulib

# zInitialize()
run first

# zScheduleTask(func, intervall, max execution time)
run after initilization

# zStart()
starts scheduler

# zRobotSetMotorSpeed(motor, speed);
motor 1 on the right, forward speed is negative
motor 2 on the left, forward speed is positive
speed -255 to 255

# uint8_t zRobotGetUltraSensor()
returns distance 0 - 400 cm forward

# uint8_t zRobotGetLineSensor
right sensor 1
left sensor 2
both 3
none 0

# zBlockingDelay(time);
delay time ms

# Serial.println()
print to monitor