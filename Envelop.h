#ifndef ENVELOP_H
#define ENVELOP_H

#include <string>

class Envelop
{
private:
   std::string m_name;
   float m_amount;
   bool m_is_locked;

public:
   Envelop(const std::string& name, float amount, bool locked = false);

   std::string getName();

   float getAmount();
   
   void setAmount(float a);

   bool getIsLocked();

   void setIsLocked(bool lock);
};

#endif // #ifndef ENVELOP_H
