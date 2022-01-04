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
#define Mem(a, b) memset(a, (b), sizeof(a))
#define ForTo(i, j, k) for (int i=j ; i<=k ; i++)
#define For(i, j) ForTo(i, 0, j-1)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (int)2147483647
#define PI 3.1415926
typedef pair<int, int> ipair;
typedef vector<int> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        iint n;
        cin >>n;
        iint arr[n];
        For(i,n)
            cin>>arr[i];
        iint brr[n];
        iint crr[n];
        brr[0]=0;
        crr[0]=brr[0]^arr[0];
        for(int i=1; i<n; i++){
            iint prelim = crr[i-1]^arr[i];
            iint larger = 0;
            if(crr[i-1]>arr[i])
                larger = crr[i-1];
            else
                larger = arr[i];
            
            int l = 0;
            for(l=0;l<32;l++) if(larger<(1<<l)) break;
            iint c = crr[i-1];
            For(k,l) c^=(1<<k);
            iint flipper = c&arr[i];
            prelim^=flipper;
            brr[i] = prelim;
            crr[i] = brr[i]^arr[i];
        }
        For(i,n-1){
            cout<<brr[i]<<" ";
        }
        cout<<brr[n-1]<<'\n';
    }
}