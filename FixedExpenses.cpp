#include "FixedExpenses.h"

FixedExpenses::FixedExpenses(float credit_card, float rent) : m_credit_card(credit_card), m_rent(rent)
{
    // empty
}

float FixedExpenses::getRent()
{
    return  m_rent;
}


float FixedExpenses::getCreditCard()
{
    return  m_credit_card;
}

float FixedExpenses::total() const 
{ 
    return m_rent + m_credit_card; 
}

// overload -= for float
float& operator-=(float& lhs, const FixedExpenses& rhs)
{
    lhs -= rhs.total();
    return lhs;
}

