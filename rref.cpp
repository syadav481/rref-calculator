#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <getopt.h>

using namespace std;
class RREF {
	vector<vector<double>> matrix;
public:
	void rref()
	{
		int lead = 0;
		int rowCount = matrix.size();
		int columnCount = matrix[0].size();
		for (int r = 0; r < rowCount; r++)
		{
			if (columnCount <= lead)
			{
				break;
			}
			int i = r;
			while (matrix[i][lead] == 0)
			{
				i++;
				if (i == rowCount)
				{
					i = r;
					lead++;
					if (columnCount == lead)
					{
						lead--;
						break;
					}
				}
			}
			for (int j = 0; j < columnCount; j++)
			{
				int temp = matrix[r][j];
				matrix[r][j] = matrix[i][j];
				matrix[i][j] = temp;
			}
			int div = matrix[r][lead];
			if (div != 0)
			{
				for (int j = 0; j < columnCount; j++)
					matrix[r][j] /= div;
			}
			for (int j = 0; j < rowCount; j++)
			{
				if (j != r)
				{
					int sub = matrix[j][lead];
					for (int k = 0; k < columnCount; k++)
						matrix[j][k] -= (sub * matrix[r][k]);
				}
			}
			lead++;
			printMatrix();
			cout << endl;
		}
	}
	void printMatrix()
	{
		for (const vector<double>& v : matrix) {
			cout << "[";
			for (auto i : v) {
				// didn't want to do this 3 way split,
				// without it, <iomanip>::setprecision, does weird stuff 
				// I was unsuccessful in googling a solution, so I had to do this. 
				if (i == 0) {
					cout << setw(5) << 0.0 << " ";
				}
				else if (i == 1) {
					cout << setw(5) << 1.0 << " ";
				}
				else {
					cout << setw(5) << i << " ";
				}
			}
			cout << " ]\n";
		}
	}
	void readFromCommandLine(int argc, char** argv) {
		int choice;
		int option_index;
		int countMode = 0;
		option long_options[] =
		{
			{"help", no_argument, nullptr, 'h'},
			{0, 0, 0, 0}
		};
		while ((choice = getopt_long(argc, argv, "hm:",
			long_options, &option_index)) != -1)
		{
			switch (choice)
			{
			case 'h':
				cout << "This program takes an input matrix and reduces it to\n";
				cout << "Row Reduced Echelon Form, it does so by performing\n";
				cout << "Gauss-Jordan Elimination to the matrix.\n";
				cout << "-----------------------------------------------------\n";
				cout << "Input: \n";
				cout << "Input can be entered at the command line, or redirected\n";
				cout << "Enter input in the following format:\n";
				cout << "<M> where M is the number of rows\n";
				cout << "<N> where N is the number of columns\n";
				cout << "a11, a12, ... a1N\n";
				cout << ".\n";
				cout << ".\n";
				cout << ".\n";
				cout << "aM1, aM2, ... aMN\n";
				cout << "Note that Aij, is the ijth entry of matrix A\n";
				exit(0);
				break;
			default:
				cerr << "unknown command line option" << endl;
				exit(1);
				break;
			}
		}
	}
	void readInput() {
		int M;
		int N;
		cin >> M;
		cin >> N;
		for (int r = 0; r < M; ++r) {
			matrix.push_back({});
			for (int c = 0; c < N; ++c) {
				double temp;
				cin >> temp;
				matrix[r].push_back(temp);
			}
		}
	}
	void performAllOperations() {
		readInput();
		cout << "The input matrix is...\n";
		printMatrix();
		for (int i = 0; i < matrix.size(); ++i)
			cout << " ";
		cout << "\n";
		cout << "Steps taken...\n";
		rref();
		cout << "The reduced matrix is...\n";
		printMatrix();
	}
};
int main(int argc, char** argv)
{
	cout << setprecision(1);
	cout << fixed;
	RREF r;
	r.readFromCommandLine(argc, argv);
	r.performAllOperations();
}

