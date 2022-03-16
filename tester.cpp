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
	int n = 100000;
	int m = 100000;

	cout<<n<<" "<<m+1<<endl;

	for(int i=2;i<=n;i++){
		int p = random(1, i-1);
		cout<<p << " "<<i<<endl;
	}

	vector<int> nodes(n);
	iota(nodes.begin(), nodes.end(), 1);
	random_shuffle(nodes.begin(), nodes.end());
	for(int i=0;i<m;i++){
		cout<<"1 "<<nodes[i]<<endl;
	}

	cout<<"2 "<<random(1,n)<<endl;
}


/*

generate tree:
for(int i=1;i<n;i++){
		int p = random(0, i-1);
		cout<<p << " "<<i<<endl;
	}

*/