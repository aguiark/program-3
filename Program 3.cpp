//---------------------------------------------------------------------
// Name: Alex Mueller
//
// Course:  CS 143, Section 02,  Spring 2014
//
// Purpose: This program calculates the cost of a customers
//          power usage based on the kilowatt hours and the
//          type of customer that they are. It also comes up
//          with a payment plan over the course of 30 days.
//
//
// Input :  This program accepts the following prompted input
//          from the keyboard:
//              killoWatt hours     - as a float
//              customer type       - as a char
//
//
//
// Output:  This program provides the following computed output,
//          appropriately labelled, to the monitor:
//                  lastTerm          - as an integer
//                  averageOfAllTerms - as a float
//                  sumOfAllTerms     - as an integer
//---------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int NUM_DAYS = 30;

char customerType;

bool shouldExit = false;

float bAmount;


double ResidentialBill();
double BusinessBill();
void MenuDisplay( double );
void InstallmentCalculator( double );
void ChangeInConsumption( double );

int main() 
{
   cout << fixed << showpoint;
   cout << setprecision(2);
   
   while( shouldExit != true)
   {
      cout << "Enter customer type: R, r"
           << " (Residential) or B, b (Business):" << endl;
      cin >> customerType;
      if (customerType == 'R' || customerType == 'r')
      {
         bAmount = ResidentialBill();
         MenuDisplay(bAmount);
      }
      else if (customerType == 'B' || customerType == 'b')
      {
         bAmount = BusinessBill();
         MenuDisplay(bAmount);
      }
   }
}

//---------------------------------------------------------------------
// This function computes the amount due of a residential bill 
// and returns the result as double.
// It prompts the user for the total usage KiloWatt Hours (KWH). 
// It presumes that total usage is non-negative and does
// not check for that.
// params: ( )
//---------------------------------------------------------------------
double ResidentialBill( )
{
   const float energyCharge = .12;
   const float flatCharge   = 8.07;
   const float salesTax     = .05;
   int kWattHours;
   float amountDue, costPerDay;
   
   cout << endl << "Welcome Residential Customer" << endl;
   cout << "Enter the total usage KiloWatt Hours (KWH):" << endl;
   cin >> kWattHours;
   amountDue = (flatCharge + (kWattHours * energyCharge));
   amountDue = amountDue + (amountDue * salesTax);
   
   
   cout << endl << "Amount Due = $" << amountDue << endl;
   cout << "30 Billing Days" << endl;
   costPerDay = amountDue / NUM_DAYS;
   cout << "Average Cost per Day = $" << costPerDay << endl;
   return amountDue;
}



//---------------------------------------------------------------------
// This function compute the amount due of a business bill 
// and returns the result as double.
// It prompts the user for the total usage KiloWatt Hours (KWH). 
// It presumes that total usage is non-negative and does
// not check for that.
// params: ( )
//---------------------------------------------------------------------
double BusinessBill( )
{
   const float baseEnergyCharge    = .17;
   const float reducedEnergyCharge = .12;
   const int perChannel            = 47;
   const float flatCharge          = 17.07;
   const int kWattLimit            = 1200;
   const float salesTax            = .08;
   
   float amountDue;
   int kWattHours;
   float kWattPrice, costPerDay;
   int primiumChannels;
   
   cout << endl << "Welcome Business Customer" << endl;
   cout << "Enter the total usage KiloWatt Hours (KWH):" << endl;
   cin >> kWattHours;
   
   if (kWattHours <= kWattLimit)
   {
      kWattPrice = kWattHours * baseEnergyCharge;
   }
   else
   {
      kWattPrice = (kWattLimit * baseEnergyCharge) +
      ((kWattHours - kWattLimit) * reducedEnergyCharge);
   }
   cout << endl << "Enter the number of premium channels used:" << endl;
   cin >> primiumChannels;
   
   amountDue = (flatCharge + kWattPrice + (primiumChannels * perChannel));
   amountDue = amountDue + (amountDue * salesTax);
   costPerDay = amountDue / NUM_DAYS;
   cout << endl << "Amount Due = $" << amountDue << endl;
   cout << "30 Billing Days" << endl;
   costPerDay = amountDue / NUM_DAYS;
   cout << "Average Cost per Day = $" << costPerDay << endl;
   
   return amountDue;

}



