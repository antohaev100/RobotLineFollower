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

void ledRight(color c){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        if(i >= 4 && i <= 6)
            zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        else
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
    }
    zLedRing.show();
}

void ledLeft(color c){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        if(i >= 10 || i == 0)
            zLedRing.setColorAt(i, c.r, c.g, c.b); // Set current LED to the color
        else
            zLedRing.setColorAt(i, OFF_C.r, OFF_C.g, OFF_C.b); // Clear all LEDs
    }
    zLedRing.show();
}

void ledFront(color c){
    if(!useLeds) return;
    for(int i = 0; i < 12; i++) {
        if(i >= 1 && i <= 3)
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