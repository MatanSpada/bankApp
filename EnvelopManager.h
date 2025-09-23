#ifndef ENVELOP_MANAGER_H
#define ENVELOP_MANAGER_H

#include <list>
#include "utils.h"

class Envelop; // forward declaration

class EnvelopManager
{
private:
   float m_current;
   float m_total_envelops_amount;
   std::list<Envelop*> m_envelops;

   void CalcEnvelopsAmount();

   Status BalanceEnvelops(float needed);

   Envelop* FindEnvelop(const std::string& name);

public:
   EnvelopManager(float total_amount);

   ~EnvelopManager();

   StatusResult AddEnvelop(const std::string& name, float amount = 0, bool is_locked = false);

   void RemoveEnvelop(const std::string& name);

   size_t getEnvelopsAmount();

   void DisplayEnvelops();

   StatusResult UpdataEnvelopAmount(const std::string& name, float new_amount);

   StatusResult FromToEnvelop(const std::string& from, const std::string& to, float amount);

   void setLockEnvelop(const std::string& name, bool lock);
};

#endif // #define ENVELOP_MANAGER_H
