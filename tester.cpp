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
	llong n = 10;

	cout<< n << " " << 1 <<endl;

	llong range = 2*n;

	vector<int> Xs(2*n); 
	for(int i=1;i<=2*n;i++) Xs[i-1] = i;
	random_shuffle(Xs.begin(), Xs.end());

	vector<int> Ys(2*n); 
	for(int i=1;i<=2*n;i++) Ys[i-1] = i;
	random_shuffle(Ys.begin(), Ys.end());

	int x = 0, y = 0;
	for(int i=0;i<n;i++){
		int x1 = Xs[x++];
		int x2 = Xs[x++];
		int y1 = Ys[y++];
		int y2 = Ys[y++];
		if(x1>x2) swap(x1,x2);
		if(y1>y2) swap(y1,y2);
		cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl; 
	}
	
}
