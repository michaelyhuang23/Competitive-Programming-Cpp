#include<bits/stdc++.h>
 
using namespace std;
typedef long long llong;
 
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 100000000000000LL


void solve(){
    int n, m; cin >> n>>m;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];

    for(int i=0;i<m;i++){
        string type; cin >> type;
        if(type=="Xor"){
            int x; cin >> x;
            for(int i=0;i<n;i++) arr[i] ^= x;
        }else if(type=="And"){
            int x; cin >> x;
            for(int i=0;i<n;i++) arr[i] &= x;
        }else if(type=="Or"){
            int x; cin >> x;
            for(int i=0;i<n;i++) arr[i] = arr[i] | x;
        }else if(type=="Ask"){
            int l, r, k; cin >> l >> r >> k;
            l--; r--;
            vector<int> crr(arr.begin()+l, arr.begin()+r+1);
            sort(crr.begin(), crr.end());
            print(crr[k-1]);
        }
    }
}





int main(){
ios_base::sync_with_stdio(0);
cin.tie(0);
    solve();
}