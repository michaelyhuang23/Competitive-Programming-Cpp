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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt; cin >> tt;
    while(tt--){
        iint n; cin >> n;
        vector<iint> arr(n);
        For(i,n) cin >> arr[i];
        iint oddCount = 0;
        For(i,n) oddCount += arr[i];
        if(oddCount%2 == 1 || oddCount == n) {
            cout << "NO" << endl;
        }
        vector<iint> ops; ops.reserve(n);
        if(arr[0] == 0 || arr[n-1] == 0) {
            cout << "YES" << endl;
            if(arr[0]==0)
                for(iint i = 0; i<n-2; i++){
                    if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                        ops.pb(i);
                        arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                    }
                }
            if(arr[n-1]==0)
                for(iint i = n-3; i>=0; i--){
                    if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                        ops.pb(i);
                        arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                    }
                }
            For(i,n) assert(arr[i] == 0);
            cout<< ops.size() << endl;
            if(ops.size()>0) {
                For(i, (iint) ops.size() - 1) cout << ops[i]+1 << " ";
                cout << ops[ops.size() - 1]+1 << endl;
            }
            continue;
        }
        iint zeroPos = -1;
        For(i,n) if(arr[i]==0){
            if(arr[i-1]==1 && arr[i+1]==1)
        }
        assert(zeroPos != -1);
        iint leftC=0, rightC=0;
        For(i,zeroPos) leftC += arr[i];
        for(iint i=zeroPos+1; i<n; i++) rightC += arr[i];
        if(leftC%2==0){
            assert(rightC%2==0);
            for(iint i=zeroPos-2; i>=0; i--){
                if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                    ops.pb(i);
                    arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                }
            }
            for(iint i=zeroPos; i<n-2; i++){
                if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                    ops.pb(i);
                    arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                }
            }
            cout<<"YES"<<endl;
            For(i,n) assert(arr[i] == 0);
            cout<< ops.size() << endl;
            if(ops.size()>0) {
                For(i, ops.size() - 1) cout << ops[i]+1 << " ";
                cout << ops[ops.size() - 1]+1 << endl;
            }
            continue;
        }else{
            assert(rightC%2==1);
            ops.pb(zeroPos-1);
            arr[zeroPos-1] = 0; arr[zeroPos] = 0; arr[zeroPos+1] = 0;
            for(iint i=zeroPos-3; i>=0; i--){
                if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                    ops.pb(i);
                    arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                }
            }
            for(iint i=zeroPos+1; i<n-2; i++){
                if(arr[i]+arr[i+1]+arr[i+2] == 2) {
                    ops.pb(i);
                    arr[i] = 0; arr[i+1] = 0; arr[i+2] = 0;
                }
            }
            cout<<"YES"<<endl;
            For(i,n) assert(arr[i] == 0);
            cout<< ops.size() << endl;
            if(ops.size()>0) {
                For(i, ops.size() - 1) cout << ops[i]+1 << " ";
                cout << ops[ops.size() - 1]+1 << endl;
            }
            continue;
        }
    }
}