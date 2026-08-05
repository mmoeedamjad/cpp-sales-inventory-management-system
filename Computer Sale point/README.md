# Nexus Tech Computer Systems (PVT) Ltd.

![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

> **Enterprise Computer Sales & Inventory System**  
> A high-performance, interactive C++ terminal application designed for commercial laptop store management, custom hardware upgrade configurations, automated file persistence, and itemized customer invoicing.

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Data Architecture & File Format](#-data-architecture--file-format)
- [Project Setup & Compilation](#-project-setup--compilation)
  - [Prerequisites](#prerequisites)
  - [Compilation Commands](#compilation-commands)
- [Interactive Usage Demo](#-interactive-usage-demo)
- [Directory Layout](#-directory-layout)

---

## 📌 Overview

**Nexus Tech Computer Systems** is an enterprise-grade commercial inventory control and point-of-sale management software. Built in C++, it manages rich laptop specifications including dedicated GPUs, dual storage options (NVMe SSD and HDD), processor designations, and customer transactions while maintaining automated persistent storage using plaintext files (`store.txt` and `sales.txt`).

---

## ✨ Key Features

- **Detailed Laptop Inventory Catalog**:
  - Track granular computer specifications:
    - **Brand**: HP, DELL, LENOVO, APPLE, etc.
    - **Model Designation**: Pavilion, ZBook, EliteBook, Latitude, ThinkPad, Legion, MacBook, Omen, etc.
    - **Processor**: `i7-8750H`, `i9-9880H`, `i7-10750H`, `i5-8350U`, `M1-8-Core`, etc.
    - **Dedicated GPU**: `4GB GTX 1050`, `6GB RTX 2060`, `6GB Quadro P3200`, `4GB Radeon Pro 5500M`, `Integrated Intel UHD`, etc.
    - **RAM Capacity**: `8 GB`, `16 GB`, `32 GB`.
    - **NVMe / SSD Storage**: `256 GB`, `512 GB` (Nullable / `None`).
    - **Hard Disk (HDD)**: `1 TB`, `2 TB` (Nullable / `None`).
    - **Pricing & Stock Balance**: Unit Price in RS. and real-time stock balance tracking.

- **Point of Sale (POS) Order Entry & Custom Upgrades**:
  - Captures full customer profile (Name, 13-digit formatted CNIC `35202-1489201-3`, `+92` Phone Number, Delivery Address).
  - Brand-filtered live inventory search.
  - **On-the-fly Hardware Expansion**: Interactively add RAM upgrades (Kingston/Corsair/Crucial) and NVMe SSD expansions (Samsung 970 EVO / WD Blue).
  - Calculates line-item totals and auto-deducts sold items from stock balances.

- **Sales Invoicing & Revenue Analytics**:
  - **Single Customer Invoice Receipt**: Itemized receipt showing customer details, serial breakdown, hardware specs, and grand total due.
  - **Store-Wide Sales Summary**: Complete historical sales ledger with cumulative store revenue calculation.

- **Automated Text File Persistence (`store.txt` & `sales.txt`)**:
  - Reads store catalog and sales transactions on application startup.
  - Automatically serializes all runtime inventory additions, field edits, stock deletions, and new sales back to text files upon system exit.

- **143-Character Pixel-Perfect Terminal Interface**:
  - Perfectly aligned box-bordered tables (`+-------+...`) using ANSI escape color formatting and native Windows Console VT mode processing (`ENABLE_VIRTUAL_TERMINAL_PROCESSING`).

---

## 🛠️ Data Architecture & File Format

### 1. `store.txt` Schema
Plaintext database storing active inventory catalog:
```text
Company   Model             Processor   GPU                   RAM   SSD   HDD   Price   Qty
HP        Pavilion-15       i7-8750H    4GB-GTX-1050          16    256   1024  135000  10
DELL      ZBook-15-G5       i7-9750H    6GB-Quadro-P3200      32    512   1024  195000  8
HP        EliteBook-840-G5  i5-8350U    Integrated-Intel-UHD  8     256   0     75000   12
DELL      Latitude-7490     i7-8650U    Integrated-Intel-UHD  16    512   0     85000   7
```

### 2. `sales.txt` Schema
Plaintext database storing customer order history:
```text
Customer       CNIC             Phone           Address             Company Model               Processor GPU                   RAM  SSD   HDD  Qty Price
MUHAMMAD-AHMAD 35202-1489201-3  +923004128956   Gulberg-III-Lahore  HP      EliteBook-840-G5    i5-8350U  Integrated-Intel-UHD  8GB  256GB 0GB  2   150000
```

---

## 🚀 Project Setup & Compilation

### Prerequisites

- **Operating System**: Windows 10/11
- **Compiler**: GCC / MinGW (`g++` v8.0+) or MSVC (`cl.exe`)

---

### Compilation Commands

#### Option 1: Standard MinGW GCC (`g++`)
```powershell
# Navigate to the project folder
cd "Computer Sale point"

# Compile source code with C++17
g++ -std=c++17 -o Computer_Sales.exe Computer_Sales.cpp

# Run executable
.\Computer_Sales.exe
```

#### Option 2: Portable Toolchain (`w64devkit`)
```powershell
$env:PATH = "d:\UCP semester 01 & 02\C++ codes (sem 02)\PF Project\tools\w64devkit\bin;" + $env:PATH
cd "d:\UCP semester 01 & 02\C++ codes (sem 02)\PF Project\Computer Sale point"
g++ -o Computer_Sales.exe Computer_Sales.cpp
.\Computer_Sales.exe
```

---

## 💻 Interactive Usage Demo

### 1. Corporate Main Menu
```text
===============================================================================================================================================
||                                               NEXUS TECH COMPUTER SYSTEMS (PVT) LTD.                                                      ||
||                                             Enterprise Inventory & Point of Sale System                                                   ||
===============================================================================================================================================
 [1] Add Inventory Stock     [2] Update Inventory      [3] Delete Stock Item
 [4] View Store Catalog     [5] Post Sales Order     [6] Sales Reports & Invoices
 [7] Exit System & Save Data
-----------------------------------------------------------------------------------------------------------------------------------------------
Enter your selection (1-7): 4
```

### 2. Inventory Stock Catalog Table
```text
[ INVENTORY STOCK CATALOG ]
-----------------------------------------------------------------------------------------------------------------------------------------------
+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+
| SR NO | BRAND      | MODEL                 | PROCESSOR       | DEDICATED GPU         | RAM     | SSD NVME| HDD     | PRICE (RS)    | QTY   |
+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+
| 1     | HP         | Pavilion-15           | i7 8750H        | 4GB GTX 1050          |    16 GB |   256 GB |     1 TB | RS.    135000 |    10 |
| 2     | DELL       | ZBook-15-G5           | i7 9750H        | 6GB Quadro P3200      |    32 GB |   512 GB |     1 TB | RS.    195000 |     8 |
| 3     | HP         | EliteBook-840-G5      | i5 8350U        | Integrated Intel UHD  |     8 GB |   256 GB |     None | RS.     75000 |    12 |
| 4     | DELL       | Latitude-7490         | i7 8650U        | Integrated Intel UHD  |    16 GB |   512 GB |     None | RS.     85000 |     7 |
| 5     | LENOVO     | ThinkPad-X1-Carbon    | i7 10510U       | Integrated Intel UHD  |    16 GB |   512 GB |     None | RS.    125000 |     5 |
| 6     | APPLE      | MacBook-Pro-16        | i9 9880H        | 4GB Radeon Pro 5500M  |    16 GB |   512 GB |     None | RS.    245000 |     6 |
| 7     | DELL       | Inspiron-7591         | i7 9750H        | 4GB GTX 1650          |    16 GB |   512 GB |     1 TB | RS.    155000 |     9 |
| 8     | LENOVO     | Legion-5-15           | i7 10750H       | 6GB RTX 2060          |    16 GB |   512 GB |     1 TB | RS.    175000 |    11 |
| 9     | APPLE      | MacBook-Air-M1        | M1 8 Core       | Integrated M1 7 Core  |     8 GB |   256 GB |     None | RS.    165000 |     5 |
| 10    | HP         | Omen-15               | i7 10750H       | 6GB RTX 2070          |    16 GB |   512 GB |     1 TB | RS.    210000 |     7 |
+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+
```

### 3. Store-Wide Sales Summary Report
```text
[ SALES INVOICES & REVENUE REPORTS ]
-----------------------------------------------------------------------------------------------------------------------------------------------
1. Single Customer Invoice Receipt
2. Complete Store Sales Report
-> Option (1-2): 2

===============================================================================================================================================
||                                               STORE-WIDE SALES SUMMARY REPORT                                                             ||
===============================================================================================================================================

+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+
| CUSTOMER         | CNIC            | PHONE         | BRAND      | MODEL                  | RAM     | SSD NVME| HDD     | QTY   | TOTAL PRICE (RS) |
+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+
| MUHAMMAD AHMAD   | 35202-1489201-3 | +923004128956 | HP         | EliteBook-840-G5       |     8 GB |   256 GB |     None |     2 | RS.       150000 |
| TARIQ MAHMOOD    | 38403-9182341-7 | +923218974512 | DELL       | Latitude-7490          |    16 GB |   512 GB |     None |     1 | RS.        85000 |
| USMAN RANA       | 34101-4561238-5 | +923335678912 | LENOVO     | ThinkPad-X1-Carbon     |    16 GB |   512 GB |     None |     1 | RS.       125000 |
| ZAINAB BIBI      | 33100-7812349-2 | +923456789012 | APPLE      | MacBook-Air-M1         |     8 GB |   256 GB |     None |     1 | RS.       165000 |
+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+
CUMULATIVE STORE SALES REVENUE: RS. 525000
```

---

## 📂 Directory Layout

```text
Computer Sale point/
├── Computer_Sales.cpp    # Primary C++ source code file
├── Computer_Sales.exe    # Compiled binary executable
├── store.txt             # Active inventory text database
├── sales.txt             # Sales order transactions text database
└── README.md             # Project documentation
```
