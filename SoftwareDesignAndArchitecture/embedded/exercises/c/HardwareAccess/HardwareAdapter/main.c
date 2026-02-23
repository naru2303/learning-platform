#include <stdio.h>
#include "timer_adapter.h"

// Mock hardware memory
uint32_t MOCK_TIMER_MEM[20];

// CORRECTION: Removed BlinkSystemLight (Copy/Paste artifact)

int main(void) {
    // 1. Setup the Low-Level stuff (Infrastructure code)
    TimerProxy real_timer;
    // CORRECTION: Timer_Init takes 2 args, removed '5' (pin number)
    Timer_Init(&real_timer, (uintptr_t)MOCK_TIMER_MEM);

    // 2. Setup the Adapter
    TimerAdapter adapter;
    TimerAdapter_Init(&adapter, &real_timer);

    // 3. Run the Application
    // CORRECTION: Proper usage of Interface VTable Macros/Calls
    ITimer_Start(&TimerAdapter_Interface, &adapter, 1000);
    
    if (ITimer_IsRunning(&TimerAdapter_Interface, &adapter)) {
         printf("Timer is running (or expired status checked)\n");
    }

    return 0;
}
