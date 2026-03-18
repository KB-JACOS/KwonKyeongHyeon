#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>

using namespace std;
//100,000 * 100,000 = 10,000,000,000 => 4백억 바이트 > 256 * 1024 * 1024


class graph {
public:
	deque<deque<int>> neighbors;
	unordered_map<string, int> weights;
	string getKey(int s, int d) { return to_string(s) + "->" + to_string(d); }
};

graph _graph;
int n;

class info {
public:
	long long w;
	int cur;
};

info getMax(int s,int n) {
	deque<bool> reserved;
	deque<info> que;
	deque<info> results;

	reserved.assign(n + 1, false);
	que.push_back({0,s});
	reserved.at(s) = true;
	
	while (!que.empty()) {
		info curInfo=que.front();
		que.pop_front();

		deque<int>& neighbors = _graph.neighbors.at(curInfo.cur);

		bool isEnd = true;
		for (int& neighbor : neighbors) {
			if (reserved.at(neighbor)) {
				continue;
			}

			int& weight = _graph.weights.at(_graph.getKey(curInfo.cur,neighbor));

			que.push_back({weight+curInfo.w,neighbor });
			reserved.at(neighbor) = true;

			isEnd = false;
		}

		if (isEnd) {
			results.push_back(curInfo);
		}
	}

	info maxInfo = {-1,-1};
	for (info& info : results) {
		if (maxInfo.w < info.w) {
			maxInfo.w = info.w;
			maxInfo.cur = info.cur;
		}
	}

	return maxInfo;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	_graph.neighbors.assign(n + 1, {});

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		int s = x;

		while (true) {
			cin >> x;
			if (x == -1)
				break;

			int d = x;
			cin >> x;
			int w = x;

			_graph.neighbors.at(s).push_back(d);
			_graph.weights.insert({ _graph.getKey(s,d),w });
		}
	}

	info first=getMax(1, n);


	info second = getMax(first.cur, n);

	cout <<  second.w;

	return 0;
}