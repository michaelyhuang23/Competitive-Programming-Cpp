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
    	int str[n];
    	int fl=-1, fr=-1;
    	for(int i=0; i<n; i++) str[i] = (s[i]=='a' ? 1 : -1);
    	int prefix[n]; prefix[0] = str[0];
    	for(int i=1; i<n; i++) prefix[i] = prefix[i-1]+str[i];
    	for(int i=0; i<n; i++)
    		for(int j=i+1; j<n; j++){
    			int back = 0;
    			if(i>0) back = prefix[i-1];
    			int count = prefix[j]-back;
    			if(count == 0){
    				fl=i; fr=j;
    				break;
    			}
    		}
    	if(fl==-1 && fr==-1)
    		cout<<"-1 -1"<<endl;
    	else
    		cout<<fl+1<<" "<<fr+1<<endl;
    }
}







