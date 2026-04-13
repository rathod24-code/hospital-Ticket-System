# 🏥 Hospital Ticket System

A C++ program that simulates a hospital service counter ticketing system using core Data Structures concepts.

---

## 📋 Features

- **Insertion Sort** — Sorts tickets by type → arrival time → ticket ID
- **Stack & Queue Dispatch** — Emergency tickets (type 1) use a Stack (LIFO); others use a Queue (FIFO)
- **Circular Linked List** — Assigns tickets to service counters in round-robin order
- **Hash Table (Linear Probing)** — Stores and searches ticket IDs with tombstone deletion
- **Binary Search Tree (BST)** — Inserts dispatched tickets and prints Pre/In/Post order traversals

---

## 🗂️ Data Structure Used

| Part | Data Structure | Purpose |
|------|---------------|---------|
| A | Insertion Sort | Sort tickets by priority |
| B | Stack + Queue | Dispatch emergency vs normal tickets |
| C | Circular Linked List | Round-robin counter assignment |
| D | Hash Table | Fast ticket lookup |
| E | Binary Search Tree | Ordered traversal of tickets |

---

## 🚀 How to Run

### Compile
```bash
g++ hospital_optimized.cpp -o hospital
```

### Run
```bash
./hospital
```

---

## 📥 Input Format

```
Enter n (number of tickets):
5
Enter 5 tickets (ticketID type time counterNo):
101 1 10 1
102 2 5 2
103 1 8 1
104 3 12 3
105 2 6 2
Enter k (number of counters):
3
Enter q (number of search queries):
2
Enter 2 query keys:
101 104
Enter kdel (ticket to delete from hash):
102
```

---

## 📤 Output Example

```
SORTED TICKETS:
103 1 8 1
101 1 10 1
102 2 5 2
105 2 6 2
104 3 12 3

DISPATCH TRACE:
Serve : 101 | Stack : 103 | Queue : 102 105 104
...

CIRCULAR COUNTER LOG:
Counter 1: 101 104
Counter 2: 103 105
Counter 3: 102

HASH SEARCH RESULTS:
Search 101: Found at Index 1, Probes: 1
Search 104: Found at Index 4, Probes: 1

FINAL HASH TABLE:
0: EMPTY
1: 101
2: DELETED
...

BST TRAVERSALS:
Preorder: 101 103 102 104 105
Inorder: 101 102 103 104 105
Postorder: 102 101 105 104 103
```

---

## 🛠️ Tech Stack

- Language: **C++**
- Concepts: **DSA (Data Structures & Algorithms)**
- IDE: Any C++ compiler (g++, Code::Blocks, VS Code)

---

## 👤 Author

**Rahul Rathod**  
GitHub: [@rathod24-code](https://github.com/rathod24-code)
