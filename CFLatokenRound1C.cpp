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
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k) for (int i=j ; i<=k ; i++)
#define REP(i, j) FOR(i, 0, j-1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define MP make_pair
#define PB push_back
#define INF (int)2147483647
#define PI 3.1415926
typedef pair<int, int> ipair;
typedef vector<int> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
typedef long int iint;
typedef unsigned long int uint;
typedef long long int llong;
typedef unsigned long long int  ulong;
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        iint n;
        cin>>n;
        iint arr[2][n];
        iint pos[2][n];
        REP(i,n){
            cin>>arr[0][i];
            arr[0][i]--;
            pos[0][arr[0][i]]=i;
        }
        REP(i,n){
            cin>>arr[1][i];
            arr[1][i]--;
            pos[1][arr[1][i]]=i;
        }
        iint color[n];
        iint color_count = 0;
        MEM(color,0);
        REP(i,n){
            if(color[i]>0)
                continue;
            color_count++;
            color[i] = color_count;
            for(iint cur=pos[0][arr[1][i]]; cur!=i; cur=pos[0][arr[1][cur]]){
                assert(color[cur]==0);
                color[cur] = color_count;
            }
        }
        llong result = 1;
        while(color_count--){
            result*=2;
            result%=MOD;
        }
        cout<<result<<'\n';
    }
}