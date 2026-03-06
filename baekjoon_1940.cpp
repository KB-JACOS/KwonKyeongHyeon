#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

typedef long long ll;

int n;

deque<ll> arr;

void init() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		arr.push_back(x);

	}

	sort(arr.begin(), arr.end());
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	init();

	int count = 0;

	for (int i = n - 1; i >= 0; i--) {
		ll target = arr.at(i);

		int s = 0;
		int e = n - 1;

		while (s != e) {
			if (s == i) {
				++s;
				continue;
			}

			if (e == i) {
				--e;
				continue;
			}

			if (s == e)
				break;

			ll sum = arr.at(s) + arr.at(e);


			if (sum == target) {
				++count; break;
			}
			else if (sum > target) {
				--e;
			}
			else if (sum < target) {
				++s;
			}


		}

	}

	cout << count;

	return 0;
}