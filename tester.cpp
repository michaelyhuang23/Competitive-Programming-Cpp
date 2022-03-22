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
	int n = 3, m=3;
	cout<<n<<" "<<m<<endl;
	int w = 2;
	for(int r=0;r<n;r++){
		for(int c=0;c<m-1;c++){
			cout<<random(1,w)<<" ";
		}
		cout<<endl;
	}

	for(int i=1;i<=m;i++){
		int p = random(1, n);
		cout<<p<<" "<<random(1,cr)<<endl;
	}
}



/*

generate tree:
for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

*/