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
#define inf 1000000000



int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n = 100000, m = 100000;
	cout<<n<<endl;
	for(int i=0;i<n;i++){
		cout<<rand()%inf<<" ";
	}
	cout<<endl;
	cout<<m<<endl;
	for(int i=0;i<m;i++){
		int type = rand()%2;
		int l = rand()%n+1;
		int r = rand()%n+1;
		cout<<type<<" "<<l<<" "<<r<<endl;
	}
}
