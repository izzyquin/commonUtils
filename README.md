# commonUtils

# 📚 data-structures & pro-templates

A collection of **algorithms**, **data structure implementations**, and **professional LaTeX document templates**.  
This repository serves as a personal reference library, playground, and template hub for coursework, and technical writing.

## 📂 Repository Structure

### **data-structures/**
Implementations of classic algorithms and data structures in C++ and Python.

#### **dijkstra/**
- `Dijkstra.cpp`, `Dijkstra.h` — implementation of Dijkstra’s shortest path algorithm.

#### **graph/**
A full custom graph library including:
- Graph traversal: **BFS**, **DFS**
- Supporting components:
  - `Node.*`
  - `Queue.*`
  - `Stack.*`
  - `DataType.*`
- Tests: `testGraph.cpp`, `testGraph.sh`

#### **trie/**
- Trie data structure (`TrieNode.*`)
- Tests: `testTrieNode.cpp`, `testTrieNode.sh`

#### **lib/**
- Utility headers such as `assert_lib.h`

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

### Compile C++ examples
```bash
g++ -std=c++17 data-structures/graph/graph.cpp -o graph
./graph
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

