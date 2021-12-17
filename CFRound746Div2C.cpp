#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

llong dfs(iint cur, iint par, vector<llong>& vals, vector<vector<iint>>& adj, vector<llong>& subVal){
    llong summ = 0;
    for(iint child : adj[cur]){
        if(child == par) continue;
        summ ^= dfs(child, cur, vals, adj, subVal);
    }
    //cout<<cur<<" "<<vals[cur]<<" "<<summ<<endl;
    subVal[cur] = summ^vals[cur];
   // cout<<cur<<" "<<subVal[cur]<<endl;
    return subVal[cur];
}

pair<iint,iint> traverse(iint cur, iint par, llong target, vector<llong>& subVals, vector<vector<iint>>& adj){
    iint count1 = 0, count2 = 0;
    for(iint child : adj[cur]){
        if(child == par) continue;
        auto ret = traverse(child, cur, target, subVals, adj);
        count1 += ret.first;
        count2 += ret.second;
    }
    if(cur !=0 && subVals[cur] == target) {
        count1++;
    }
    if(cur != 0 && (subVals[0]^subVals[cur]) == target){
        count2++;
    }
    return make_pair(count1, count2);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt; cin >> tt;
    while(tt--){
        iint n, k;
        cin >> n >> k;
        vector<llong> arr(n);
        For(i,n) cin >> arr[i];
        vector<vector<iint>> adj(n);
        For(i,n) adj[i] = vector<iint>();
        For(i,n-1) {
            iint a, b;
            cin >> a >> b;
            a--; b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<llong> subVal(n);
        dfs(0,0,arr,adj,subVal);
        if(subVal[0]==0){
            cout<<"YES"<<endl;
        }else{
            auto ret = traverse(0,0,subVal[0],subVal,adj);
            if(k<3)
                cout<<"NO"<<endl;
            else if(ret.first>1 || ret.first==1 && ret.second>0)
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
}
