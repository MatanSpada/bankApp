#ifndef FIXED_EXPENSES_H
#define FIXED_EXPENSES_H

class FixedExpenses
{
private:
   float m_credit_card;
   float m_rent;

public:
   FixedExpenses(float credit_card, float rent);

   float getRent();
   float getCreditCard();
   
   float total() const ;

   // overload -= for float
   friend float& operator-=(float& lhs, const FixedExpenses& rhs);
};

#endif // #ifndef FIXED_EXPENSES_H
