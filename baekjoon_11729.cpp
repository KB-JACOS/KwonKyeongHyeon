#include <iostream>
#include <string>

using namespace std;

string result;
int counts = 0;

void func(int n, int from, int mid, int go) {
	++counts;
	if (n == 1) {
		string str = to_string(from) + " " + to_string(go) + "\n";
		result += str;
	}
	else {
		--n;
		func(n, from, go, mid);
		string str = to_string(from) + " " + to_string(go) + "\n";
		result += str;
		func(n, mid, from, go);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	func(n, 1, 2, 3);

	cout << counts << "\n";
	cout << result;

	return 0;
}