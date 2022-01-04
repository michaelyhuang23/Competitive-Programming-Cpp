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
    	iint n; cin >> n;
    	vector<bool> arr(n);
    	For(i,n){
    		llong num; cin >> num;
    		arr[i] = num%2;
    	}
    	// deb(arr);
    	iint oddC = 0, evenC = 0;
    	For(i,n) if(arr[i]) oddC++;
    	For(i,n) if(!arr[i]) evenC++;
    	vector<iint> oddPos;
    	For(i,n) if(arr[i]) oddPos.pb(i);
    	if(n%2==1){
    		if(abs(oddC-evenC) != 1){
    			cout<<-1<<endl;
    			continue;
    		}
    	}else{
    		if(oddC!=evenC){
    			cout<<-1<<endl;
    			continue;
    		}
    	}
    	vector<iint> target1;
    	vector<iint> target2;
    	For(i,n) if(i%2==1) target1.pb(i);
    	For(i,n) if((i+1)%2==1) target2.pb(i);
    	// deb(target1);
    	// deb(target2);
    	// deb(oddPos);
    	// target2 has 1 more odd when n is odd
    	llong dist1=-1,dist2=-1,minDist=inf;
    	if(target1.size() == oddPos.size()){
	    	dist1 = 0;
	    	For(i,oddC){
	    		llong pos = oddPos[i];
	    		llong ePos = target1[i];
	    		dist1 += abs(pos - ePos);
	    	}
	    	minDist = min(minDist,dist1);
	    }
	    if(target2.size() == oddPos.size()){
	    	dist2 = 0;
	    	For(i,oddC){
	    		llong pos = oddPos[i];
	    		llong ePos = target2[i];
	    		dist2 += abs(pos - ePos);
	    	}
	    	minDist = min(minDist,dist2);
	    }
	    assert(dist1 != -1 || dist2 != -1);
	    cout<<minDist<<endl;

    }
}






/*

010101
6 2 3 4 5 1
001011

*/