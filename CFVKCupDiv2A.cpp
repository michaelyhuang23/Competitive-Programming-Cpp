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
    int tt; cin >> tt;
    while(tt--){
    	int n;
    	cin >> n;
    	int arr[n+1];
    	For(i,n) cin >> arr[i+1];
    	//n is odd
    	iint lastIter = 0;
    	for(int j=1; j<=2*n; j++){
    		if(j%2==1)
	    		for(int i=1; i<n; i+=2){
	    			if(arr[i]>arr[i+1]){
	    				swap(arr[i],arr[i+1]);
	    				lastIter = j;
	    			}
	    		}
	    	else
	    		for(int i=2; i<n; i+=2){
	    			if(arr[i]>arr[i+1]){
	    				swap(arr[i],arr[i+1]);
	    				lastIter = j;
	    			}
	    		}
    	}
    	int arrcpy[n+1];
    	copy(arr, arr+n+1, arrcpy);
    	arrcpy[0]=0;
    	sort(arrcpy, arrcpy+n+1);
    	for(int i=1; i<=n; i++)
    		assert(arrcpy[i] == arr[i]);
    	cout<<lastIter<<endl;
    }

}