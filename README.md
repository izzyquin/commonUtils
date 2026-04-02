# commonUtils

# 📚 data-structures & pro-templates

A collection of **algorithms**, **data structure implementations**, and **professional LaTeX document templates**.  
This repository serves as a personal reference library, playground, and template hub for coursework, and technical writing.

## 📂 Repository Structure

### **data-structures/**
Implementations of classic algorithms and data structures in C++ and Python.

#### **dijkstra/**
- `dijkstra.cpp`, `dijkstra.h` — implementation of Dijkstra’s shortest path algorithm.

#### **graph/**
A full custom graph library including:
- Graph traversal: **BFS**, **DFS**
- Tests: `test_graph.cpp`, `run_gtest.sh`

#### **trie/**
- Trie data structure (`TrieNode.*`)
- Tests: `test_trie_tode.cpp`, `run_gtest.sh`

#### **lib/**
- Utility headers such as `assert_lib.h`
- Basic components:
  - `Node.h`
  - `Queue.h`
  - `Stack.h`

#### **py/**
- Python utilities (e.g., `testHashMap.py`)

---

### **pro-templates/**
A collection of professional document templates, mainly LaTeX-based.

#### **assignment_tex/**
A full assignment/report template with:
- Source `.tex` files
- Example figures and plots
- PGF/TikZ support
- Scripts folder

Use for academic assignments and reports.

---

## 🧰 Features

- Clean implementations of fundamental algorithms  
- Ready-to-use LaTeX templates for professional documents   
- Contains C, C++, Python code  

---

## 🛠 How to Use

### Clone the repo
```bash
git clone git@github.com:izzyquin/commonUtils.git
cd commonUtils
```

### Run C++ test scripts
```bash
./data-structures/cpp/run_gtest.sh
```

### Run Python scripts
```bash
python3 data-structures/py/testHashMap.py
```

### Use LaTeX templates
```bash
cd pro-templates/assignment_tex
pdflatex assignment_1.tex
```

---

## 📌 Notes

- Subrepos inside `gitTest/` are intentionally ignored using `.gitignore`.
- Large PGF/TikZ libraries included to ensure templates work offline.
- This repository is under continuous cleanup and improvement.

---

## 🧑‍💻 Author

**Izzy Pasandi**  
Software Engineer • Systems • Algorithms • LaTeXlover

