#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n, m;
vvi bd;
vvb visit;
int ct;
int max_area;

const auto dx = vi{ -1,1,0,0 };
const auto dy = vi{ 0,0,-1,1 };

int dfs(int i, int j) {
	auto st = stack<pii>{};
	st.push({ i, j });
	visit[i][j] = true;

	auto ret = 0;
	while (!st.empty()) {
		const auto [y, x] = st.top();
		st.pop();

		++ret;

		for (auto d = 0; d < 4; ++d) {
			const auto ny = y + dy[d];
			const auto nx = x + dx[d];

			if (ny < 0 || n <= ny ||
				nx < 0 || m <= nx) {
				continue;
			}

			if (0 == bd[ny][nx]) {
				continue;
			}

			if (visit[ny][nx]) {
				continue;
			}

			st.push({ ny, nx });
			visit[ny][nx] = true;
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;

	bd = vvi(n, vi(m));
	for (auto&& r : bd) {
		for (auto&& x : r) {
			cin >> x;
		}
	}

	visit = vvb(n, vb(m, false));
	ct = 0;
	max_area = 0;

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (0 == bd[i][j]) {
				continue;
			}

			if (visit[i][j]) {
				continue;
			}

			max_area = max(max_area, dfs(i, j));
			++ct;
		}
	}

	cout << ct << '\n'
		<< max_area;

	return 0;
}