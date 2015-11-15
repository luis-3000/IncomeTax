// TI or TaxableIncome.cpp : This program calculates the tax owed on earned income,
// based on four different cases.
// Author: Jose Luis Castillo


#include <fstream>   // File input/output
#include <iostream> 
#include <iomanip>
using namespace std;

// 1. Constants
const double rate1 = 0.1;
const double rate2 = 0.15;
const double rate3 = 0.27;
const double rate4 = 0.3;
const double rate5 = 0.35;
const double rate6 = 0.386;

const int Single = 0;
const int MarriedJointly = 1;
const int MarriedSeparately = 2;
const int HeadOfHousehold = 3;

/* 2. Module to compute tax. */
double ComputeTax(double taxableIncome, double cap1, double cap2, double cap3, double cap4,
							double cap5) {

	double tax = 0.0;
	double t1 = cap1 * rate1;
	double t2 = (cap2 - cap1) * rate2;
	double t3 = (cap3 - cap2) * rate3;
	double t4 = (cap4 - cap3) * rate4;
	double t5 = (cap5 - cap4) * rate5;

	if (taxableIncome <= cap1) {

		tax = taxableIncome * rate1;

	} else if (taxableIncome <= cap2) {

		tax = taxableIncome * rate2;

	} else if (taxableIncome <= cap3) {

		tax = taxableIncome * rate3;

	} else if (taxableIncome <= cap4) {

		tax = taxableIncome * rate4;

	}

	return tax;
}


/*  2. Module to determine the tax owed. */
double DetermineTax(int filingStatus, double taxableIncome) {
	// 0 = Single
	// 1 = Married filing jointly
	// 2 = Married filing separately
	// 3 = Head of household
	double tax = 0.0;

	switch(filingStatus)
	{
		case 0: // Single
			tax = ComputeTax(taxableIncome, 6000.00, 27950.00, 67700.00, 141250.00, 307050.00);
			break;
		case 1: // Married filing jointly
			tax = ComputeTax(taxableIncome, 12000.00, 46700.00, 112850.00, 171950.00, 307050.00);
			break;
		case 2: // Married filing  separately
			tax = ComputeTax(taxableIncome, 6000.00, 23350.00, 56425.00, 85975.00, 153526.00);
			break;
		case 3: // Head of household
			tax = ComputeTax(taxableIncome, 12000.00, 37450.00, 96700.00, 156600.00, 307050.00);
			break;
		default:
			cout << filingStatus << " was specified incorrectly, review and re-enter filing status." << endl;
			break;	
	}

	return tax;
}


int main() {
	// 0 = Single
	// 1 = Married filing jointly
	// 2 = Married filing separately
	// 3 = Head of household
	int ssNo, filingStatus; // 0 ... 3 as specified below
	double taxableIncome, grossIncome, adjustments, tax;
	ifstream inFile;
	ofstream outFile;

	// 3. Character strings representing the names of the input files.
	char inFileName[] = "TaxRoll.txt";
	char outFileName[] = "TaxesPaid.txt";

	// Open file
	inFile.open(inFileName);
	if (inFile == 0)
	{
		cout << inFileName << " file did not open." << endl;
		return 0;
	}

	outFile.open(outFileName);
	if (outFile == 0)
	{
		cout << outFileName << " file did not open." << endl;
	}

	outFile << setprecision(2) << showpoint << fixed;

	// Header for the output file
	outFile << "SS Number  FS  Taxable inc.   Tax paid     Percent" << endl;
	outFile << "---------  --  ------------   ----------   -------" << endl;
	//          123456789  1   $ 12345.67     $ 1234.56 	10.00%

	while (!inFile.eof()) // while there are characters to read from the file
	{
		/* Read the next line including the social security number, filing status coded as above,
		 * a gross income and adjustments to it that will allow us to get a taxable income. */
		inFile >> ssNo >> filingStatus >> grossIncome >> adjustments;
		taxableIncome = grossIncome - adjustments;
		tax = DetermineTax(filingStatus, taxableIncome);
		double percent = tax / grossIncome * 100.0;

		// 5. Formatted file output with setprecision, showpoint, fixed ans setw.
		outFile <<   setw(9) << ssNo 		  << " " <<
				     setw(2) << filingStatus  << " " <<
		   "   $" << setw(9) << taxableIncome << " " <<
		   "   $" << setw(9) << tax 		  << " " <<
		   "    " << setw(5) << percent       << "% " <<  endl;
	}

	inFile.close();
	outFile.close();


	return 0;
}

