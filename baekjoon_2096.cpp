#include <iostream>
#include <deque>

using namespace std;

//4mb => 4 1024 1024 => 4 * 1000000 => 4,000,000

// 6 * 4 * 100000 => 2,400,000

//6 * 100000 * 1

int n;

//deque<deque<char>> graph;//y,x

char arr[100000][3] = { 0, };

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;

	//graph.assign(n, {});

	for (int i = 0; i < n; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		arr[i][0] = x;
		arr[i][1] = y;
		arr[i][2] = z;
		//graph.at(i).push_back(x);
		//graph.at(i).push_back(y);
		//graph.at(i).push_back(z);
	}

	deque<int> temp;
	temp.assign(3, -1);
	temp.at(0) = arr[n - 1][0];
	temp.at(1) = arr[n - 1][1];
	temp.at(2) = arr[n - 1][2];
	for (int i = n - 1; i >= 1; i--) {

		int leftMax = max(temp.at(0), temp.at(1));
		int rightMax = max(temp.at(1), temp.at(2));

		int up = i - 1;
		temp.at(0) = arr[up][0] + leftMax;
		temp.at(2) = arr[up][2] + rightMax;
		temp.at(1) = arr[up][1] + max(leftMax, rightMax);
	}
	cout << max(max(temp.at(0), temp.at(1)), temp.at(2)) << " ";

	temp.at(0) = arr[n - 1][0];
	temp.at(1) = arr[n - 1][1];
	temp.at(2) = arr[n - 1][2];
	for (int i = n - 1; i >= 1; i--) {

		int leftMin = min(temp.at(0), temp.at(1));
		int rightMin = min(temp.at(1), temp.at(2));

		int up = i - 1;
		temp.at(0) = arr[up][0] + leftMin;
		temp.at(2) = arr[up][2] + rightMin;
		temp.at(1) = arr[up][1] + min(leftMin, rightMin);
	}
	cout << min(min(temp.at(0), temp.at(1)), temp.at(2)) << " ";

	return 0;
}