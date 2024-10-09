#pragma once

class TrapBase {
protected:
    int trapHealth;
    int trapDamage;
    bool isActive;

public:
    TrapBase(int health, int damage); // Constructor declaration
    virtual ~TrapBase(); // Virtual destructor

    virtual void spawnTrap(int x, int y);
    virtual void takeDamage(int damageAmount);
    virtual bool isDestroyed() const;
    virtual void destructTrap();

    bool getIsActive() const { return isActive; } // Getter for isActive
    void setIsActive(bool active) { isActive = active; } // Setter for isActive
};
