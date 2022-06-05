#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair

void solve(int tt){
	int n; cin >> n;
	deque<int> arr;
	for(int i=0;i<n;i++) {
		int a; cin >> a;
		arr.pb(a);
	}

	int cmax = 0;
	int cc = 0;
	for(int i=0;i<n;i++){
		if(arr.back() <= arr.front()){
			int val = arr.back(); arr.pop_back();
			if(val >= cmax){
				cmax = val;
				cc++;
			}
		}else{
			int val = arr.front(); arr.pop_front();
			if(val >= cmax){
				cmax = val;
				cc++;
			}
		}
	}

	cout<<"Case #"<<tt<<": "<<cc<<endl;
}







int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int i=1;i<=tt;i++)
		solve(i);
}