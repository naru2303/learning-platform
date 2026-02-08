#include "HardwareProxy/Practice/timer_driver.h"
#include <stdio.h>

// Mock Hardware Address for simulation
uint32_t VIRTUAL_TIMER[1024]; 

#define TIMER_BASE ((uintptr_t)VIRTUAL_TIMER)

int main(void) {
    TimerProxy TimerProxyInstance;
    
    // Initialize the proxy (bind it to address and pin)
    Timer_Init(&TimerProxyInstance, TIMER_BASE);

    // Set a reload value 
    Timer_SetReload(&TimerProxyInstance, 1000);

    // Start the timer
    Timer_Start(&TimerProxyInstance);
    printf("Timer started with reload value 1000.\n");

    // Simulate some operation
    // In a real scenario, we would wait and check the timer status
    // For demonstration, we will just get the counter value
    uint32_t counter = Timer_GetCounter(&TimerProxyInstance);
    printf("Current Timer Counter: %u\n", counter);

    // Stop the timer
    Timer_Stop(&TimerProxyInstance);
    printf("Timer stopped.\n");


    return 0;
}
