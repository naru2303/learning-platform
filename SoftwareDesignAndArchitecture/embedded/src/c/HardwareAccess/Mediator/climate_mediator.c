#include "climate_mediator.h"
#include <stdio.h>

void Mediator_Init(ClimateMediator* me, Thermometer* t, Heater* h, Cooler* c) {
    me->sensor = t;
    me->heater = h;
    me->cooler = c;
    me->low_threshold = 20.0f;
    me->high_threshold = 25.0f;
}

void Mediator_Update(ClimateMediator* me) {
    // 1. Gather Info (Input)
    float current_temp = Thermometer_Read(me->sensor);
    printf("State: Temp=%.1f C -> ", current_temp);

    // 2. Make Decision (Logic)
    // Notice: The Heater knows NOTHING about the thermometer. 
    // The Mediator connects them.
    if (current_temp < me->low_threshold) {
        // Too Cold
        Heater_TurnOn(me->heater);
        Cooler_TurnOff(me->cooler);
    } 
    else if (current_temp > me->high_threshold) {
        // Too Hot
        Heater_TurnOff(me->heater);
        Cooler_TurnOn(me->cooler);
    } 
    else {
        // Just Right (Deadband)
        Heater_TurnOff(me->heater);
        Cooler_TurnOff(me->cooler);
    }
}
