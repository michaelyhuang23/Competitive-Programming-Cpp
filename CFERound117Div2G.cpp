#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <queue>

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m; cin >> m;
    vector<llong> fact(1000005,1);
    for(int i = 2; i<1000005; i++) fact[i] = (fact[i-1]*i)%MOD;
    vector<int> cs(m);
    vector<bool> isO(m,0);
    For(i,m) cin >> cs[i];
    int oddC = 0;
    llong val = 0;
    For(i,m) if(cs[i]%2 == 1) {
    	oddC++; cs[i]--; isO[i] = 1;
    }
    int maxH = 0;
    For(i,m) cs[i]/=2; // basically the center is affecting the outer side unexpectedly
    For(i,m) maxH = max(maxH, cs[i]);
    priority_queue<int, vector<int>, greater<int> > pq;
    priority_queue<int, vector<int>, greater<int> > pqO;
    For(i,m) if(!isO[i]) pq.push(cs[i]);
    For(i,m) if(isO[i]) pqO.push(cs[i]);
    llong ways = 1;
    llong side = 0;
    for(int h = 0; h <= maxH; h++){
    	while(!pq.empty() && pq.top()==h){
    		pq.pop();
    	}
    	llong diff = (llong)(pq.size())+2LL*side+oddC;
    	val += ((((2LL*h+1LL)*diff)%MOD)*pq.size())%MOD;
    	val %= MOD;
    	side += pq.size();
    	ways *= fact[pq.size()];
    	ways %= MOD;
    	ways *= fact[pq.size()];
    	ways %= MOD;

        while(!pqO.empty() && pqO.top()==h){
            pqO.pop();
        }
        diff = (llong)(pqO.size())+2LL*side+oddC;
        val += ((((2LL*h+2LL)*diff)%MOD)*pqO.size())%MOD;
        val %= MOD;
        side += pqO.size();
        ways *= fact[pqO.size()];
        ways %= MOD;
        ways *= fact[pqO.size()];
        ways %= MOD;
    }
    ways*=fact[oddC];
    ways%=MOD;
    cout<<val<<" "<<ways<<endl;
}