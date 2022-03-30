#include<bits/stdc++.h>
//#include "debughelp.hpp"

using namespace std;

typedef long long llong;

#define MOD 1000000007LL
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

int random(int st, int ed){
	if(st==ed) return st;
	return rand()%(ed-st+1)+st;
}

int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n=5000,m=10000,q=100000;
	cout<<n<<" "<<m<<endl;

	for(int i=0;i<m;i++) {
		int l = random(1,n);
		int r = random(1,n);
		if(l == r){i--; continue;}
		cout<<l<<" "<<r<<endl;
	}
	cout<<q<<endl;
	for(int i=0;i<q;i++){
		int l=random(1,n);
		int r=random(1,n);
		cout<<l<<" "<<r<<endl;
	}
}



/*

generate tree:
for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

*/