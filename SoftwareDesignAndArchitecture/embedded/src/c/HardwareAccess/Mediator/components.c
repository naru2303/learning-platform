#include "components.h"

// --- Thermometer Implementation ---
void Thermometer_Init(Thermometer* me) { me->current_temp = 22.0f; }
float Thermometer_Read(Thermometer* me) { return me->current_temp; }
void Thermometer_SetMockTemp(Thermometer* me, float t) { me->current_temp = t; }

// --- Heater Implementation ---
void Heater_Init(Heater* me) { me->is_on = 0; }
void Heater_TurnOn(Heater* me) { 
    if (!me->is_on) { printf("  [HW] Heater ON\n"); me->is_on = 1; }
}
void Heater_TurnOff(Heater* me) {
    if (me->is_on) { printf("  [HW] Heater OFF\n"); me->is_on = 0; }
}

// --- Cooler Implementation ---
void Cooler_Init(Cooler* me) { me->is_on = 0; }
void Cooler_TurnOn(Cooler* me) {
    if (!me->is_on) { printf("  [HW] Cooler ON\n"); me->is_on = 1; }
}
void Cooler_TurnOff(Cooler* me) {
    if (me->is_on) { printf("  [HW] Cooler OFF\n"); me->is_on = 0; }
}
