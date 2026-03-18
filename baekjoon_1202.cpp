#include <iostream>
#include <deque>
#include <algorithm>
#include <queue>

using namespace std;

int n;
class info {
public:
	int w;
	int p;

	bool operator>(const info& o) const {
		if (this->p == o.p)
			return this->w < o.w;

		return this->p > o.p;
	}
	bool operator<=(const info& o) const {
		return !(*(this) > o);
	}
	bool operator<(const info& o) const {
		if (this->p == o.p)
			return this->w > o.w;

		return this->p < o.p;
	}
	bool operator>=(const info& o)const {
		return !(*(this) > o);
	}
	bool operator==(const info& o) const {
		return (this->p == o.p) && (this->w == o.w);
	}
};
deque<info> things;
deque<bool> reserved;

class pred {
public:
	bool operator()(const info& a, const info& b) {
		return a.w < b.w;
	}
};

int k;
class bag {
public:
	int size;
	int searchEndIdx;

	bool operator>(const bag& o) {

		return this->size > o.size;
	}
	bool operator<=(const bag& o) {
		return !(*(this) > o);
	}
	bool operator<(const bag& o) {

		return this->size < o.size;
	}
	bool operator>=(const bag& o) {
		return !(*(this) > o);
	}
	bool operator==(const bag& o) {
		return (this->size == o.size);
	}
};
deque<bag> bags;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	cin >> k;

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		int d;
		cin >> d;
		things.push_back({ x,d });
	}
	reserved.assign(n, false);

	for (int i = 1; i <= k; i++) {
		int x;
		cin >> x;
		bags.push_back({x,-1});
	}

	sort(things.begin(), things.end(),pred());
	sort(bags.begin(), bags.end());

	int j = 0;
	for (int i = 0; i < k; i++) {
		bag& curBag = bags.at(i);
		for (; j < n; j++) {
			info& thing = things.at(j);
			if (thing.w > curBag.size)
				break;
		}
		curBag.searchEndIdx = j;
	}


	priority_queue<info> pq;

	int bagIdx = 0;
	int thingsIdx = 0;

	long long sum = 0;
	while (bagIdx < k) {
		bag& curBag = bags.at(bagIdx);

		for (; thingsIdx < curBag.searchEndIdx; thingsIdx++) {
			pq.push(things.at(thingsIdx));
		}

		if (!pq.empty()) {
			sum+=pq.top().p;
			pq.pop();
		}

		++bagIdx;
	}

	cout << sum;
	return 0;
}