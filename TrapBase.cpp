#include "TrapBase.h"
#include <iostream>

TrapBase::TrapBase(int health, int damage) 
    : trapHealth(health), trapDamage(damage), isActive(false) {}

TrapBase::~TrapBase() {
    // Cleanup if necessary
}

void TrapBase::spawnTrap(int x, int y) {
    isActive = true;
    std::cout << "Trap spawned at (" << x << ", " << y << ")" << std::endl;
}

void TrapBase::takeDamage(int damageAmount) {
    trapHealth -= damageAmount;
    std::cout << "Trap took " << damageAmount << " damage. Current health: " << trapHealth << std::endl;

    if (trapHealth <= 0) {
        destructTrap();
    }
}

bool TrapBase::isDestroyed() const {
    return trapHealth <= 0;
}

void TrapBase::destructTrap() {
    isActive = false;
    std::cout << "Trap destroyed." << std::endl;
}


