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

llong dpl[1001][1001] = {0};
llong dpr[1001][1001] = {0};
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n; cin >> n;
    vector<llong> arr(n+1);
    For(i,n) cin >> arr[i+1];

    for(iint i=1;i<=n;i++){
    	if(i%2==0)
    		dpl[i][i] = arr[i];
    	else
    		dpr[i][i] = arr[i];
    }
    for(iint r=2; r<=n; r++){
    	for(iint i=1;i<n;i++){
    		iint j = i+r-1;
    		if(j>n) continue;
    		llong radd=0, ladd=0;
    		if(i%2==1){
    			dpl[i][j] = dpl[i+1][j] - arr[i];
    			// if(i==2 && j==4)
    			// 	cout<<dpl[i][j]<<endl;
    			if(dpl[i][j]<0){
    				//radd = -dpl[i][j];
    				dpl[i][j]=0;
    			}
    		}else{
    			dpl[i][j] = dpl[i+1][j] + arr[i];
    		}
    		if(j%2==1){
    			dpr[i][j] = dpr[i][j-1] + arr[j];
    		}else{
    			dpr[i][j] = dpr[i][j-1] - arr[j];
    			if(dpr[i][j]<0){
    				//ladd = -dpr[i][j];
    				dpr[i][j]=0;
    			}
    		}
    		// if(i==2 && j==4)
    		// 	cout<<dpl[i][j]<<endl;
    		//dpl[i][j] += ladd;
    		//dpr[i][j] += radd;
    	}
    }
    // for(iint i=1; i<=n; i++){
    // 	for(iint j=1; j<=n; j++)
    // 		cout<<dpl[i][j]<<" ";
    // 	cout<<endl;
    // }
    // for(iint i=1; i<=n; i++){
    // 	for(iint j=1; j<=n; j++)
    // 		cout<<dpr[i][j]<<" ";
    // 	cout<<endl;
    // }

    llong total = 0;
    for(iint i=1; i<=n; i+=2){
    	for(iint j=i+1; j<=n; j+=2){
    		assert((j-i)%2==1);
    		llong rem = 0;
    		llong ln = dpl[i+1][j-1];
    		llong rn = dpr[i+1][j-1];
    		llong lrem = arr[i]-ln;
    		llong rrem = arr[j]-rn;
    		if(ln==0) lrem--;
    		if(rn==0) rrem--;
    		if(lrem>=0 && rrem>=0){
	    		rem = min(lrem, rrem)+1;
	    		total+=rem;
	    	}
    	}
    }
    cout<<total<<endl;
}




/*

5
4 1 2 3 1

4*( 1*) 2*( 3*) 1*(
get immediate seqs easily

permute (i,j) of compressed form. 
4*( 1*) 2*( 3*)
get prefix alternating sum = 2
need to abandon at least 2 fronts
from there: abandon front and back simultaneously


range DP
to determine extern help needed of subseq
if i is left
externl[i][j]=externl[i+1][j]-arr[i]
if i is right
externl[i][j]=externl[i+1][j]+arr[i]




*/





