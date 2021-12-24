#include<iostream>
#include<vector>
#include<assert.h>
#include <set>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--){
		llong n; cin >> n;
		vector<llong> cost;
		set<llong> scost;
		for(llong i=0;i<n;i++) {
			llong a;
			cin >> a;
			scost.insert(a);
		}
		for(llong s : scost) cost.pb(s);

		n = cost.size();

		llong maxx = cost[n-1];
		//cout<<maxx<<endl;
		vector<llong> mc(n);
		vector<bool> hasx(3,0);
		for(llong i=0;i<n;i++) mc[i] = cost[i]%3;
		for(llong i=0;i<n;i++) hasx[mc[i]] = true;
		llong a=0,b=0,c=0;
		llong result = 1000000000;
		if(maxx%3 == 0){
			// 3 cases
			c = maxx/3;
			if(hasx[1]) a = 1;
			if(hasx[2]) b = 1;
			result = min(result, a+b+c);

			a = b = c = 0;
			c = maxx/3-1;
			b = 1; a = 1;
			result = min(result, a+b+c);

			//a = b = c = 0;
			// impossible to win.

		}else if(maxx%3 == 1){
			// two cases
			c = maxx/3;
			a = 1;
			if(hasx[2]) b = 1;
			result = min(result, a+b+c);

			a = b = c = 0;
			c = maxx/3-1;
			b = 2;
			if(n-2 >=0 && cost[n-2] == (c+1)*3 || cost[0] == 1) a = 1;
			result = min(result, a+b+c);
		}else{
			c = maxx/3;
			b = 1;
			if(hasx[1]) a = 1;
			result = min(result, a+b+c);
		}
		cout<<result<<endl;
	}
}
