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

llong random(llong st, llong ed){
	if(st==ed) return st;
	return rand()%(ed-st+1)+st;
}

int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n = 3, m = 1;
	cout << n<<" "<<m+1 << endl;

	for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

	for(int i=0;i<m;i++){
		cout<<"1 ";
		int a = random(1,n);
		int x = random(1,2);
		cout<<a<<" "<<x<<endl;
	}

	cout<<"2 "<<random(1,n)<<endl;
}



/*

generate tree:
for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

*/