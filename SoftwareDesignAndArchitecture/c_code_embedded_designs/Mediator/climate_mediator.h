#ifndef CLIMATE_MEDIATOR_H
#define CLIMATE_MEDIATOR_H

#include "components.h"

// The Mediator
// It holds references to all components it coordinates.
typedef struct {
    Thermometer* sensor;
    Heater* heater;
    Cooler* cooler;
    
    // Configuration (optional state logic)
    float low_threshold;
    float high_threshold;
} ClimateMediator;

void Mediator_Init(ClimateMediator* me, Thermometer* t, Heater* h, Cooler* c);

// The Core Logic: "Run Control Loop" or "OnUpdate"
void Mediator_Update(ClimateMediator* me);

#endif // CLIMATE_MEDIATOR_H
