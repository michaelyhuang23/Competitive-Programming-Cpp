#define MAXSIZE 1000
#define RANGE 1000

struct Node{

};

Node nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int counter = 0;
struct DynamicSegtree{
    DynamicSegtree(){}
    void pull_up(int idx){
        Node leftNode, rightNode;
        if(lefts[idx]!=-1) leftNode = nodes[lefts[idx]];
        if(rights[idx]!=-1) rightNode = nodes[rights[idx]];
        nodes[idx].pull_up(leftNode, rightNode);
    }
    void push_down(int idx){
        if(lefts[idx]==-1) lefts[idx] = ++counter;
        if(rights[idx]==-1) rights[idx] = ++counter;
        nodes[idx].push_down(nodes[lefts[idx]], nodes[rights[idx]]);
    }
    Node query(int idx, int ll, int rr, int ts=0, int te=RANGE){
        if(ll == ts && rr == te) return nodes[idx];
        int tm = (ts+te)/2;
        push_down(idx);
        Node leftNode, rightNode;
        if(lefts[idx]!=-1 && ll <= tm){
            leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
        }
        if(rights[idx]!=-1 && rr > tm){
            rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
        }
        return Node::merge(leftNode, rightNode);
    }
    void update(int idx, int ll, int rr, int val, int ts=0, int te=RANGE){
        if(idx==ts && idx==te){ nodes[idx].update(val); return; }
        int tm = (ts+te)/2;
        push_down(idx);
        if(ll <= tm){
            if(lefts[idx]==-1) lefts[idx] = ++counter; // instantiate
            update(lefts[idx], ll, min(rr,tm), val, ts, tm);
        }
        if(rr > tm){
            if(rights[idx]==-1) rights[idx] = ++counter; // instantiate
            update(rights[idx], max(ll,tm+1), rr, tm+1, te);
        }
        pull_up(idx);
    }
};
