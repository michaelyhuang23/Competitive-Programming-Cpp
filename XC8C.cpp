#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<set>

#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct BIT{
	vector<int> bits; // index start from 1
	int n;
	BIT(int n_){
		n = n_+2;
		bits = vector<int>(n,0);
	}
	int lowbit(int n){ return n&(-n); }
	void update(int idx, int val){
		idx+=2; // for safety
		for(int i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	int get_sum(int idx){
		idx+=2; // for safety
		int sum = 0;
		for(int i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};

int n;

void solve(){
	cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	vector<int> sorted = arr;
	vector<int> pref(n,0);
	vector<int> pref2(n,0);
	BIT bit(n+5);
	for(int i=1;i<n;i++){
		pref[i] = pref[i-1];
		if(sorted[0] < sorted[i]) {
			pref[i]++;
			swap(sorted[0], sorted[i]);
		}
	}
	unordered_set<int> leftS;
	bit.update(sorted[0], 1);
	leftS.insert(sorted[0]);
	//deb(sorted)
	for(int i=1;i<n;i++){
		int total = bit.get_sum(n+3);
		int left = bit.get_sum(sorted[i]);
		int right = total - left;
		//deb(mt(i,sorted[i],right))
		pref2[i] = right+pref2[i-1];

		if(leftS.find(sorted[i]) == leftS.end())
			bit.update(sorted[i],1);
		leftS.insert(sorted[i]);
	}
	deb(pref)
	deb(pref2)
	for(int i=0;i<n-1;i++) cout<<pref[i]+pref2[i]<<" ";
	cout<<pref[n-1]+pref2[n-1]<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}
