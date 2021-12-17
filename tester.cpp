#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>
#include <stdlib.h>
//#include "debughelp.hpp"

using namespace std;

typedef long long llong;

#define MOD 1000000007LL
#define pb push_back
#define mp make_pair
#define mt make_tuple



int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n = 7, k = 5, q = 9;
	cout<<n<<" " <<k<<endl;
	for(int i=0;i<n;i++){
		if(i==n-1) cout<<rand()%k+1<<endl;
		else cout<<rand()%k+1<<" ";
	}
	cout<< q <<endl;
	for(int i=0;i<q;i++){
		int a = rand()%n+1, b = rand()%n+1;
		if(a>b) swap(a,b);
		cout<<a<<" "<<b<<endl;
	}
}