#include <stdio.h>
#include "components.h"
#include "climate_mediator.h"

int main(void) {
    // 1. Instantiate Hardware/Proxies
    Thermometer t; Thermometer_Init(&t);
    Heater h;      Heater_Init(&h);
    Cooler c;      Cooler_Init(&c);

    // 2. Instantiate and Wire Mediator
    ClimateMediator sys_controller;
    Mediator_Init(&sys_controller, &t, &h, &c);

    // 3. Simulate System
    printf("--- Simulation Start ---\n");

    // Scenario A: It's Cold
    Thermometer_SetMockTemp(&t, 15.0f);
    Mediator_Update(&sys_controller);

    // Scenario B: Warming up
    Thermometer_SetMockTemp(&t, 22.0f);
    Mediator_Update(&sys_controller);

    // Scenario C: Too Hot
    Thermometer_SetMockTemp(&t, 28.0f);
    Mediator_Update(&sys_controller);

    return 0;
}
