#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_set>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple

int n, m;
vector<vector<int>> adj, badj;
vector<unordered_set<int>> behind, ahead;
bool check_cycle(vector<int> deg){
    queue<int> pq;
    for(int i=0;i<n;i++) if(deg[i] == 0) pq.push(i);
    while(!pq.empty()){
        int cur = pq.front(); pq.pop();
        for(int son : adj[cur]) if(deg[son]!=0){
            deg[son]--;
            if(deg[son]==0) pq.push(son);
        }
    }
    bool cycle = false;
    for(int i=0;i<n;i++) if(deg[i]>0) cycle=true;
    return cycle;
}
void compute_behind(vector<int> deg){
    queue<int> pq;
    behind = vector<unordered_set<int>>(n);
    for(int i=0;i<n;i++) behind[i].insert(i);
    for(int i=0;i<n;i++) if(deg[i] == 0) pq.push(i);
    while(!pq.empty()){
        int cur = pq.front(); pq.pop();
        for(int son : adj[cur]) if(deg[son]!=0){
            behind[son].insert(behind[cur].begin(), behind[cur].end());
            deg[son]--;
            if(deg[son]==0) pq.push(son);
        }
    }
}
void compute_ahead(vector<int> deg){
    queue<int> pq;
    ahead = vector<unordered_set<int>>(n);
    for(int i=0;i<n;i++) ahead[i].insert(i);
    for(int i=0;i<n;i++) if(deg[i] == 0) pq.push(i);
    while(!pq.empty()){
        int cur = pq.front(); pq.pop();
        for(int son : badj[cur]) if(deg[son]!=0){
            ahead[son].insert(ahead[cur].begin(), ahead[cur].end());
            deg[son]--;
            if(deg[son]==0) pq.push(son);
        }
    }
}
void solve(){
    cin >> n >> m;
    int d = n/2;
    adj = vector<vector<int>>(n);
    badj = vector<vector<int>>(n);
    vector<int> deg(n,0), bdeg(n,0);
    for(int i=0;i<m;i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[b].pb(a);
        badj[a].pb(b);
        deg[a]++;
        bdeg[b]++;
    }
    if(check_cycle(deg)){
        for(int i=0;i<n;i++) cout<<"0";
        cout<<endl;
        return;
    }
    compute_behind(deg);
    compute_ahead(bdeg);

    for(int i=0;i<n;i++){
        int cahead = n-behind[i].size();
        int cbehind = n-ahead[i].size();
        if(cahead>=d && cbehind>=d) cout<<"1";
        else cout<<"0";
    }
    cout<<endl;
}

int main(){
    int tt; cin >> tt;
    while(tt--) solve();
}
