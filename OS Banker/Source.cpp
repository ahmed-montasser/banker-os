#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

void fill_vector(int n, int m, vector<vector<int>>& a) {
	int input;
	for (int i = 0; i < n; i++) {
		cout << "P" << i << endl;
		for (int j = 0; j < m; j++) {
			cout << "Enter Number of instances for R" << j << " : ";
			cin >> input;
			a[i].push_back(input);
		}
	}
	input = 0;
}



int main() {

	int m; // Number of Resources
	int n; // Number of Processes
	int input; // Input Variable

	cout << "Please Enter Number of Resources" << endl;
	cin >> m ;
	cout << "Please Enter Number of Processes" << endl;
	cin >> n;

	vector<int> available(m);
	vector<vector<int>> max(n);
	vector<vector<int>> allocation(n);
	vector<vector<int>> need(n);

	// Reading Available Vector (START)
	cout << "Enter Available vector" << endl;

	for (int i = 0; i++; i < m) {
		cout << "R" << i << " : " ;
		cin >> input;
		available.push_back(input);
	}

	// *********************************************************************************************

		// Reading Max Matrix (START)
		cout << "Enter Max Matrix" << endl;

		fill_vector(n, m, max);

		// *********************************************************************************************
	
	
		// Reading Alloc Matrix (START)
		cout << "Enter Alloc Matrix" << endl;

		fill_vector(n, m, allocation);

		// *********************************************************************************************
	
	// Calculate Need Matrix
	cout << "Need Matrix" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i].push_back(max[i][j] - allocation[i][j]);
		}
	}

	// *********************************************************************************************

	//Print Need Matrix
	cout << "    ";
	for (int i = 0; i < m; i++) {
		cout << "R" << i << " ";
	}

	for (int i = 0; i < n; i++) {
		cout << endl << "P" << i << "  ";
		for (int j = 0; j < m; j++) {
			cout << fixed << setw(2) << need[i][j] << " " ;
		}
	}
	// *********************************************************************************************



	system("pause");
	return 0;
}