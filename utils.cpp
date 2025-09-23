#include "utils.h"
#include <ostream>

// pretty-print Status
std::ostream& operator<<(std::ostream& os, Status s)
{
   switch (s)
   {
      case Status::Ok:                    return os << "STATUS_OK" << std::endl;
      case Status::NotEnoughMoneyToSplit: return os << "NOT_ENOUGH_MONEY_TO_SPLIT" << std::endl;
      case Status::EnvelopsHasBalanced:   return os << "ENVELOPS_HAS_BALANCED" << std::endl;
      case Status::InvalidEnvelopName:    return os << "INVALID_ENVELOP_NAME" << std::endl;
      case Status::EnvelopIsLocked:       return os << "ENVELOP_IS_LOCKED" << std::endl;
      case Status::CannotBalanceEnvelops: return os << "CANNOT_BALANCE_ENVELOPS" << std::endl;
      case Status::EnvelopNameExist:      return os << "ENVELOP_NAME_ALREADY_EXIST" << std::endl;
      case Status::NotEnoughMoneyToMove:  return os << "NOT_ENOUGH_MONEY_IN_ENVELOP_TO_TRANSFER" << std::endl;
   }

   return os << "UNKNOWN";
}

// pretty-print StatusResult
std::ostream& operator<<(std::ostream& os, const StatusResult& r)
{
   if (r.status == Status::Ok)
      return os; 

   return os << r.status << "(name: " << r.name << ", amount: " << r.amount << ")" << std::endl;
}