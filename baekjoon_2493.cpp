#include <iostream>
#include <deque>

using namespace std;

deque<int> height;
deque<int> indexRecord;
int n;

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;
	height.assign(n + 1, 0);
	indexRecord.assign(n + 1, 0);
	height.at(0) = 100, 000, 001;

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;

		height.at(i) = x;

		if (i != 1) {
			int searchIdx = i - 1;

			while (searchIdx != 0) {
				if (height.at(searchIdx) >= height.at(i)) {
					indexRecord.at(i) = searchIdx;
					break;
				}
				else {
					searchIdx = indexRecord.at(searchIdx);
				}
			}
		}
	}

	indexRecord.pop_front();
	for (int& x : indexRecord) {
		cout << x << " ";
	}

	return 0;
}