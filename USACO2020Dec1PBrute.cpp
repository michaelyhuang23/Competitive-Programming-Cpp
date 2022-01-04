#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;

#define MOD 1000000007LL
#define pb push_back
#define mp make_pair
#define mt make_tuple

bool query(int num, int n, int r, int c){
	if(num & (1<<(r*n+c))) return true;
	else return false;
}

int main(){
	int n; cin >> n;
	vector<pair<int, int> > cows(n);
	vector<pair<int, int> > barns(n);
	for(int i=0;i<n;i++) {int a; cin >> a; cows[i]=mp(a,i);}
	for(int i=0;i<n;i++) {int a; cin >> a; barns[i]=mp(a,i);}
	int count = 0;
	int top = 1;
	for(int i=0;i<n*n;i++) top*=2;
	top --;
	for(int idx=0;idx<=top;idx++){
		bool suc = true;
		int jc, ic;
		for(int i=0;i<n;i++, ic=0) {
			if(!suc) break;
			for(int j=0;j<n;j++) 
				if(query(idx,n,i,j)) {
					if(cows[i].first>barns[j].first) {suc=false; break;} 
					if(++ic>1) {suc=false; break;}
				}
		}

		
		for(int j=0;j<n;j++, jc=0) {
			if(!suc) break;
			for(int i=0;i<n;i++) 
				if(query(idx,n,i,j)) {
					if(cows[i].first>barns[j].first) {suc=false; break;} 
					if(++jc>1) {suc=false; break;}
				}
		}

		//cout<<jc<<endl;
		if(!suc) continue;
		int lb = 0, mc = (int)1e9;
		for(int i=0;i<n;i++) {
			bool nope = true;
			for(int j=0;j<n;j++) if(query(idx,n,i,j)) {nope=false; break;}
			if(nope) mc = min(mc, cows[i].first);
		}
		for(int j=0;j<n;j++) {
			bool nope = true;
			for(int i=0;i<n;i++) if(query(idx,n,i,j)) {nope=false; break;}
			if(nope) lb = max(lb, barns[j].first);
		}
		if(mc>lb) {count++;
			// for(int i=0;i<n;i++){
			// 	for(int j=0;j<n;j++) cout<<query(idx,n,i,j);
			// 	cout<<endl;
			// }
			// cout<<endl;
		}
	}
	cout<<count<<endl;
	
}