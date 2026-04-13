/*
 * Hospital Pharmacy & Lab – ECS 202
 * Flow:  Input → A(Sort) → B(Stack/Queue) → C(Circular List) → D(Hash) → E(BST)
 */

#include <iostream>
#include <string>
using namespace std;

const int MAXN  = 10;     
const int HT_SZ = 10;     
const int EMPTY = -1;     
const int TOMB  = -2;     

 1. TICKET  (plain data holder)
struct Ticket {
    int id, type, time, counter;
};

// ══════════════════════════════════════════════
 2. PART A  –  INSERTION SORT
// ══════════════════════════════════════════════


bool comes_before(const Ticket& a, const Ticket& b) {
    if (a.type != b.type)  return a.type < b.type;
    if (a.time != b.time)  return a.time < b.time;
    return a.id < b.id;
}

void insertion_sort(Ticket t[], int n) {
    for (int i = 1; i < n; i++) {
        Ticket key = t[i];
        int j = i - 1;
        
        while (j >= 0 && comes_before(key, t[j])) {
            t[j+1] = t[j];
            j--;
        }
        t[j+1] = key;
    }
}

void print_sorted(const Ticket t[], int n) {
    cout << "\nSORTED TICKETS :\n";
    for (int i = 0; i < n; i++)
        cout << t[i].id << " " << t[i].type << " "
             << t[i].time << " " << t[i].counter << "\n";
}

// ══════════════════════════════════════════════
 3. PART B  –  STACK  (array-based, LIFO)
// ══════════════════════════════════════════════
struct Stack {
    int data[MAXN];
    int top = -1;

    bool empty()       const { return top < 0; }
    void push(int x)         { data[++top] = x; }
    int  pop()               { return data[top--]; }
    int  peek()        const { return data[top]; }

    
    void print() const {
        if (empty()) { cout << "EMPTY"; return; }
        for (int i = top; i >= 0; i--) {
            if (i != top) cout << " ";
            cout << data[i];
        }
    }
};

// ══════════════════════════════════════════════
4. PART B  –  QUEUE  (circular array, FIFO)
// ══════════════════════════════════════════════
struct Queue {
    int data[MAXN];
    int head = 0, tail = 0, sz = 0;

    bool empty()       const { return sz == 0; }
    void enqueue(int x)      { data[tail] = x; tail = (tail+1)%MAXN; sz++; }
    int  dequeue()           { int x = data[head]; head = (head+1)%MAXN; sz--; return x; }

    // print front → rear
    void print() const {
        if (empty()) { cout << "EMPTY"; return; }
        for (int i = 0; i < sz; i++)
            cout << (i ? " " : "") << data[(head+i)%MAXN];
    }
};

// ══════════════════════════════════════════════
 5. PART B  –  DISPATCH  (stack first, then queue)
// ══════════════════════════════════════════════
int run_dispatch(const Ticket sorted[], int n,
                 int out[], int& out_cnt) {
    Stack S;
    Queue Q;

    for (int i = 0; i < n; i++) {
        if (sorted[i].type == 1) S.push(sorted[i].id);
        else                     Q.enqueue(sorted[i].id);
    }

    cout << "\nDISPATCH TRACE :\n";
    out_cnt = 0;

    while (!S.empty() || !Q.empty()) {
    
        int served = (!S.empty()) ? S.pop() : Q.dequeue();
        out[out_cnt++] = served;

        cout << "Serve : " << served
             << " | Stack : "; S.print();
        cout << " | Queue : "; Q.print();
        cout << "\n";
    }
    return out_cnt;
}

// ══════════════════════════════════════════════
 6. PART C  –  CIRCULAR LINKED LIST
// ══════════════════════════════════════════════
struct CNode {
    int  counter_no;
    int  ids[MAXN];       
    int  id_cnt = 0;
    CNode* next = nullptr;
};


CNode* build_circle(int k) {
    CNode* head = nullptr;
    CNode* tail = nullptr;
    for (int i = 1; i <= k; i++) {
        CNode* node = new CNode();
        node->counter_no = i;
        if (!head) head = tail = node;
        else       { tail->next = node; tail = node; }
    }
    tail->next = head;   // close the ring
    return head;
}


void assign_round_robin(CNode* head, const int ids[], int cnt) {
    CNode* cur = head;
    for (int i = 0; i < cnt; i++) {
        cur->ids[cur->id_cnt++] = ids[i];
        cur = cur->next;
    }
}

void print_counter_log(CNode* head, int k) {
    cout << "\nCIRCULAR COUNTER LOG :\n";
    CNode* ptr = head;
    for (int i = 0; i < k; i++) {
        cout << "Counter " << ptr->counter_no << ": ";
        if (ptr->id_cnt == 0) cout << "EMPTY";
        else
            for (int j = 0; j < ptr->id_cnt; j++)
                cout << (j ? " " : "") << ptr->ids[j];
        cout << "\n";
        ptr = ptr->next;
    }
}

// ══════════════════════════════════════════════
7. PART D  –  HASH TABLE  (linear probing + tombstone)

