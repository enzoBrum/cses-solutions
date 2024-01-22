#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include<iostream>
#include <string>
#include <unordered_map>
#include<vector>
#include<algorithm>
#include<sstream>




/**
- idndice ta erradoç
*/
















typedef long long ll;
typedef unsigned long long ull;
using namespace std;

class UnionFind {
  public:
    UnionFind(int n, const vector<int>& vec) {
      total_groups = n;
      size.assign(n, 1);
      parent.resize(n);
      right.resize(n);
      left.resize(n);
      sum.resize(n);
      
      for (int i = 0; i < n; ++i) {
        sum[i] = vec[i];
        left[i] = i - 1;
        right[i] = i + 1;
        parent[i] = i;
      }
    }

    int find_set(int a) {
      if (parent[a] == a)
        return a;
      return parent[a] = find_set(parent[a]);
    }

    void union_set(int a, int b) {
      int pa = parent[a], pb = parent[b];
      if (pa == pb) return;
      
      total_groups--;
      
      if (size[b] > size[a])
        swap(a, b);

      parent[b] = a;
      size[a] += size[b];
      sum[a] += sum[b];
    }
    
    ll get_sum(int a) {
      return sum[ find_set(a) ];
    }

    vector<int> parent, size, left, right;
    vector<ll> sum;
    int total_groups = 0;
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, k;
  cin >> n >> k;
  vector<int> vec(n);
  for (auto& v : vec) cin >> v;

  UnionFind uf(n, vec);
  set<pair<ll, int>> st;
  set<int> idx;

  for (int i = 0; i < n; ++i) {
    st.insert({vec[i], i});
    idx.insert(i);
  }
  while (uf.total_groups != k) {
    auto it = st.begin();
    int ia = it->second;
    ll va = it->first;

    int il = -1;
    ll vl = 1e9;
    int ir = n;
    ll vr = 1e9;

    auto idx_it = idx.find(ia);
    if (idx_it != idx.begin()) {
      il = *prev(idx_it);
      vl = uf.get_sum(il);
    }
    if (idx_it != prev(idx.end())) {
      ir = *next(idx_it);
      vr = uf.get_sum(ir);
    }
    
    int i_chosen;
    ll v_chosen;
    if(uf.find_set(il) != uf.find_set(ia) && (vl < vr || uf.find_set(ir) == uf.find_set(ia))) {
      i_chosen = il;
      v_chosen = vl;
    }
    else {
      i_chosen = ir;
      v_chosen = vr;
    }
    
    st.erase(it);
    st.erase({i_chosen, v_chosen});
    idx.erase(idx_it);
    idx.erase(i_chosen);
    
    uf.union_set(ia, i_chosen);
    st.insert({uf.get_sum(ia), uf.find_set(ia)});
    idx.insert(uf.find_set(ia));
  }

  ll ans = 0;
  for (auto&[v, i] : st) ans = max(ans, v);
  cout << ans << '\n';
}
