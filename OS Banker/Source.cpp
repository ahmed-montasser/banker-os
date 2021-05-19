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
	input = -1;
}

bool compare_LessOrEqual_vector(const vector<int> &a , const vector<int> &b) {
	
	if (a.size() == b.size()) {
		for (int u = 0; u < a.size(); u++) {
			if (a[u] > b[u]) {
				return false;
			}
		}
	}
	return true;
}



int index;

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
	vector<int> safe_sequence;

	// Reading Available Vector (START)
	cout << "Enter Available vector" << endl;

	for (int i = 0; i < m ; i++) {
		cout << "R" << i << " : " ;
		cin >> input;
		available[i]=input;
	}

	input = -1;
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
	// User enters request

	int req = -1;
	cout << endl << "Please enter \"1\" to check safe state \n or \"2\" to check immediate request possibility \n or \"0\" to exit : ";
	cin >> req;
	cout << endl;
	if (req == 0) {
		cout << "Thank U" << endl;
	}
	else if (req == 1) {

		//**********************************************************************************************
		//Safe Algorithm

		vector<int> work(available);

		vector<bool> finish(n);
		bool flag;
		bool flag2 = false;
		index = -1;
		int sum_current = 0;
		int past_sum = -1;

		safe_sequence.clear();
		while (!flag2) {
			flag2 = true;
			for (int i = 0; i < n; i++) {
				flag = true;
				if (!finish[i]) {
					for (int j = 0; j < m; j++) {
						if (need[i][j] > work[j])
						{
							flag = false;
							break;
						}
					}
					if (flag) { index = i; }

				}

				if (index != -1) {
					finish[index] = true;
					for (int i = 0; i < m; i++) {
						work[i] += allocation[index][i];
					}

					safe_sequence.push_back(index);

					index = -1;
				}
			}

			sum_current = 0;
			for (int i = 0; i < n; i++) {
				
				if (!finish[i]) {
					
					sum_current = sum_current + i;
					flag2=false;
				}
			}

			if (sum_current == past_sum && flag2==false) {
				cout << endl << "No , Not Safe state \n";
				return 0;
			}

			past_sum = sum_current;
		}
		cout << endl << "Yes , Safe state \n";
		for (int i = 0; i < safe_sequence.size() - 1; i++) {
			cout << "P" << safe_sequence[i] << " -> ";
		}
		cout << "P" << safe_sequence[safe_sequence.size() - 1] << endl;
	}

	else if(req ==2){
	//Resource-Request Algorithm
		vector<vector<int>> request(n);
		int index_request = -1;
		input = -1;
		cout << "Please Enter Number of Process \n(Processes indices are zero-Based , i.e First Process has index = 0)" << endl;
		cin >> index_request;

		// Take Request Vector
		for (int j = 0; j < m; j++) {
			cout << "Enter Number of instances for R" << j << " : ";
			cin >> input;
			request[index_request].push_back(input);
		}

		if (!compare_LessOrEqual_vector(request[index_request], need[index_request])) {
			cout << "Error condition, The Process has exceeded its maximum claim.";
			return 0; // End Program
		}
		

		if (!compare_LessOrEqual_vector(request[index_request],available)) {
			cout <<"P" << index_request << " must wait, as the resources are not available.";
			return 0; // End Program
		}

		for (int j = 0; j < m; j++) {
			available[j] = available[j] - request[index_request][j];
		}

		for (int j = 0; j < m; j++) {
			need[index_request][j] = need[index_request][j] - request[index_request][j];
		}
		for (int j = 0; j < m; j++) {
			allocation[index_request][j] = allocation[index_request][j] + request[index_request][j];
		}
		vector<int> work(available);

		vector<bool> finish(n);
		bool flag;
		bool flag2 = false;
		index = -1;
		int sum_current = 0;
		int past_sum = -1;


		safe_sequence.clear();
		finish[index_request] = true;
		for (int i = 0; i < m; i++) {
			work[i] += allocation[index_request][i];
		}
		safe_sequence.push_back(index_request);

		while (!flag2) {

			flag2 = true;

			for (int i = 0; i < n; i++) {
				if (i == index_request) {
					continue;
				}
				flag = true;
				if (!finish[i]) {
					for (int j = 0; j < m; j++) {
						if (need[i][j] > work[j])
						{
							flag = false;
							break;
						}
					}
					if (flag) { index = i; }

				}

				if (index != -1) {
					finish[index] = true;
					for (int i = 0; i < m; i++) {
						work[i] += allocation[index][i];
					}

					safe_sequence.push_back(index);;

					index = -1;
				}
			}

			
			for (int i = 0; i < n; i++) {

				if (!finish[i]) {
					sum_current += i;
					flag2 = false;
				}
			}
			sum_current = 0;
			if (sum_current == past_sum && !flag2) {
				cout << endl << "No request cannot be granted with safe state \n";
				//Restore Past Allocation State
				for (int j = 0; j < m; j++) {
					available[j] = available[j] + request[index_request][j];
				}

				for (int j = 0; j < m; j++) {
					need[index_request][j] = need[index_request][j] + request[index_request][j];
				}
				for (int j = 0; j < m; j++) {
					allocation[index_request][j] = allocation[index_request][j] - request[index_request][j];
				}
				cout << endl << "Past Resource-Allocation State is restored\n";

				system("pause");
				return 0; //End Program
			}
			past_sum = sum_current;
		}
		cout << endl << "Yes request can be granted with safe state , Safe state \n";
		cout << "P" << safe_sequence[0] << " (req) -> ";
		for (int i = 1; i < safe_sequence.size()-1; i++) {
			cout << "P" << safe_sequence[i] << " -> ";
		}
		cout << "P" << safe_sequence[safe_sequence.size()-1] << endl;
	//****************************************************************************************************
	}

	system("pause");
	return 0;
}