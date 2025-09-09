#include "kaulab.h"
#include "header.h"

car_state state;
bool useLeds;


void safePrint(const char* message) {
    cli();  // Disable interrupts
    Serial.print(message);
    Serial.flush();  // Wait for transmission to complete
    sei();  // Re-enable interrupts
}

void safePrintln(const char* message) {
    cli();
    Serial.println(message);
    Serial.flush();
    sei();
}

// Timer0 setup function for FreeRTOS tick
extern "C" void prvSetupTimerInterrupt(void) {
    // Disable Timer0 interrupts during configuration
    TIMSK0 = 0;
    
    // Configure Timer0 for CTC mode with prescaler 8
    TCCR0A = NO_PWM | MODE_CTC_TCCR0A;
    TCCR0B = MODE_CTC_TCCR0B | PRESCALER_8;
    OCR0A = TICK_COUNTER_TOP;  // 199 for 10kHz
    
    // Reset counter to prevent missing first interrupt
    TCNT0 = 0;
    
    // Enable Timer0 Compare Match A interrupt
    TIMSK0 = INTERRUPT_AT_TOP;
}

// Timer0 ISR for preemptive scheduler
ISR(TIMER0_COMPA_vect) {
    // Increment the tick count and check if context switch is needed
    if (xTaskIncrementTick() != pdFALSE) {
        // A higher priority task is ready, request context switch
        taskYIELD();
    }
}

// Custom delay function for Timer0 configuration
extern "C" void vPortDelay(const uint32_t ms) {
    if (ms == 0) return;
    
    // With 10kHz ticks (0.1ms per tick), convert ms to ticks
    const uint32_t ticksPerMs = configTICK_RATE_HZ / 1000; // 10 ticks per ms
    
    if (ms < 1) {
        // Use busy wait for sub-millisecond delays
        delayMicroseconds(ms * 1000);
    } else {
        // Convert milliseconds to ticks for FreeRTOS delay
        TickType_t ticks = ms * ticksPerMs;
        vTaskDelay(ticks);
    }
}

static void readLineValue() {
    uint8_t lineValue = zRobotGetLineSensor();
    handleLineValue(lineValue, &state);
}

static void readSensorValue(){
	double sensorValue = zUltraSonicSensor.distanceCm(); //max every 23 ms
    if(sensorValue < MAX_OBS_DST){
        state.last_obs_dst = sensorValue;
        state.obs = where_obs(&state);
        state.last_obs_avoid_time = micros();
    }
}


static void updateRobotState() {
    updateRobot(&state);
}


void setup() {
    state.main = OFF_LINE;
    state.off_line = OFF_RIGHT;
    state.obs = OBS_CLEAR;
    state.last_obs_dst = MAX_OBS_DST;
    useLeds = true;
    
    zInitialize();
    zTaskSetTrace(0);
    safePrintln("scheduling");
    //tick is at 10000HZ, 1 tick = 0.1ms
    zScheduleTask((void*)readLineValue, (TickType_t)200, (TickType_t)40);  
    zScheduleTask((void*)updateRobotState, (TickType_t)2000, (TickType_t)60);
    zScheduleTask((void*)readSensorValue, (TickType_t)2500, (TickType_t)40);  
    zStart();
}

void loop() {
    //EMPTY
}





