#include<iostream>
#include<vector>

using namespace std;
#define pb push_back
#define print(x) cout<<x

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	int ans = 1000000007;
	vector<int> arr2(n);
	for(int i=0;i<n;i++) arr2[i] = arr[n-1-i];

	int st = 0;
	for(int i=0;i<n;i++) if(arr[i]==1) st=i;

	bool sU = 1;
	for(int i=0;i<n;i++){
		int pi = (st+i)%n;
		if(arr[pi] != i+1) sU = 0;
	}
	if(sU){
		ans = min(ans, st);
	}

	int et = 0;
	for(int i=0;i<n;i++) if(arr[i]==n) et=i;

	bool eU = 1;
	for(int i=0;i<n;i++){
		int pi = (et+i)%n;
		if(arr[pi] != n-i) eU = 0;
	}
	if(eU){
		ans = min(ans, et+1);
	}



	st = 0;
	for(int i=0;i<n;i++) if(arr2[i]==1) st=i;

	sU = 1;
	for(int i=0;i<n;i++){
		int pi = (st+i)%n;
		if(arr2[pi] != i+1) sU = 0;
	}
	if(sU){
		ans = min(ans, st+1);
	}

	et = 0;
	for(int i=0;i<n;i++) if(arr2[i]==n) et=i;

	eU = 1;
	for(int i=0;i<n;i++){
		int pi = (et+i)%n;
		if(arr2[pi] != n-i) eU = 0;
	}
	if(eU){
		ans = min(ans, et+2);
	}


	cout<<ans<<endl;
}






/*

operation is very limited, instead of flipping, we can just say we 
can move the tail to the head and the head to the tail (rotate left or right)

2 3 4 5 6 7 8 9 10 1
3 4 5 6 7 8 9 10 1 2
2 1 10 9 8 7 6 5 4 3 
1 10 9 8 7 6 5 4 3 2

that means the subsequence must already be sorted either in ascending order
 or descending order with some start point we don't know yet

 7 8 9 1 2 3 4 5 6 

Just look for the location of 1! to find the start of ascending order

3 2 1 9 8 7 6 5 4 
look for 9 if descending order


could be both
*/