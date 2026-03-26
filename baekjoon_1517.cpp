#include <iostream>

#include <string>

#include <deque>

#include <algorithm>

using namespace std;

struct node {
	int val;
	int idx;

	bool operator==(const node& n)const {
		return val == n.val && idx == n.idx;
	}

	bool operator!= (const node& n)const {
		return !((*this) == n);
	}

	bool operator<(const node& n)const {
		if (val == n.val)
			return idx < n.idx;
		return val < n.val;
	}

	bool operator>(const node& n)const {
		return n < (*this);
	}

	bool operator<=(const node& n) const {
		return !((*this) > n);
	}

	bool operator>=(const node& n)const {
		return !((*this) < n);
	}
};

void parse(string str, deque<node>& cmd) {
	int len = str.length() - 1;

	int cmdidx = 0;
	int num = 0;
	bool neg = false;

	for (int i = 0; i <= len; i++) {
		char c = str.at(i);

		switch (c) {
		case ' ':
			if (neg) {
				num *= -1;
			}

			cmd.push_back({ num,cmdidx });

			++cmdidx;
			num = 0;
			neg = false;
			break;
		case '-':
			neg = true;
			break;
		default:
			num = num * 10 + (c - '0');
			break;
		}
	}

	if (neg) {
		num *= -1;
	}

	cmd.push_back({ num,cmdidx });

	return;
}

void mergesort(deque<node>& cmd, long long& result, int start, int end) {
	if (start >= end) {
		return;
	}

	int mid = (start + end) / 2;

	int lefti = start;
	int righti = mid + 1;

	mergesort(cmd, result, start, mid);
	mergesort(cmd, result, mid + 1, end);

	deque<node> temp;


	while (true) {
		if (lefti > mid || righti > end)
			break;

		if (cmd.at(lefti) <= cmd.at(righti)) {
			temp.push_back(cmd.at(lefti));
			++lefti;
		}
		else {
			temp.push_back(cmd.at(righti));
			++righti;
		}
	}

	if (lefti > mid) {
		while (righti <= end) {
			temp.push_back(cmd.at(righti));
			++righti;
		}
	}
	else {
		while (lefti <= mid) {
			temp.push_back(cmd.at(lefti));
			++lefti;
		}
	}

	int len = temp.size() - 1;

	for (int i = 0; i <= len; i++) {
		int absidx = i + start;

		if (temp.at(i).idx - absidx <= 0) {
			result += (absidx - temp.at(i).idx);
		}

		temp.at(i).idx = absidx;
		cmd.at(absidx) = temp.at(i);
	}

	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	cin.ignore();

	string str;
	getline(cin, str);

	deque<node> cmd;
	parse(str, cmd);

	long long result = 0;


	mergesort(cmd, result, 0, cmd.size() - 1);


	cout << result;
	return 0;
}