#include<iostream>
#include<vector>

using namespace std;
#define pb push_back
#define print(x) cout<<x

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	vector<int> R(n);
	vector<int> C(n);
	for(int i=0;i<n;i++) cin >> R[i];
	for(int i=0;i<n;i++) cin >> C[i];

	int q; cin >> q;
	for(int i=0;i<q;i++){
		int r, c; cin >> r >> c; r--; c--;
		int cv = C[c];
		int rv = R[r];
		if(n+1-cv<=rv) print("#");
		else print(".");
	}
	cout<<endl;
}



/*

when n = 5
Consider painting the columns with 5, 4, 3, 2, 1 colors in sequence
the 1 4 leaves
the 2 3 leaves

or consider in reverse, 1,2,3,4,5
1 must be on the row of 5
2 must be on the row of 5 and 4
3 must be on the row of 5, 4, 3
...

so if we know column is c,
we know the column must be colored in on the row of
[n+1-c,n]

*/

