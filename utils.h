#ifndef UTILS_H
#define UTILS_H

#define SUCCESS 0

#include <string>
#include <iosfwd>   // for std::ostream forward declaration

enum class Status
{
   Ok = 0,
   NotEnoughMoneyToSplit = 1,
   EnvelopsHasBalanced = 2,
   InvalidEnvelopName = 3,
   EnvelopIsLocked = 4, 
   CannotBalanceEnvelops = 5,
   EnvelopNameExist = 6,
   NotEnoughMoneyToMove = 7 // between envelops
};

struct StatusResult
{
   Status status;
   std::string name;
   float amount;
};


// pretty-print Status
std::ostream& operator<<(std::ostream& os, Status s);

// pretty-print StatusResult
std::ostream& operator<<(std::ostream& os, const StatusResult& r);

#endif // #ifndef UTILS_H
