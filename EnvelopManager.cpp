#include <list>
#include "utils.h"
#include "EnvelopManager.h"
#include "Envelop.h"
#include <iostream>
#include <iomanip>


// private:

void EnvelopManager::CalcEnvelopsAmount()
{
    m_total_envelops_amount = 0;
    for (auto e : m_envelops)
    {
        m_total_envelops_amount += e->getAmount();
    }
}

Status EnvelopManager::BalanceEnvelops(float needed)
{
    if (needed <= 0.0f) 
    {
        return Status::Ok;
    }

    float sum_unlocked = 0.0f;

    for (auto e : m_envelops)
    {
        if(e->getIsLocked() == false)
        {
        sum_unlocked += e->getAmount();
        }
    }

    if (sum_unlocked <= 0.0f || needed > sum_unlocked)
    {
        return Status::CannotBalanceEnvelops;
    }

    // balancing
    for (auto e : m_envelops)
    {
        if (e->getIsLocked() == false)
        {
        float ratio  = e->getAmount() / sum_unlocked;
        float reduce = ratio * needed;
        e->setAmount(e->getAmount() - reduce);
        }
    }

    CalcEnvelopsAmount();

    return Status::Ok;
}

Envelop* EnvelopManager::FindEnvelop(const std::string& name)
{
    for (auto e : m_envelops)
    {
        if (e->getName() == name)
        {
        return e; 
        }
    }

    return nullptr; 
}

// public:
EnvelopManager::EnvelopManager(float total_amount) : m_current(total_amount), m_total_envelops_amount(0) 
{
    // empty
}

EnvelopManager::~EnvelopManager()
{
    for (auto e : m_envelops)
        delete e;
}

StatusResult EnvelopManager::AddEnvelop(const std::string& name, float amount, bool is_locked)
{
    if(nullptr != FindEnvelop(name))
    {
        return {Status::EnvelopNameExist, name, amount};
    }
    bool balanced = false;

    if (m_current < (m_total_envelops_amount + amount))
    {
        float needed = m_total_envelops_amount + amount - m_current;

        if(Status::Ok != BalanceEnvelops(needed))
        {
        return {Status::NotEnoughMoneyToSplit, name, amount};
        }

        balanced = true;
    }

    Envelop* envelop = new Envelop(name, amount, is_locked);
    m_envelops.push_back(envelop);
    m_total_envelops_amount += amount;

    return (balanced == true) ? StatusResult{Status::EnvelopsHasBalanced, name, amount} : StatusResult{Status::Ok, name, amount};
}

void EnvelopManager::RemoveEnvelop(const std::string& name)
{
    Envelop* e = FindEnvelop(name);
    if(nullptr == e)
    {
        return;
    }

    UpdataEnvelopAmount(e->getName(), 0);

    m_envelops.remove(e);
    delete e;
}

size_t EnvelopManager::getEnvelopsAmount() { return m_envelops.size(); }

void EnvelopManager::DisplayEnvelops()
{
    int i = 1;
    std::cout << "\ncurrent after fixed expenses: " 
            << std::fixed << std::setprecision(2) << m_current << std::endl;

    std::cout << "\ndisplay envelops:" << std::endl;

    for (auto e : m_envelops)
    {
        std::cout << i++ << ". " << e->getName() 
                    << ": " << std::fixed << std::setprecision(2) 
                    << e->getAmount() << std::endl;
    }

    std::cout << "\ncurrent after splitting: " 
            << std::fixed << std::setprecision(2) 
            << m_current - m_total_envelops_amount << std::endl;
}

StatusResult EnvelopManager::UpdataEnvelopAmount(const std::string& name, float new_amount)
{
    Envelop* e = FindEnvelop(name);
    if (!e)
        return {Status::InvalidEnvelopName, name, new_amount};

    float old_amount = e->getAmount();
    if (e->getIsLocked() && new_amount != old_amount)
    {
        return {Status::EnvelopIsLocked, name, new_amount};
    }

    float diff = new_amount - old_amount;

    // add money to an envelop
    if (diff > 0)
    {
        float free = m_current - m_total_envelops_amount;      // יתרה פנויה נוכחית

        // enough money - no balance needed
        if (free >= diff)
        {
        e->setAmount(new_amount);
        CalcEnvelopsAmount();
        return {Status::Ok, name, new_amount};
        }

        //float sum_others   = m_total_envelops_amount - old_amount;     // סכום שאר המעטפות
        float sum_locked_others = 0.0f;
        float sum_unlocked_others = 0.0f;

        for (auto other : m_envelops)
        {
        if (other != e)
        {
            if (other->getIsLocked())
            {
                sum_locked_others += other->getAmount();
            }
            else
            {
                sum_unlocked_others += other->getAmount();
            }
        }
        }

        // not enough money - need to balance
        float target_others = m_current - new_amount - sum_locked_others;

        // no moeny or empty envelops
        if (target_others < 0.0f || sum_unlocked_others <= 0.0f)
        {
        return {Status::NotEnoughMoneyToSplit, name, new_amount};
        }

        // scale for calculating other envelops
        float s = target_others / sum_unlocked_others;

        // balance only other envelops
        for (auto other : m_envelops)
        {
        if (other != e && other->getIsLocked() == false)
        {
            other->setAmount(other->getAmount() * s);
        }
        }
        
        // set the chosen envelop
        e->setAmount(new_amount);
        CalcEnvelopsAmount();

        return {Status::EnvelopsHasBalanced, name, new_amount};
    }

    // 
    e->setAmount(new_amount);
    CalcEnvelopsAmount();
    return {Status::Ok, name, new_amount};
}

StatusResult EnvelopManager::FromToEnvelop(const std::string& from, const std::string& to, float amount)
{
    Envelop *f = FindEnvelop(from);
    Envelop *t = FindEnvelop(to);

    if (t == nullptr || f == nullptr)
    {
        return {Status::InvalidEnvelopName, to, amount};
    }

    if (from == to)
    {
        return {Status::Ok, from, 0.0f};
    }

    float from_old = f->getAmount();
    float to_old   = t->getAmount();

    if(from_old < amount)
    {
        return {Status::NotEnoughMoneyToMove, from, amount};
    }

    StatusResult s = UpdataEnvelopAmount(from, from_old - amount);
    if (s.status != Status::Ok)
    {
        return s;
    }

    s = UpdataEnvelopAmount(to, to_old + amount);
    if (s.status != Status::Ok && s.status != Status::EnvelopsHasBalanced)
    {
        // if failed, moving back
        UpdataEnvelopAmount(from, from_old);
        return s;
    }

    // success
    return s;
}

void EnvelopManager::setLockEnvelop(const std::string& name, bool lock)
{
    Envelop *e = FindEnvelop(name);
    if(nullptr != e)
    {
        e->setIsLocked(lock);
    }
}
