#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000008

#define print(x) cout<<x<<endl


int n, d;

int rehabilitate(vector<int>& arr, int omit){
	int minD = inf, maxD = 0;
	for(int i=0;i<n;i++){
		if(i == omit) continue;
		int start = 1;
		if(i>0) {
			if(i-1 == omit){
				if(i-2>=0) start=arr[i-2]+1;
				else start = 1;
			}else
				start = arr[i-1]+1;
		}
		int d = arr[i] - start;
		minD = min(minD, d);
		maxD = max(maxD, d);
	}

	// print(minD);
	// print(maxD);

	int back = arr.back();
	if(omit == arr.size() - 1) back = arr[arr.size()-2];
	maxD = max(maxD, (d-back-1)*2+1);

	int newm = (maxD-1) / 2;

	return min(minD, newm);

}

void solve(){
	cin >> n >> d;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	sort(arr.begin(), arr.end());
	
	// if there's a 3 way equal, cannot change

	// if there's a 2 way equal, move the middle of the 2 if they are contagious

	// if there's a 1 way equal, try moving either end point

	int minD = inf, minC = 0;
	set<int> endptrs;
	for(int i=0;i<n;i++){
		int start = 1;
		if(i > 0) start = arr[i-1]+1;
		int d = arr[i] - start;
		if(d < minD){
			minD = d;
			minC = 1;
			endptrs = set<int>();
			endptrs.insert(i);
		}else if(d == minD){
			minC++;
			endptrs.insert(i);
		}
	}


	if(minC >= 3){ print(minD); return; }

	if(minC == 2){
		assert(endptrs.size() == 2);
		int first = *endptrs.begin();
		int second = *(next(endptrs.begin()));

		if(first+1 != second){
			print(minD); return;
		}

		minD = max(minD, rehabilitate(arr, first));
		print(minD);
		return;
	}

	assert(endptrs.size() == 1);


	int first = *endptrs.begin();

	//print(first);
	minD = max(minD, rehabilitate(arr, first));
	if(first > 0)
		minD = max(minD, rehabilitate(arr, first-1));

	print(minD);
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tt; cin >> tt;
	while(tt--) solve();
}