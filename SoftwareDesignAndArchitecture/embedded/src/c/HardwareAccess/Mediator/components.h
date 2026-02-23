#ifndef COMPONENT_PROXIES_H
#define COMPONENT_PROXIES_H

#include <stdint.h>
#include <stdio.h>

// --- Colleague 1: Thermometer ---
typedef struct {
    float current_temp; // Mock hardware register
} Thermometer;

void Thermometer_Init(Thermometer* me);
float Thermometer_Read(Thermometer* me);
void Thermometer_SetMockTemp(Thermometer* me, float t); // Use for testing

// --- Colleague 2: Heater ---
typedef struct {
    int is_on;
} Heater;

void Heater_Init(Heater* me);
void Heater_TurnOn(Heater* me);
void Heater_TurnOff(Heater* me);

// --- Colleague 3: Cooler ---
typedef struct {
    int is_on;
} Cooler;

void Cooler_Init(Cooler* me);
void Cooler_TurnOn(Cooler* me);
void Cooler_TurnOff(Cooler* me);

#endif // COMPONENT_PROXIES_H
