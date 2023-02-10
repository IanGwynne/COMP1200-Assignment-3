#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

// Ian Haworth
// Tracking Wine Sales Across different quarters for different wines

int loadArrays(ifstream&, string[], double[][4], int&);
void computeSum(double[][4], double[], int);
void printReport(ofstream&, string[], double[][4], double[], int, int);
void findWine(double[][4], int&, int&, int);
int mostWineSold(double[], int&, int);

const int SIZE = 25;

int main()
{
	double salesAmt[SIZE][4];  //no need to change your variable names to match mine!
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);
	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;

	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");
}

int loadArrays(ifstream& fin, string pWines[], double pQuart[][4], int& pNoWines)
{
	int row, col;
	for (row = 0; row < SIZE; row++)
	{
		getline(fin, pWines[row]);
		for (col = 0; col < 4; col++)
		{
			fin >> pQuart[row][col];
		}
		if (fin.eof())
			break;
		fin.ignore(80, '\n');
		fin.clear();
	}
	pNoWines = row;
	return row;
}

void computeSum(double pSalesAmt[][4], double pYearlySales[], int pNoWines)
{
	int row, col;
	for (row = 0; row < pNoWines; row++)
	{
		for (col = 0; col < 4; col++)
		{
			pYearlySales[row] += pSalesAmt[row][col];
		}
	}
}

void printReport(ofstream& fout, string pWines[], double pQuart[][4], double pYearlySales[], int mostSold, int pNumWines)
{
	double totalSales = 0;
	for (int ctr = 0; ctr < pNumWines; ctr++)
	{
		totalSales += pYearlySales[ctr];
	}
	int row, col;
	fout << left << setw(30) << "Wine" << right << setw(21) << "Quarterly Sales" << endl;
	fout << right << setw(27) << "1st" << setw(12) << "2nd" << setw(12) << "3rd" << setw(12) << "4th" << setw(12) << "Yearly" << endl << endl;
	for (row = 0; row < pNumWines; row++)
	{
		fout << left << setw(15) << pWines[row];
		for (col = 0; col < 4; col++)
		{
			fout << right << setw(12) << pQuart[row][col];
		}
		fout << setw(12) << pYearlySales[row];
		fout << endl;
	}
	fout << endl << "Total Sales Amount $" << totalSales << endl;
	system("type wineSales.rpt");
}

void findWine(double pSalesAmt[][4], int& pHighestRow, int& pHighestCol, int pNoWines)
{
	int row, col;
	pHighestRow = 0;
	pHighestCol = 0;
	for (row = 0; row < pNoWines; row++)
	{
		for (col = 0; col < 4; col++)
		{
			if (pSalesAmt[row][col] < pSalesAmt[pHighestRow][pHighestCol])
			{
				pHighestRow = row;
				pHighestCol = col;
			}
		}
	}
}


int mostWineSold(double pYealySales[], int& pMostSold, int pNoWines)
{
	int highestSale = 0;
	for (int ctr = 0; ctr < pNoWines; ctr++)
	{
		if (pYealySales[ctr] > pYealySales[highestSale])
			highestSale = ctr;
	}
	pMostSold = highestSale;
	return highestSale;
}

//I/O 
/*


Load arrays



=======================================================



Compute yearly Sale



=======================================================



Find best selling wine and highest sales amount:



Rose had the highest sales amount = $0.00


=======================================================



Find the most sold wine:



 Most sold wine is Sparkling


=======================================================

Wine                                Quarterly Sales
						1st         2nd         3rd         4th      Yearly

Red               200000.00    50000.00    57000.00    16800.00   323800.00
Rose               25000.00        0.00     4500.00     7800.00    37300.00
White             300000.00     4400.00    23000.00     5300.00   332700.00
Sparkling         250000.00    75000.00    40000.00   100000.00   465000.00
Dessert            60000.00    50000.00    80000.00     8500.00   198500.00
Fortified          45000.00    60000.00    75000.00    40000.00   220000.00

Total Sales Amount $1577300.00


=======================================================

program ended successfully


 Printing wines.dat file

Red
200000.00       50000.00        57000.00        16800.00
Rose
25000.00                0.00      4500.00         7800.00
White
300000.00            4400.00            23000.00              5300.00
Sparkling
250000.00       75000.00        40000.00        100000.00
Dessert
60000.00        50000.00        80000.00        8500.00
Fortified
45000.00        60000.00        75000.00        40000.00


 Printing winesales.rpt file

Wine                                Quarterly Sales
						1st         2nd         3rd         4th      Yearly

Red               200000.00    50000.00    57000.00    16800.00   323800.00
Rose               25000.00        0.00     4500.00     7800.00    37300.00
White             300000.00     4400.00    23000.00     5300.00   332700.00
Sparkling         250000.00    75000.00    40000.00   100000.00   465000.00
Dessert            60000.00    50000.00    80000.00     8500.00   198500.00
Fortified          45000.00    60000.00    75000.00    40000.00   220000.00

Total Sales Amount $1577300.00
Press any key to continue . . .

C:\Users\Ian\source\repos\COMP1200\Assignment3\x64\Debug\Assignment3.exe (process 20784) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
*/
