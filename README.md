# 🏥 Hospital Ticket System

A C++ program that simulates a hospital service counter ticketing system using core Data Structures & Algorithms concepts.

---

## 📋 What It Does

This program takes patient tickets as input and processes them through 5 data structure stages:

1. **Sorts** tickets by priority using Insertion Sort
2. **Dispatches** them using Stack (emergencies) and Queue (normal/general)
3. **Assigns** tickets to counters using a Circular Linked List (round-robin)
4. **Stores & searches** ticket IDs using a Hash Table with Linear Probing
5. **Builds** a Binary Search Tree and prints Pre/In/Post order traversals

---

## 🗂️ Data Structures Used

| Part | Data Structure | Purpose |
|------|---------------|---------|
| A | Insertion Sort | Sort tickets by type → time → ID |
| B | Stack + Queue | Emergency (LIFO) vs normal (FIFO) dispatch |
| C | Circular Linked List | Round-robin counter assignment |
| D | Hash Table (Linear Probing) | Fast ticket lookup + tombstone deletion |
| E | Binary Search Tree | Ordered traversal of dispatched tickets |

---

## 🚀 How to Compile & Run

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

> **Ticket types:** `1` = Emergency, `2` = Normal, `3` = General

---

## 📤 Sample Output
