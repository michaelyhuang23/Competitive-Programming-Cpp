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
	int n = 50000;
	cout<<n<<endl;
	int range = 50000;
	
	for(int i=0;i<n;i++){
		int start = rand()%range+1;
		int end = rand()%range+1;
		if(end<start) {i--; continue;}
		int dur = rand()%(end-start+1)+1;
		cout<<start<<" "<<end<<" "<<dur<<endl;
	}
}
