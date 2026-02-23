#ifndef I_LIGHT_H
#define I_LIGHT_H

// The Interface Definition
// Application code uses this, not the specific implementation.

typedef struct ILight ILight;

struct ILight {
    // Methods (VTable)
    void (*turnOn)(void* instance);
    void (*turnOff)(void* instance);
    int  (*isOn)(void* instance);
};

// Helper macros for cleaner syntax (optional, but nice)
#define ILight_TurnOn(interface, instance)  ((interface)->turnOn(instance))
#define ILight_TurnOff(interface, instance) ((interface)->turnOff(instance))
#define ILight_IsOn(interface, instance)    ((interface)->isOn(instance))

#endif // I_LIGHT_H
