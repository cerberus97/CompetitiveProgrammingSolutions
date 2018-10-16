/* cerberus97 - Hanit Banga

Solution: I store at each index i, the set of k values for which I next have to start a component at i.
Also for each color c, I keep the smallest index larger than i where c occurs in an order statistics tree.
Now to find the component size for k starting at i, I just need to find the (k + 1)th smallest element 
in the tree. When moving from i to i + 1, I need to erase one value from the tree and possibly add one 
more to it.

Complexity is O(nlog^2(n)) because for each k, we search <= n / k times and each search requires O(log(n)).
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

template<typename has_less>
using ordered_set =
tree<has_less,
	null_type,
	less<has_less>,
	rb_tree_tag,
	tree_order_statistics_node_update>;

const int N = 1e5 + 10;

int a[N], ans[N];
queue<int> indices[N], srch[N];

int main() {
	fast_cin();
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		indices[a[i]].push(i);
	}
	ordered_set<int> st;
	for (int i = 1; i <= n; ++i) {
		if (!indices[i].empty()) {
			st.insert(indices[i].front());
		}
	}
	for (int k = 1; k <= n; ++k) {
		srch[1].push(k);
	}
	for (int i = 1; i <= n; ++i) {
		while (!srch[i].empty()) {
			int k = srch[i].front();
			srch[i].pop();
			++ans[k];
			if (st.size() < k + 1) {
				continue;
			}

			auto tmp = st.find_by_order(k);
			srch[*tmp].push(k);
		}
		st.erase(i);
		indices[a[i]].pop();
		if (!indices[a[i]].empty()) {
			st.insert(indices[a[i]].front());
		}
	}
	for (int k = 1; k <= n; ++k) {
		cout << ans[k] << ' ';
	}
}