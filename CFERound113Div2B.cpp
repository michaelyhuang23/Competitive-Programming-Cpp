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
    	int n; cin >> n;
    	string s; cin >> s;
    	bool types[n];
    	for(int i=0; i<n; i++) types[i] = (s[i] == '2');
    	int twoCount = 0;
    	for(int i=0; i<n; i++) if(types[i]) twoCount++;
    	if(twoCount>0 && twoCount<=2){
    		cout<<"NO"<<endl;
    		continue;
    	}else{
    		cout<<"YES"<<endl;
    	}
    	char connect[n][n];
    	for(int i=0; i<n; i++)
    		for(int j=0; j<n; j++) connect[i][j]='=';
    	for(int i=0; i<n; i++) connect[i][i]='X';
    	vector<int> twoPos;
    	for(int i=0; i<n; i++) if(types[i]) twoPos.pb(i);
    	for(int i=0; i<(int)twoPos.size()-1; i++){
    		connect[twoPos[i]][twoPos[i+1]]='+';
    		connect[twoPos[i+1]][twoPos[i]]='-';
    	}
    	if(twoPos.size()>0){
	    	connect[twoPos[twoPos.size()-1]][twoPos[0]]='+';
	    	connect[twoPos[0]][twoPos[twoPos.size()-1]]='-';
	    }
    	for(int i=0; i<n; i++){
    		for(int j=0; j<n; j++)
    			cout<<connect[i][j];
    		cout<<endl;
    	}
    }
}

/*

satisfy no loss players first: all =
for 1 win players, they can't win against a no-loss 
but only other 1 win
if there're >2 1 win players, we simply draw a loop around them
no loss player can't receive an edge and doesn't make sense to spawn
one either

*/