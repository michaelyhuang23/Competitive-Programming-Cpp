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
#include <math.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i = 0; i < j; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        iint arr[n];
        For(i, n) cin >> arr[i];
        iint len = 1 << n;
        bool success = false;
        for (iint i = 1; i < len; i++) {
            vector<iint> nums;
            For(j, n) if (i & (1 << j)) nums.pb(j);
            iint signs = 1 << nums.size();
            For(j, signs){
                llong sum = 0;
                For(k, nums.size())
                {
                    if (j & (1 << k))
                        sum += arr[nums[k]];
                    else
                        sum -= arr[nums[k]];
                }
                if (sum == 0)
                {
                    success = true;
                    break;
                }
            }
            if(success)
                break;
        }
        if (success)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}