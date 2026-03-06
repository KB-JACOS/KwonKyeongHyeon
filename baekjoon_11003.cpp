//11003

#include <iostream>
#include <deque>

using namespace std;

class Node {
public:
	int index;
	int value;

	Node(int index, int value) :index(index), value(value) {}
};

deque<Node> window;
deque<int> input;
deque<int> result;

int window_size;
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	cin >> window_size;

	input.assign(n + 1, 1000000001);

	for (int i = 1; i <= n; i++) {
		cin >> input.at(i);
	}

	for (int i = 1; i <= window_size - 1; i++) {
		input.push_front(1000000001);
	}

	for (int i = window_size; i <= n + (window_size - 1); i++) {
		int iter_value = input.at(i);

		if (window.empty()) {
			window.push_back(Node(i, iter_value));
		}
		else {
			while (window.back().value > iter_value) {
				window.pop_back();

				if (window.empty()) {
					break;
				}
			}

			window.push_back(Node(i, iter_value));
		}

		//------------------------------------------------

		while (!window.empty() && window.front().index < i - window_size + 1) {
			window.pop_front();
		}

		int x = window.front().value;
		result.push_back(x);
	}


	while (!result.empty()) {
		int x = result.front();
		result.pop_front();
		cout << x << " ";
	}

	return 0;
}