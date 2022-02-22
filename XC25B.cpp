#include<bits/stdc++.h>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define MOD 1000000009
#define print(x) cout<<x<<endl


struct matrix{ 
	vector<vector<int>> mat;
	int s;
	matrix(int s_, int v_){
		s = s_;
		mat = vector<vector<int>>(s, vector<int>(s,v_));
	}

	matrix operator*(const matrix& other){
		matrix ret(s, 0);
		for(int r=0;r<s;r++){
			for(int c=0;c<s;c++){
				for(int i=0;i<s;i++){
					ret.mat[r][c] += mat[r][i] * other.mat[i][c];
				}
			}
		}
		return ret;
	}

	vector<int> mul(const vector<int>& x){
		vector<int> ret(s,0);
		for(int r=0;r<s;r++){
			for(int i=0;i<s;i++){
				ret[r] += mat[r][i]*x[i];
			}
		}
		return ret;
	}

	matrix identity(){
		matrix ret(s,0);
		for(int i=0;i<s;i++) ret.mat[i][i]=1;
		return ret;
	}

};

int n, m; 
vector<vector<int>> preprocess(vector<int>& C){
	vector<vector<int>> H(m+1, vector<int>(m+1, 0)); // H for cross boundary
	vector<vector<int>> G(2*m+1, vector<int>(2*m+1, 0)); // G for not cross boundary
	// first start, second target

	vector<vector<vector<int>>> Gp(2*m+1, vector<vector<int>>(2*m+1, vector<int>(2*m+1,0)));

	for(int d=0;d<=2*m;d++){
		for(int k=0;k<d;k++){
			if(d-k<=m)
				G[d][k] = C[d-k];
		}
	}

	for(int d=0;d<=2*m;d++){
		for(int k=0;k<d;k++){
			for(int k2=k+1;k2<d;k2++){
				G[d][k] += G[d][k2]*G[k2][k];
			}
		}			
	}


	for(int d=0;d<=m;d++){
		for(int k=0;k<=m;k++){
			int nd = d+m;
			int nk = m-k;
			H[d][k] = G[nd][nk];
		}
	}

	// vector<vector<vector<int>>> Hp(2*m+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));
	// for(int r=1;r<=m;r++){
	// 	for(int d=0;d<=m;d++){
	// 		int k = d - r;
	// 		if(k<0){
	// 			Hp[1][d][-k] += C[r];				
	// 		}
	// 	}
	// }

	// for(int t=2;t<=2*m;t++){
	// 	for(int d=0;d<=m;d++){
	// 		for(int k=0;k<=m;k++){
	// 			for(int k2=k-1;k2>=0;k2--){
	// 				Hp[t][d][k] += Hp[t-1][d][k2] * G[k][k2]; // swap for G because of negation
	// 			}
	// 			for(int k2=0;k2<d;k2++){
	// 				Hp[t][d][k] += G[d][k2] * Hp[t-1][k2][k];
	// 			}
	// 		}
	// 	}
	// }

	// for(int t=0;t<2*m+1;t++) deb(Hp[t][3][3])

	// for(int d=0;d<=m;d++)
	// 	for(int k=0;k<=m;k++)
	// 		for(int t=1;t<=2*m;t++)
	// 			H[d][k] += Hp[t][d][k];

	return H;
}

matrix expower(matrix& base, int pow){
	if(pow == 0){
		return base.identity();
	}
	if(pow % 2 == 0){
		matrix inter = expower(base, pow/2);
		return inter * inter;
	}else{
		return base * expower(base, pow-1);
	}
}

void solve(){
	cin >> n >> m;
	vector<int> C(m+1);
	for(int i=1;i<=m;i++) cin >> C[i];

	vector<vector<int>> H = preprocess(C);

	// now we build the matrix
	int length = (m+1)*(m+1);
	matrix M(length, 0);

	for(int r=0;r<length;r++){
		int col = r/(m+1);
		// 0 <= col <= m
		int d = r%(m+1);

		for(int c=0;c<length;c++){
			int col2 = c/(m+1);
			int d2 = c%(m+1);

			if(col>0 && col == col2+1 && d==d2){
				M.mat[r][c]=1;
			}
		}
	} // simple part


	M.mat[0][0] = C[2];
	for(int r=0;r<m+1;r++){
		int col = 0;
		int d = r;
		for(int c=0;c<length;c++){
			int col2 = c/(m+1);
			int d2 = c%(m+1);
			int col2m = col2+1;

			if(col2m != d2) continue; // what the fuck?
			M.mat[r][c] += H[d][d2];
		}
	}

	deb(M.mat)

	// should be done here
	vector<int> dp0(length, 0);
	dp0[0] = 1;
	for(int d=1;d<=m;d++){
		dp0[d] = 2*C[d]; // orientation here
	}

	// now the exponentiation part.

	matrix MT = expower(M, 3);

	vector<int> dpn = MT.mul(dp0);

	print(dpn[0]);
}













int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

}















