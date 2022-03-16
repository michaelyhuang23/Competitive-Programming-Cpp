#include <bits/stdc++.h>
using namespace std;
 
void fastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
 
typedef long long ll;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;
int N, K, arr[300100], s_mn[300100], s_mx[300100];
ll dp[300100], psum[300100];
 
map<ll, int> mp;
 
int mxbit[300100], mnbit[300100], order[300100];
 
void U(int ind, int mn, int mx){
    while (ind <= N+1){
        mxbit[ind] = max(mxbit[ind], mx);
        mnbit[ind] = min(mnbit[ind], mn);
        ind += ind&(-ind);
    }
}
 
pair<int, int> S(int ind){
    pair<int, int> ret = {INF, -INF};
    while (ind > 0){
        ret.first = min(mnbit[ind], ret.first);
        ret.second = max(mxbit[ind], ret.second);
        ind -= ind&(-ind);
    }
    return ret;
}
 
bool work(ll val){
    for (int i = 1; i <= N+1; i++){
        mxbit[i] = -INF;
        mnbit[i] = INF;
    }
    for (int i = 1; i <= N+1; i++){
        s_mn[i] = INF;
        s_mx[i] = -INF;
    }
    s_mn[N+1] = 0;
    s_mx[N+1] = 0;
    U(order[N], 0, 0);
    for (int i = N; i >= 1; i--){
        auto it = mp.upper_bound(psum[i-1]+val);
        if (it == mp.begin()) continue;
        it--;
        pair<int, int> query = S((*it).second);
        if (query.first != INF)
            s_mn[i] = query.first+1;
        if (query.second != -INF)
            s_mx[i] = query.second+1;
        U(order[i-1], s_mn[i], s_mx[i]);
    }
    if (s_mn[1] <= K && s_mx[1] >= K) return true;
    return false;
}
 
//----Segtree #2------// 
vector<int> add[300100], rem[300100];
set<int> ss[300100]; //current integers for each node
int ST2[1200100];
 
void U2(int pos, int val, bool add, int n){
    int upd;
    if (add){
        ss[pos].insert(val);
        upd = *ss[pos].rbegin();
    } else {
        if (ss[pos].find(val) != ss[pos].end()) ss[pos].erase(ss[pos].find(val));
        if (ss[pos].empty()) upd = -1;
        else upd = *ss[pos].rbegin();
    }
    pos--;
    pos += n;
    ST2[pos] = upd;
    while (pos > 1) {
        pos >>= 1;
        ST2[pos] = max(ST2[2 * pos], ST2[2 * pos + 1]);
    }
}
 
int Q2(int l, int r, int n){
    l--, r--;
    l += n;
    r += n;
    int mi = -INF;
    while (l < r) {
        if (l & 1) {
            mi = max(mi, ST2[l]);
            l++;
        }
        if (r & 1) {
            r--;
            mi = max(mi, ST2[r]);
        }
        l /= 2;
        r /= 2;
    }
    return mi;
}
 
int main(){
    fastIO();
    int T; cin >> T;
    while (T--){
        cin >> N >> K;
        ll pos = 0, neg = 0;
        for (int i = 1; i <= N; i++){
            cin >> arr[i];
            if (arr[i] > 0) pos += arr[i];
            if (arr[i] < 0) neg += arr[i];
        }
        mp.clear();
        mp[0] = 0;
        for (int i = 1; i <= N; i++){
            psum[i] = psum[i-1]+arr[i];
            mp[psum[i]] = 0;
        }
        int ind = 0;
        for (auto it = mp.begin(); it != mp.end(); it++){
            mp[(*it).first] = ++ind;
        }
        for (int i = 0; i <= N; i++){
            order[i] = mp[psum[i]];
        }
        ll l = neg, r = pos;
        cout<<l <<" "<<r<<endl;
        int cc = 0;
        while (l != r){
            cc++;
            ll mid = (l+r)/2;
            if (l+r < 0 && (r-l)%2 == 1) mid--;
            if (work(mid)){
                r = mid;
            } else {
                l = mid+1;
            }
        }
        cout<<cc<<endl;
        work(l);
        for (int i = 0; i <= N+1; i++){
            ss[i].clear();
            add[i].clear();
            rem[i].clear();
            U2(i, 0, 0, N+1);
        }
        for (int i = 1; i <= N+1; i++){
            if (s_mx[i] != -INF)
                add[s_mx[i]].push_back(i);
            if (s_mn[i] != INF)
                rem[s_mn[i]].push_back(i);
            if (s_mn[i] < K && s_mx[i] >= K){
                U2(mp[psum[i-1]], i-1, 1, N+1);
            }
        }
        int cur = 0;
        int num = 0;
        while (num != K){
            for (int x : add[K-num-1]){
                U2(order[x-1], x-1, 1, N+1);
            }
            auto it = mp.upper_bound(psum[cur]+l);
            it--;
            int mx = Q2(1, (*it).second+1, N+1);
            U2(order[mx], mx, 0, N+1);
            for (int x : rem[K-num-1]){
                U2(order[x-1], x-1, 0, N+1);
            }
            cout << mx-cur;
            cur = mx;
            num++;
            if (num != K) cout << " ";
        }
        cout << "\n";
    }
}