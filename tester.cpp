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
	int n = 5;
	int m = 10;
	cout<<n<<" "<<m<<endl;
	int range = 10;
	
	for(int i=0;i<n;i++){
		cout<<rand()%n+1<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<rand()%range+1<<" ";
	}
	cout<<endl;

	for(int i=0;i<n-1;i++){
		cout<<1<<" "<<i+2<<endl;
	}

	for(int i=0;i<m-n+1;i++){
		int a = rand()%n+1;
		int b = rand()%n+1;
		if(a==b) {i--; continue;}
		if(a>b) swap(a,b);
		cout<<a<<" "<<b<<endl;
	}
}
