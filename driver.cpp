/*
Author: Sriram Acharya
Class: CS 301
*/

#include "SetT.h"
#include <iostream>
#include<fstream>
#include <string>
#include <forward_list>
using namespace std;

int main()
{
	SetT<int> setA;
	SetT<int> setB;
	SetT<int> setC;





	ifstream inFile;
	// file containing operations
	ofstream outFile;
	// file containing output
	string inFileName;
	// input file external name
	string outFileName;
	// output file external name
	string outputLabel;


	string command;
	int set_item;

	// operation to be executed
	int list_item;
	// Prompt for file names, read file names, and prepare files
	/*cout << "Enter name of input command file; press return." << endl;
	cin >> inFileName;*/

	inFile.open("test.txt");
	/*cout << "Enter name of output file; press return." << endl;
	cin >> outFileName;*/

	outFile.open("outfile.txt");
	cout << "Enter name of test run; press return." << endl;
	cin >> outputLabel;
	outFile << outputLabel << endl;
	if (!inFile)
	{
		cout << "File not found." << endl;
		exit(2);
	}
	inFile >> command;
	while (command != "quit")
	{
		if (command == "addA") {

			inFile >> set_item;
			setA + set_item;
			//setA.Add(set_item);
			cout << set_item << " " << "has been added to the set A" << endl;
			outFile << set_item << " " << "has been added to the set A" << endl;

		}

		else if (command == "addB") {

			inFile >> set_item;
			setB + set_item;
			//setB.Add(set_item);

			cout << set_item << " " << "has been added to the set B" << endl;
			outFile << set_item << " " << "has been added to the set B" << endl;

		}
		else if (command == "remove") {
			inFile >> set_item;
			setA - set_item;
			cout << set_item << " " << "has been removed from the set" << endl;
			outFile << set_item << " " << "has been removed from the set" << endl;
		}
		else if (command == "contains") {
			inFile >> set_item;
			cout << setA.Contains(set_item) << endl;
			outFile << setA.Contains(set_item) << endl;

		}
		else if (command == "intersection") {
			setC = setA * setB;

			cout << "intersection of A and B" << endl;
			outFile << "intersection of A and B" << endl;

			setC.print_bucket();
			setC.print_bucket(outFile);

		}
		else if (command == "union") {

			setC = setA + setB;

			cout << "union of A and B" << endl;
			outFile << "union of A and B" << endl;

			setC.print_bucket();
			setC.print_bucket(outFile);

		}
		else if (command == "difference") {

			setC = setA - setB;
			cout << "difference" << endl;
			outFile << "difference" << endl;
			setC.print_bucket();
			setC.print_bucket(outFile);

		}
		else if (command == "printA") {
			cout << "set A" << endl;
			cout << "-----" << endl;

			outFile << "set A" << endl;
			outFile << "-----" << endl;

			setA.print_bucket();
			setA.print_bucket(outFile);
		}

		else if (command == "printB") {
			cout << "set B" << endl;
			cout << "-----" << endl;

			outFile << "set B" << endl;
			outFile << "-----" << endl;

			setB.print_bucket();
			setB.print_bucket(outFile);
		}

		inFile >> command;

	}


	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