//---------------------------------------------------------------------
// This function presents a menu of the choices available to customers.
// It prompts the user for an option. 
// It presumes that the user enter a correct choice and does
// not check for that.
// Based on user's choice, it calls either function InstallmentCalculator 
// or function ChangeInConsumption.
// params: ( in )
//---------------------------------------------------------------------
void MenuDisplay ( double bAmount )
{
   char response;
   cout << endl << "Please select an option :" << endl;
   cout << "I: Enroll in our Installment Plan" << endl;
   cout << "V: View change in consumption: Compare your "
        << "current bill with your previous one" << endl;
   cout << "E: Exit" << endl;
   cin >> response;
   if( response == 'i' || response == 'I')
   {
      cout << "......................................." << endl;
      cout << "If you do not want to make a onetime payment," << endl;
      cout << "we have an easy installment plan for you." << endl;
      cout << "This is an interest charge plan." << endl;
      cout << "Sign up for the Installment Payment Plan (y/n)?" << endl;
      cin >> response;
      if (response == 'y' || response == 'Y')
      {
         InstallmentCalculator(bAmount);
      }
      else if (response == 'n' || response == 'N')
      {
         MenuDisplay(bAmount);
      }
   }
   else if (response == 'v' || response == 'V')
   {
      ChangeInConsumption(bAmount);
   }
   else if(response == 'e' || response == 'E')
   {
      shouldExit = true;
      cout << "Goodbye." << endl;
   }
   
}
//---------------------------------------------------------------------
// This function calculates an amount due repayment plan to be paid off
// in equal installments over 30 billing days.
// It prompts the user for the number of the required Installment.
// It presumes that the user enter a correct number of installments
// (2 ,3 ,or 4), and does not check for that.
// It prints to the standard output, the new amount due after applying
// the required installment plan, and the amount of each installment.
//
// params: ( in )
//---------------------------------------------------------------------
void InstallmentCalculator( double bAmount )
{
   const double PLAN_CHARGE_2 = .0535;
   const double PLAN_CHARGE_3 = .055;
   const double PLAN_CHARGE_4 = .0575;
   const int TWO = 2;
   const int THREE = 3;
   const int FOUR = 4;
   double afterPlan, perInstall;
   float numInstall;
   cout << "Enter the number of the required Installment "
        << "(2 , 3 , or 4):" << endl;
   cin >> numInstall;
   switch ((int)numInstall)
   {
      case TWO: afterPlan = bAmount + (bAmount * PLAN_CHARGE_2);
         break;
      case THREE: afterPlan = bAmount + (bAmount * PLAN_CHARGE_3);
         break;
      case FOUR: afterPlan = bAmount + (bAmount * PLAN_CHARGE_4);
         break;
         
      default:
         break;
   }
   
   perInstall = afterPlan / numInstall;
   cout << "With " << (int) numInstall << " installment your bill of $";
   cout << bAmount << " will be worth $" << afterPlan << '.' << endl;
   cout << "Each installment will be worth $"
        << perInstall << '.' << endl;
   MenuDisplay(bAmount);
   
}




//---------------------------------------------------------------------
// This function calculates change in consumption and whether the 
// change is increasing or decreasing as determined by the 
// comparison between the amount due of present bill and the bill 
// one month ago.
// It prompts the user number for the amount due of her/his
// previous bill.
// It should check whether change in consumption is an increasing or a 
// decreasing.  
// It prints to the standard output, the value of change in
// consumption as a percentage
// params: (in)
//---------------------------------------------------------------------
void ChangeInConsumption( double NewbAmount )
{
   const int HUNDERED = 100;
   const int ZERO = 0;
   float lastBill, differance;
   bool increasing = false;
   string change = "increasing";
   
   cout << "Enter the amount due of your previous bill" << endl;
   cin >> lastBill;
   
   differance = lastBill - NewbAmount;
   if (differance < ZERO)
      increasing = false;
   else
      increasing = true;
   differance = (differance / lastBill) * HUNDERED;
   differance = abs(differance);
   if (increasing == true)
   {
      cout << "The change in consumption is decreasing by "
      << differance << "%, when comparing with previous due" << endl;
      MenuDisplay(bAmount);
   }
   else
   {
      cout << "The change in consumption is increasing by "
           << differance << "% , when comparing with "
           << "previous due" << endl;
      MenuDisplay(bAmount);
   }
}