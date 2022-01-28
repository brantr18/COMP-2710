/* FILE NAME: project1_Robertson_bar0065
* AUTHOR: Brantley Robertson
* AUBURN USER ID: bar0065
* I did not use any outside sources when writing this program.
* Any sources I used are permitted sources that do not require citation.
*/


#include <iostream>
using namespace std;

int main() {
	// VARIABLE INITIALIZATION
	double loan;					// LOAN AMOUNT
	double interestRate;			// YEARLY INTEREST RATE %
	double monthlyPaid;				// MONTHLY PAYMENT AMOUNT
	double interestRateC;			// INTEREST RATE CONVERTED TO MONTHLY RATE DECIMAL FOR CALCULATION
	int currentMonth = 0;			// MONTH COUNTER
	double interestTotal = 0;		// TOTAL AMOUNT OF INTEREST PAID AFTER PAYING OFF LOAN
	double interest = 0;			// INTEREST AMOUNT EACH MONTH OF THE LOAN (AS SHOWN IN TABLE)
	double principal = 0;			// MONTHLY PAYMENT MINUS THE INTEREST (AS SHOWN IN TABLE)


	// CURRENCY FORMATTING
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// GETTING THE LOAN AMOUNT AND THE INTEREST RATE FROM THE USER.
	cout << "\nLoan Amount: ";
	cin >> loan;
	while ((cin.fail()) || (!cin) || (loan < 1)) {
		cout << "Loan has to be a number and greater than 0.";
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nLoan Amount: ";
		cin >> loan;
	}


	cout << "Interest rate (% per year): ";
	cin >> interestRate;
	while ((cin.fail()) || (!cin) || (interestRate < 0)) {
		cout << "Interest rate has to be a number and not negative.\n";
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Interest rate (% per year): ";
		cin >> interestRate;
	}


	// GETTING PROPER INTEREST RATES FOR CALCULATIONS AND GETTING MONTHLY PAYMENT FROM USER.
	interestRate /= 12;
	interestRateC = interestRate / 100;
	cout << "Monthly Payments: ";
	cin >> monthlyPaid;
	while ((cin.fail()) || (!cin) || (monthlyPaid < 1) || (monthlyPaid <= loan * interestRateC)) {
		cout << "Invalid monthly payment.\n";
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Monthly Payments: ";
		cin >> monthlyPaid;
	}

	cout << endl;

	// AMORTIZATION TABLE
	cout << "*****************************************************************\n"
		<< "\tAmortization Table\n"
		<< "*****************************************************************\n"
		<< "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";


	// LOOP TO FILL IN THE TABLE
	while (loan > 0) {
		if (currentMonth == 0) {
			cout << currentMonth++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
		}
		else {
			// interestRate is already divided by 12.
			interest = loan * interestRateC;
			// The addition of the small decimal is for when a principal that ends
			// with .99999... gets chopped off and rounded down.
			principal = (monthlyPaid - interest) + (0.00000001);
			if (loan < monthlyPaid + interest) {
				monthlyPaid = loan + interest;
				principal = monthlyPaid - interest;
			}
			loan = loan - principal;
			cout << currentMonth++
				<< "\t$"
				<< loan;
			if (loan < 1000) cout << "\t";
			cout << "\t"
				<< monthlyPaid
				<< "\t"
				<< interestRate
				<< "\t"
				<< interest
				<< "\t\t"
				<< principal
				<< "\n";
			interestTotal = interestTotal + interest;
		}
	}
	cout << "****************************************************************\n";
	cout << "\nIt takes " << --currentMonth << " months to pay off "
		<< "the loan.\n"
		<< "Total interest paid is: $" << interestTotal;
	cout << endl << endl;
	return 0;
}