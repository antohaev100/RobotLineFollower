#include "header.h"
#include "MeRGBLed.h"


extern MeRGBLed zLedRing;
extern bool useLeds;
static unsigned long lastAnimationTime = 0;
static int animationStep = 0;

void loadingAnimationsLeds(color c){
    if(!useLeds) return;
    unsigned long currentTime = millis();
    if(currentTime - lastAnimationTime >= 100) {
        lastAnimationTime = currentTime;

        for(int i = 0; i < 12; i++) {
            if(i != animationStep)
                zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
            else
                zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        }
        zLedRing.show();
        animationStep++;
        if(animationStep >= 12) {
            animationStep = 0;
        }
    }
}

void ledRight(color c, uint8_t ledCount){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        int dist = min(abs(i - 5), 12 - abs(i - 5));  // Shortest distance to center, handling wrap
        if(dist <= ledCount) {
            zLedRing.setColorAt(i, c.r, c.g, c.b);  // Set current LED to the color
        } else {
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b);  // Clear all LEDs
        }
    }
    zLedRing.show();
}

void ledLeft(color c, uint8_t ledCount){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        int dist = min(abs(i - 11), 12 - abs(i - 11));  // Shortest distance to center, handling wrap
        if(dist <= ledCount) 
            zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        else
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
    }
    zLedRing.show();
}

void ledFront(color c, uint8_t ledCount){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        int dist = min(abs(i - 2), 12 - abs(i - 2));  // Shortest distance to center, handling wrap
        if(dist <= ledCount) 
            zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        else
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
    }
    zLedRing.show();
}

void ledBack(color c){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        if(i >= 7 && i <= 9)
            zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        else
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
    }
    zLedRing.show();
}