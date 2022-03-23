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
	int n = 40, q = 2;
	cout<<n<<" "<<q<<endl;
	int w = 30;
	for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<" "<< random(1,w)<<endl;
	}

	for(int i=0;i<q;i++){
		cout<<random(1,n)<<" "<<random(1,w)<<endl;
	}
}



/*

generate tree:
for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

*/