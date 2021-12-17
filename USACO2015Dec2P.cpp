#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct SegTree {
    static iint pow_up(iint num) {
        For(i, 65) if (1 << i >= num) return 1 << i;
        return -1;
    }

    vector<iint> state;
    vector<iint> score;
    vector<iint> openA;
    vector<iint> openB;
    iint n;

    SegTree(iint *states, iint size) {
        n = pow_up(size);
        state = vector<iint>(n, 0);
        openA = vector<iint>(n * 2, 0);
        openB = vector<iint>(n * 2, 0);
        score = vector<iint>(n * 2, 0);
        copy(states, states + size, state.begin());
        build();
    }

    inline void pull_up(iint idx) {
        iint inter = min(openB[idx << 1 | 1], openA[idx << 1]);
        score[idx] = score[idx << 1] + score[idx << 1 | 1] + inter;
        openB[idx] = openB[idx << 1 | 1] - inter + openB[idx << 1];
        openA[idx] = openA[idx << 1] - inter + openA[idx << 1 | 1];
    }

    inline void build() {
        for (iint i = n; i < 2 * n; i++) {
            if (state[i-n] == 2) openB[i] = 1;
            else if (state[i-n] == 1) openA[i] = 1;
        }
        for (iint i = n - 1; i >= 1; i--) pull_up(i);
    }

    inline void update(iint pos, iint val) {
        state[pos] = val;
        if (val == 2) openB[pos + n] = 1;
        else if (val == 1) openA[pos + n] = 1;
        for (iint i = (pos + n) >> 1; i >= 1; i >>= 1) pull_up(i);
    }

    inline tuple<iint, iint, iint> query(iint idx, iint ts, iint te, iint left, iint right) {
        // both inclusive; ts, te indicate the coverage of this index
        if (left > right) return make_tuple(0, 0, 0);
        if (ts == left && te == right) return make_tuple(score[idx], openA[idx], openB[idx]);
        iint tm = (ts + te) >> 1;
        if (left <= tm && right > tm) {
            tuple<iint,iint,iint> leftr = query(idx << 1, ts, tm, left, min(right, tm));
            tuple<iint,iint,iint> rightr = query(idx << 1 | 1, tm + 1, te, max(tm + 1, left), right);
            iint inter = min(get<2>(rightr), get<1>(leftr));
            iint scorei = get<0>(leftr) + get<0>(rightr) + inter;
            iint openAi = get<1>(leftr) - inter + get<1>(rightr);
            iint openBi = get<2>(rightr) - inter + get<2>(leftr);
            return make_tuple(scorei, openAi, openBi);
        }
        if (left <= tm)
            return query(idx << 1, ts, tm, left, min(right, tm));
        if (right > tm)
            return query(idx << 1 | 1, tm + 1, te, max(tm + 1, left), right);
        assert(false);
        return make_tuple(0, 0, 0); // should never run this
    }

    inline llong query(iint left, iint right) { return get<0>(query(1, 0, n - 1, left, right)); }
};

int main() {
    ifstream fin("cardgame.in");
    ofstream fout("cardgame.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n; cin >> n;
    vector<iint> arrA(n);
    vector<iint> arrB;
    arrB.reserve(n);
    For(i, n) cin >> arrA[i];
    unordered_set<iint> As(arrA.begin(), arrA.end());
    for (iint i = 1; i <= 2 * n; i++) if (As.find(i) == As.end()) arrB.pb(i);
    assert(arrB.size() == n);
    assert(arrA.size() == n);
    sort(arrB.begin(), arrB.end(), greater<iint>());
    // sort in descending order
    iint *baseArr = new iint[2 * n];
    fill(baseArr, baseArr + 2 * n, 0);
    SegTree segtree(baseArr, 2 * n);
    vector<iint> maxFScores(n + 5);
    vector<iint> maxBScores(n + 5);
    maxFScores[0] = 0;
    for (iint i = 0; i < arrA.size(); i++) {
        segtree.update(arrA[i] - 1, 1);
        // arr in segtree is useless
        segtree.update(arrB[i] - 1, 2);
        // add in the new key first (mind first case)
        iint maxScore = segtree.query(0, 2 * n - 1);
        maxFScores[i + 1] = maxScore;
    }
    baseArr = new iint[2*n];
    fill(baseArr, baseArr + 2 * n, 0);
    SegTree segtree2(baseArr, 2 * n);
    maxBScores[arrA.size()] = 0;
    for (iint i = arrA.size() - 1; i >= 0; i--) {
        segtree2.update(arrB[i] - 1, 1); //swap here because it's lower wins
        // arr in segtree is useless
        segtree2.update(arrA[i] - 1, 2);
        // add in the new key first (mind first case)
        iint maxScore = segtree2.query(0, 2 * n - 1);
        maxBScores[i] = maxScore;
    }
    iint maxScore2 = 0;
    for (iint i = 0; i <= arrA.size(); i++) {
        maxScore2 = max(maxFScores[i] + maxBScores[i], maxScore2);
    }
    cout << maxScore2 << endl;
}