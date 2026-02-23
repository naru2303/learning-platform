#ifndef I_LIGHT_HPP
#define I_LIGHT_HPP

// Abstract Base Class (Interface)
class ILight {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual bool getState() const = 0;
    
    virtual ~ILight() = default; // Essential for polymorphic destruction
};

#endif // I_LIGHT_HPP
