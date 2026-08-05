# Basic Sales & Inventory System

![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

> A procedural C++ point-of-sale (POS) and inventory control system featuring input validation, real-time stock deduction, parallel array storage, and ANSI color box-bordered terminal tables.

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Data Architecture](#-data-architecture)
- [Project Setup & Compilation](#-project-setup--compilation)
  - [Prerequisites](#prerequisites)
  - [Compilation Commands](#compilation-commands)
- [Interactive Usage Demo](#-interactive-usage-demo)
- [Directory Layout](#-directory-layout)

---

## 📌 Overview

The **Basic Sales & Inventory System** provides core commercial management operations without relying on OOP classes, dynamic memory pointers, or external database engines. It is constructed using standard C++ procedural constructs (`parallel arrays`, `while`, `do-while`, `for`, `if-else`) and Windows Console Virtual Terminal Processing for ANSI color rendering.

---

## ✨ Key Features

1. **Product Inventory Registration (`Option 1`)**:
   - Register new catalog items with unique Product Code, Name, Price ($), and Stock Quantity.
   - **Linear Search Duplicate Validation**: Prevents duplicate product codes.
   - **Input Validation**: Enforces product price > $0 via `do-while` validation loops.

2. **Inventory Stock Catalog (`Option 2`)**:
   - Tabulates active products in aligned box tables (`+------+...`).

3. **Point of Sale Order Entry (`Option 3`)**:
   - Interactive item selection by product code.
   - **Real-Time Stock Deduction**: Validates requested quantity against available stock and decrements inventory immediately upon order confirmation.

4. **Received Orders Log (`Option 4`)**:
   - Displays all historical customer line-item transactions.

5. **Sales Invoice & Store Revenue Summary (`Option 5`)**:
   - Groups order line-items by Order ID and Customer Name.
   - Calculates itemized subtotals (`Quantity × Unit Price`) and cumulative store revenue.

---

## 🛠️ Data Architecture

The application utilizes **parallel arrays** in memory to manage inventory and sales data:

### 1. Inventory Database Arrays
| Variable Name | Data Type | Description |
| :--- | :--- | :--- |
| `product_code[100]` | `std::string` | Unique product code (e.g. `P001`) |
| `product_name[100]` | `std::string` | Product title/name (e.g. `Keyboard`) |
| `product_price[100]` | `int` | Unit price in USD ($) |
| `product_quantity[100]` | `int` | Current stock balance |

### 2. Customer Sales Order Arrays
| Variable Name | Data Type | Description |
| :--- | :--- | :--- |
| `order[100]` | `std::string` | Order transaction ID (e.g. `ORD-101`) |
| `customer[100]` | `std::string` | Customer full name |
| `pro_code[100]` | `std::string` | Purchased product code |
| `odr_pro_name[100]` | `std::string` | Resolved product title |
| `qty[100]` | `int` | Purchased unit quantity |

---

## 🚀 Project Setup & Compilation

### Prerequisites

- **Operating System**: Windows 10/11
- **Compiler**: GCC / MinGW (`g++` v8.0+) or MSVC (`cl.exe`)

---

### Compilation Commands

#### 1. Using GCC / MinGW (`g++`)
```powershell
# Open terminal in this folder
cd "Basic Sales & Inventory System"

# Compile source code with C++17 standard
g++ -std=c++17 -o sales_management_project.exe sales_management_project.cpp

# Execute application
.\sales_management_project.exe
```

#### 2. Using Standalone GCC Toolchain (`w64devkit`)
```powershell
$env:PATH = "d:\UCP semester 01 & 02\C++ codes (sem 02)\PF Project\tools\w64devkit\bin;" + $env:PATH
cd "d:\UCP semester 01 & 02\C++ codes (sem 02)\PF Project\Basic Sales & Inventory System"
g++ -o sales_management_project.exe sales_management_project.cpp
.\sales_management_project.exe
```

---

## 💻 Interactive Usage Demo

### Step 1: Main Menu Options
```text
===================================================================================================
||                             BASIC SALES & INVENTORY SYSTEM                                    ||
===================================================================================================
 [1] Product Entry       [2] Product Display     [3] Order Entry
 [4] Received Orders     [5] Sales Summary       [6] Exit System
---------------------------------------------------------------------------------------------------
Enter your choice (1-6): 1
```

### Step 2: Add Inventory Product
```text
[ PRODUCT INVENTORY REGISTRATION ]
---------------------------------------------------------------------------------------------------
Enter Product Code: P001
Enter Product Name: Dell-Inspiron-Laptop
Enter Product Price ($): 750
Enter Stock Quantity: 15

>> Product registered successfully!
Add another product? (y/n): n
```

### Step 3: View Inventory Catalog
```text
[ PRODUCT INVENTORY CATALOG ]
---------------------------------------------------------------------------------------------------
+--------+-------------------------+------------+------------+
| CODE   | PRODUCT NAME            | PRICE ($)  | STOCK QTY  |
+--------+-------------------------+------------+------------+
| P001   | Dell-Inspiron-Laptop    | $      750 |         15 |
+--------+-------------------------+------------+------------+
```

### Step 4: Process Customer Order
```text
[ CUSTOMER SALES ORDER ENTRY ]
---------------------------------------------------------------------------------------------------
Enter Order ID: ORD-101
Enter Customer Name: John-Doe
Enter Product Code to Purchase: P001
Enter Quantity to Purchase: 3

>> Order posted successfully! Stock updated.
```

---

## 📂 Directory Layout

```text
Basic Sales & Inventory System/
├── sales_management_project.cpp    # Primary source code
├── sales_management_project.exe    # Compiled binary executable
└── README.md                       # Documentation
```
