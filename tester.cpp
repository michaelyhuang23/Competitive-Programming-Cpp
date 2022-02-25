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
	llong n = 500;
	print(n);

	llong range = 500;
	llong vrange = 1000000;

	for(int i=0;i<n;i++){
		llong k = rand()%range + 1;
		print(k);
		for(int j=0;j<k;j++){
			llong x = rand()%vrange - vrange/2;
			llong y = rand()%vrange - vrange/2;
			cout<<x<<" "<<y<<endl;
		}
	}
	
}
