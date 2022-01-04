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
	int n = 11, k = 36;
	cout<<1<<endl;
	int first = rand()%n+1;
	cout<<first<<" "<<first+rand()%k+1<<endl;
}
