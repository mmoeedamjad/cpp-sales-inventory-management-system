# C++ Sales & Computer Inventory Management System

![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

> **Commercial Point-of-Sale (POS) & Computer Inventory Solutions**  
> A collection of procedural C++ applications for managing computer store inventory, customer orders, custom hardware upgrades, ANSI terminal interfaces, and automated file persistence.

---

## 📋 Table of Contents

- [Repository Overview](#-repository-overview)
- [Project Modules](#-project-modules)
- [Folder Structure](#-folder-structure)
- [Quick Start & Build Guide](#-quick-start--build-guide)
- [License](#-license)

---

## 📌 Repository Overview

This repository contains two complete C++ management applications engineered for point-of-sale operations, inventory tracking, and sales analytics:

1. **Basic Sales & Inventory System**: A procedural in-memory POS system utilizing parallel arrays, input validation, and real-time stock deduction.
2. **Nexus Tech Computer Systems (PVT) Ltd.**: An enterprise laptop inventory and POS management system featuring detailed hardware specifications (Dedicated GPU, NVMe SSD, HDD), interactive upgrade options, automated text-file persistence (`store.txt` & `sales.txt`), and a 143-character pixel-perfect ANSI terminal layout.

---

## 🛠️ Project Modules

### 1. Basic Sales & Inventory System
- **Location**: [`Basic Sales & Inventory System/`](./Basic%20Sales%20&%20Inventory%20System/)
- **Core Technology**: Parallel arrays, linear search duplicate checking, stock validation.
- **Key Features**:
  - Unique product code registration with validation.
  - Interactive order entry with real-time stock balance deduction.
  - Tabular received orders log and invoice revenue summaries.

### 2. Nexus Tech Computer Systems (POS & File Persistence)
- **Location**: [`Computer Sale point/`](./Computer%20Sale%20point/)
- **Core Technology**: Struct data models, file I/O streams, automated persistence.
- **Key Features**:
  - Detailed laptop hardware attributes (`Company`, `Model`, `Processor`, `Dedicated GPU`, `RAM`, `NVMe/SSD`, `HDD`, `Price`, `Stock`).
  - Interactive RAM & NVMe SSD upgrade configuration modules.
  - Persistent text file databases (`store.txt` & `sales.txt`).
  - Single customer invoice receipt and store-wide revenue analytics.

---

## 📂 Folder Structure

```text
PF Project/
├── Basic Sales & Inventory System/        # Module 1: Basic In-Memory POS
│   ├── sales_management_project.cpp       # C++ source code file
│   ├── sales_management_project.exe       # Compiled Windows binary executable
│   └── README.md                          # Module documentation & CLI demo
├── Computer Sale point/                   # Module 2: Enterprise POS & File Store
│   ├── Computer_Sales.cpp                 # C++ source code file
│   ├── Computer_Sales.exe                 # Compiled Windows binary executable
│   ├── store.txt                          # Active inventory text database
│   ├── sales.txt                          # Order transactions text database
│   └── README.md                          # Module documentation & CLI demo
├── .gitignore                             # Git repository ignore rules
├── LICENSE                                # Official MIT License
└── README.md                              # Repository overview documentation
```

---

## 🚀 Quick Start & Build Guide

### Prerequisites

- **Operating System**: Windows 10/11
- **Compiler**: GCC / MinGW (`g++` v8.0+) or MSVC (`cl.exe`)

---

### Building Module 1: Basic Sales System

```powershell
# Navigate to Module 1
cd "Basic Sales & Inventory System"

# Compile with GCC / MinGW
g++ -std=c++17 -o sales_management_project.exe sales_management_project.cpp

# Run executable
.\sales_management_project.exe
```

---

### Building Module 2: Enterprise POS System

```powershell
# Navigate to Module 2
cd "Computer Sale point"

# Compile with GCC / MinGW
g++ -std=c++17 -o Computer_Sales.exe Computer_Sales.cpp

# Run executable
.\Computer_Sales.exe
```

---

## 📄 License

Distributed under the **MIT License**. See [`LICENSE`](./LICENSE) for full details.
