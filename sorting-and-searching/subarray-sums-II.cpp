#include<iostream>
#include <string>
#include <unordered_map>
#include<vector>
#include<algorithm>
#include<sstream>

typedef long long ll;
typedef unsigned long long ull;
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  ll n, x; cin >> n >> x;
  vector<ll> vec(n);
  for (auto& val : vec) cin >> val;

  unordered_map<ll, ll> mp_sum;
  ll curr = 0;

  ull ans = 0;
  for (auto& v : vec) {
    if (v + curr == x) ans++;
    if (mp_sum.count(v + curr - x)) ans += mp_sum[v + curr - x];
    mp_sum[v+curr]++;
    curr += v;
  }

  cout << ans << '\n';
}