// ══════════════════════════════════════════════
int ht[HT_SZ];   

void ht_init()  { for (int i = 0; i < HT_SZ; i++) ht[i] = EMPTY; }

void ht_insert(int key) {
    int h = key % HT_SZ;
    for (int i = 0; i < HT_SZ; i++) {
        int idx = (h + i) % HT_SZ;
        
        if (ht[idx] == EMPTY || ht[idx] == TOMB) { ht[idx] = key; return; }
        if (ht[idx] == key) return;               
    }
}
pair<int,int> ht_search(int key) {
    int h = key % HT_SZ, probes = 0;
    for (int i = 0; i < HT_SZ; i++) {
        int idx = (h + i) % HT_SZ;
        probes++;
        if (ht[idx] == EMPTY) return {-1, probes};  
        if (ht[idx] == key)   return {idx, probes};  
        
    }
    return {-1, probes};  
}

void ht_delete(int key) {
    auto [idx, _] = ht_search(key);
    if (idx != -1) ht[idx] = TOMB;   
}

void ht_print() {
    cout << "\nFINAL HASH TABLE :\n";
    for (int i = 0; i < HT_SZ; i++) {
        cout << i << ": ";
        if      (ht[i] == EMPTY) cout << "EMPTY\n";
        else if (ht[i] == TOMB)  cout << "DELETED\n";
        else                      cout << ht[i] << "\n";
    }
}

// ══════════════════════════════════════════════
 8. PART E  –  BST  (Binary Search Tree)
// ══════════════════════════════════════════════
struct BNode {
    int   val;
    BNode *L = nullptr, *R = nullptr;
    BNode(int v) : val(v) {}
};

BNode* bst_insert(BNode* root, int v) {
    if (!root)        return new BNode(v);
    if (v < root->val) root->L = bst_insert(root->L, v);
    if (v > root->val) root->R = bst_insert(root->R, v);
    return root;
}

void preorder (BNode* n, int a[], int& c) {
    if (!n) return;
    a[c++] = n->val;
    preorder (n->L, a, c);
    preorder (n->R, a, c);
}
void inorder  (BNode* n, int a[], int& c) {
    if (!n) return;
    inorder  (n->L, a, c);
    a[c++] = n->val;
    inorder  (n->R, a, c);
}
void postorder(BNode* n, int a[], int& c) {
    if (!n) return;
    postorder(n->L, a, c);
    postorder(n->R, a, c);
    a[c++] = n->val;
}

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << a[i];
    cout << "\n";
}

void run_bst(const int dispatch[], int cnt) {
    BNode* root = nullptr;
    for (int i = 0; i < cnt; i++) root = bst_insert(root, dispatch[i]);

    int pre[MAXN], in[MAXN], post[MAXN];
    int c1=0, c2=0, c3=0;
    preorder (root, pre,  c1);
    inorder  (root, in,   c2);
    postorder(root, post, c3);

    cout << "\nBST TRAVERSALS :\n";
    cout << "Preorder : ";  print_arr(pre,  c1);
    cout << "Inorder : ";   print_arr(in,   c2);
    cout << "Postorder : "; print_arr(post, c3);
}

// ══════════════════════════════════════════════
 MAIN  –  read input, call each part in order
// ══════════════════════════════════════════════
int main() {
    
    int n;
    cout << "Enter n (number of tickets):\n";  cin >> n;

    Ticket tickets[MAXN];
    cout << "Enter " << n << " tickets (ticketID type time counterNo):\n";
    for (int i = 0; i < n; i++)
        cin >> tickets[i].id >> tickets[i].type
            >> tickets[i].time >> tickets[i].counter;

    int k;
    cout << "Enter k (number of counters):\n";  cin >> k;

    int q;
    cout << "Enter q (number of search queries):\n";  cin >> q;
    int queries[MAXN];
    cout << "Enter " << q << " query keys:\n";
    for (int i = 0; i < q; i++) cin >> queries[i];

    int kdel;
    cout << "Enter kdel (ticket to delete from hash):\n";  cin >> kdel;

    
    insertion_sort(tickets, n);
    print_sorted(tickets, n);

    
    int dispatch[MAXN], dcnt = 0;
    run_dispatch(tickets, n, dispatch, dcnt);

    
    CNode* circle = build_circle(k);
    assign_round_robin(circle, dispatch, dcnt);
    print_counter_log(circle, k);

    
    ht_init();
    for (int i = 0; i < dcnt; i++) ht_insert(dispatch[i]);

    cout << "\nHASH SEARCH RESULTS :\n";
    for (int i = 0; i < q; i++) {
        auto [idx, probes] = ht_search(queries[i]);
        if (idx != -1)
            cout << "Search " << queries[i] << ": Found at Index "
                 << idx << " , Probes : " << probes << "\n";
        else
            cout << "Search " << queries[i] << ": Not Found , Probes : "
                 << probes << "\n";
    }
    ht_delete(kdel);
    ht_print();

    
    run_bst(dispatch, dcnt);

    return 0;
}
