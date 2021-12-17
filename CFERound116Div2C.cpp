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
#include <unordered_map>
#include <unordered_set>
#include <fstream>


using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<llong> exps(10);
    exps[0] = 1;
    for(iint i=1; i<10; i++) exps[i] = exps[i-1]*10;
    iint tt; cin >> tt;
    while(tt--){
        llong n, k;
        cin >> n >> k;
        k++;
        vector<llong> arr(n);
        For(i,n) cin >> arr[i];
        vector<llong> preft(n);
        preft[0] = 0;
        llong ans = 0;
        for(iint i = 1; i<n; i++) preft[i] = preft[i-1] + exps[arr[i]]/exps[arr[i-1]]-1;
        for(iint i=1; i<n; i++){
            if(preft[i] >= k){
                llong left = k - preft[i-1];
                ans = exps[arr[i-1]]-1;
                ans+=exps[arr[i-1]]*left; // watch logic
                break;
            }
        }
        if(ans>0){
            cout<<ans<<endl;
            continue;
        }
        ans = exps[arr[n-1]]-1;
        ans += (k-preft[n-1])*exps[arr[n-1]]; // watch logic
        cout<<ans<<endl;
    }
}

/*
 0 3 7 9
 (10^3-1) + (10^7/10^3-1) + (10^9/10^7-1)

 */

