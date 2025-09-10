#include "header.h"
#include "kaulab.h"

// Global timing functions - these will be used everywhere
unsigned long globalMillis(void) {
    return (xTaskGetTickCount() * 1000UL) / configTICK_RATE_HZ;
}

unsigned long globalMicros(void) {
    return (xTaskGetTickCount() * 1000000UL) / configTICK_RATE_HZ;
}

void globalDelayMicroseconds(unsigned int us) {
    
}

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
    
    // Configure Timer0 for CTC mode
    TCCR0A = NO_PWM | MODE_CTC_TCCR0A;
    TCCR0B = MODE_CTC_TCCR0B | PRESCALER_8; 
    OCR0A = TICK_COUNTER_TOP; 
    
    // Reset counter
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
    
    // With 100kHz ticks (0.01ms per tick), convert ms to ticks
    const uint32_t ticksPerMs = configTICK_RATE_HZ / 1000; // 100 ticks per ms
    
    if (ms < 1) {
        // Use busy wait for sub-millisecond delays
        delayMicroseconds(ms * 1000);
    } else {
        // Convert milliseconds to ticks for FreeRTOS delay
        TickType_t ticks = ms * ticksPerMs;
        vTaskDelay(ticks);
    }
}