#include <iostream>
#include "ClimateMediator.hpp"

int main() {
    // 1. Hardware
    Thermometer term(18.0f);
    Heater h;
    Cooler c;

    // 2. Mediator
    // In C++20, Template Argument Deduction (CTAD) figures out the types automatically.
    // We don't need to write ClimateMediator<Thermometer, Heater, Cooler>
    ClimateMediator controller(term, h, c);

    // 3. Loop
    std::cout << "--- C++20 Mediator Simulation ---" << std::endl;

    // Initial check (18C)
    controller.update();

    // Heating up
    term.setMockTemp(23.0f);
    controller.update();

    // Overheating
    term.setMockTemp(30.0f);
    controller.update();

    return 0;
}
