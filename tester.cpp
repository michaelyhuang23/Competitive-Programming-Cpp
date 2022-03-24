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
	int n=200,q=200;
	int R = (int)1e9;
	cout<<n<<endl;
	for(int i=0;i<n;i++) cout<<random(1,R)<<" ";
	cout<<endl;
	cout<<q<<endl;
	for(int i=0;i<q;i++){
		int l=random(0,n-1);
		int r=random(0,n-1);
		if(l>r) swap(l,r);
		cout<<l<<" "<<r<<" "<<random(-R,R)<<endl;
	}
}



/*

generate tree:
for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

*/