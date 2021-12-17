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


using namespace std;

#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt;
    while(tt--) {
        iint n, x;
        cin >> n >> x;
        vector<iint> arr(n);
        For(i,n) cin >> arr[i];
        vector<iint> cpy =  arr;
        sort(cpy.begin(), cpy.end());
        iint left=x;
        iint right=n-1-x;
        if(right<left){
            bool suc = true;
            for(iint i = right+1; i<=left-1; i++) {
                if (arr[i] != cpy[i]) suc = false;
            }
            if(suc)
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }else {
            cout << "YES" << endl;
        }
    }
}

/*


 3 5 2 1 4
 3 1 2 5 4
 3 5 2 1 4
 1 4 2 3 5
 1 4 5 3 2
 1 2 5 3 4
 1 2 4 3 5
 4 2 1 3 5
 3 2 1 4 5
 1 2 3 4 5

 3 1 2 5 4 6
 5 1 2 3 4 6
 4 1 2 3 5 6
 3 1 2 4 5 6
 6 1 2 4 5 3
 6 1 3 4 5 2
 6 1 3 4 5 2


 3 2 1 4 5 6 5
 1 2 3 4 5 5 6

 1 2 3 3 4 5 5 6
*/