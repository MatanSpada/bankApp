#include <iostream>
#include <string>
#include "utils.h"
#include "FixedExpenses.h"
#include "EnvelopManager.h"

int main()
{
   using std::cin;
   using std::cout;
   using std::endl;
   using std::string;

   float current = 0.0f;
   float credit = 0.0f;
   float rent   = 0.0f;

   cout << "==== Envelop Manager ====\n";
   cout << "Enter current balance (before fixed expenses): ";
   cin  >> current;

   cout << "Enter fixed expenses - credit card: ";
   cin  >> credit;

   cout << "Enter fixed expenses - rent: ";
   cin  >> rent;

   FixedExpenses monthly(credit, rent);                
   current -= monthly;                                 
   EnvelopManager manager(current);                   

   auto print_status = [](const StatusResult& r) 
   {     
      std::cout << r; 
   };

   // ===== תפריט =====
   for (;;)
   {
      cout << "\n---- Menu ----\n";
      cout << "1) Display envelopes\n";
      cout << "2) Add envelope\n";
      cout << "3) Update envelope amount\n";
      cout << "4) Transfer between envelopes\n";
      cout << "5) Lock / Unlock envelope\n";
      cout << "6) Remove envelope\n";
      cout << "0) Exit\n";
      cout << "Choose: ";

      int choice = -1;

      if (!(cin >> choice)) {
         cout << "Invalid input. Exiting.\n";
         return 0;
      }

      if (choice == 0) {
         cout << "Bye.\n";
         
         break;
      }

      switch (choice)
      {
         case 1: 
         {
            manager.DisplayEnvelops();
            
            break;
         }  

         case 2: 
         {
            string name;
            float amount = 0.0f;
            int lock_int = 0;

            cout << "Envelope name: ";
            cin  >> name;
            cout << "Initial amount: ";
            cin  >> amount;
            cout << "Lock it? (1=yes, 0=no): ";
            cin  >> lock_int;

            StatusResult r = manager.AddEnvelop(name, amount, lock_int != 0);  
            print_status(r);
            
            break;
         }  

         case 3: 
         {
            string name;
            float new_amount = 0.0f;

            cout << "Envelope name: ";
            cin  >> name;
            cout << "New amount: ";
            cin  >> new_amount;

            StatusResult r = manager.UpdataEnvelopAmount(name, new_amount); 
            print_status(r);
            
            break;
         }  

         case 4: 
         {
            string from, to;
            float amount = 0.0f;

            cout << "From envelope: ";
            cin  >> from;
            cout << "To envelope: ";
            cin  >> to;
            cout << "Amount to transfer: ";
            cin  >> amount;

            StatusResult r = manager.FromToEnvelop(from, to, amount); 
            print_status(r);
            
            break;
         } 

         case 5: 
         {
            string name;
            int lock_int = 0;

            cout << "Envelope name: ";
            cin  >> name;
            cout << "Lock? (1=yes, 0=no): ";
            cin  >> lock_int;

            manager.setLockEnvelop(name, lock_int != 0);
            cout << "OK\n";
            
            break;
         } 

         case 6: 
         {
            string name;
            cout << "Envelope name to remove: ";
            cin  >> name;
            manager.RemoveEnvelop(name);
            cout << "Removed (if existed)\n";
            
            break;
         }  

         default:
            cout << "Unknown choice.\n";
            break;
      }
   }

   return 0;
}
