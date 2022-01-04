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
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    REP(i,t){
        int n;
        cin>>n;
        int arr[n];
        REP(j,n){
            cin>>arr[j];
        }
        if(n==1){
            cout<<arr[0]<<'\n';
            continue;
        }
        int64 save = 0;
        if(n>1 && arr[0]>arr[1])
            save+=arr[0]-arr[1];
        if(n>1 && arr[n-1]>arr[n-2])
            save+=arr[n-1]-arr[n-2];
        FOR(k,1,n-2){
            if(arr[k]>arr[k-1] && arr[k]>arr[k+1])
                save+=arr[k]-max(arr[k-1],arr[k+1]);
        }
        int64 orig = arr[0]+arr[n-1];
        FOR(k,1,n-1){
            orig+=abs(arr[k]-arr[k-1]);
        }
        cout<<orig-save<<'\n';
    }
}