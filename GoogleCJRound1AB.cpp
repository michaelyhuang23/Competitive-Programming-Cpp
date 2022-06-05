#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

const int nbit = 29;

void solve(int tt){
	int n; cin >> n;
	// assert(n==100);

	llong sum = 0, sumA = 0, sumB = 0, suma = 0;
	vector<bool> used(500, 0);
	vector<int> A(n,0);
	for(int k=0;k<=nbit;k++){
		A[k] = 1<<k;
		if(A[k]<500) used[A[k]] = true;
		suma = suma + A[k];
	}
	for(int k=nbit+1;k<n;k++){
		for(int i=1;i<500;i++){
			if(!used[i]){
				used[i] = true;
				A[k] = i;
				break;
			}
		}
	}


	for(int i=0;i<n;i++) sumA = sumA + A[i];

	for(int k=0;k<n-1;k++)
		cout<<A[k]<<" ";
	cout<<A[n-1]<<endl;

	cout.flush();

	vector<int> B(n);
	for(int i=0;i<n;i++) cin >> B[i];
	for(int i=0;i<n;i++) sumB = sumB + B[i];

	sum = sumA + sumB;

	assert(sum % 2 == 0);

	llong sumH = sum / 2;
	
	llong psum = 0;
	int id = -1;
	for(int i=0;i<n;i++){
		psum += B[i];
		if(sumH - psum <= suma && sumH - psum >= 0){
			id = i;
			break;
		}
	}

	llong remn = sumH - psum;

	assert(id != -1);

	for(int i=0;i<id;i++){
		cout<<B[i]<<" ";
	}
	cout<<B[id];

	if(remn == 0){
		cout<<endl;
		cout.flush();
		return;
	}

	assert(remn <= suma);

	vector<int> ansK;
	for(int k=0;k<=nbit;k++){
		if(remn & (1<<k))
			ansK.pb(k);
	}
	cout<<" ";
	for(int i=0;i<ansK.size()-1;i++)
		cout<<(1<<ansK[i])<<" ";
	cout<<(1<<ansK.back())<<endl;
	cout.flush();
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t = 1; t <= tt; t++)
		solve(t);
}