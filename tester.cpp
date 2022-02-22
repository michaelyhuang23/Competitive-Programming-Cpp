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



int main(int argc, char** argv){
	srand(atoi(argv[1]));
	llong n = 100;
	llong k = 1000000;
	llong w = rand()%(k*n-k)+k;
	cout<<n<<" "<<k<<" "<<w<<endl;
	llong range = 1000000000;
	
	for(llong i=0;i<n;i++){
		llong val = rand()%range+1;
		cout<<val<<" ";
	}
	cout<<endl;
}
