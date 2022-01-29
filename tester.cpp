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
	int n = 5, m = 2;
	int range = 10;
	cout<<n<<" "<<m<<endl;
	for(int i=0;i<n;i++){
		cout<<rand()%range<<" ";
	}
	cout<<endl;
	for(int i=0;i<m;i++){
		int type = (rand()%2)+1;
		int l = rand()%n+1;
		int r = rand()%n+1;
		if(type == 2)
			cout<<type<<" "<<l<<" "<<r<<endl;
		else 
			cout<<type<<" "<<l<<" "<<r<<" "<<rand()%range<<endl;
	}
}
