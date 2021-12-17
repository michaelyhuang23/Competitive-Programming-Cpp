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

inline llong decomCount(int num){
	if(num<10) return num+1;
	return 9 - (num - 9) + 1;
}

inline llong dfs(vector<int> num, int pos){
	if(pos>=num.size()) return 1;
	llong count = 0;
	int req = num[pos]; // mind negative
	if(req>=0)
		count += decomCount(req) * dfs(num, pos+1);
	req += 10;
	if(pos+2 < num.size()){
		num[pos+2]--;
		count += decomCount(req) * dfs(num, pos+1);
	}
	return count; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    while(tt--){
    	string s; cin>>s;
    	vector<int> num;
    	for(int i=s.length()-1; i>=0; i--) num.pb((int)s[i] - (int)('0'));
    	cout<<dfs(num,0)-2<<endl;
    }
}


/*

for each digit, any two pairs that add up to the same is the same
this is just a lower bound

if a digit doesn't add to same number, it must differ by 10, the digit
it carries to must be 1 bigger or smaller. 

so each digit has 2 choice, x or 1x

so if we permute them all, that's only 2^9

*/