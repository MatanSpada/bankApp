#include "Envelop.h"

Envelop::Envelop(const std::string& name, float amount, bool locked) : 
    m_name(name), m_amount(amount), m_is_locked(locked)
{
    // empty
}

std::string Envelop::getName() 
{ 
    return m_name; 
}

float Envelop::getAmount() 
{ 
    return m_amount; 
}

void Envelop::setAmount(float a) 
{ 
    m_amount = a; 
}

bool Envelop::getIsLocked()
{
    return m_is_locked;
}

void Envelop::setIsLocked(bool lock)
{
    m_is_locked = lock;
}

