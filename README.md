# OOP-V3 - Forked from OOP-V2 by jullion14
```
delete FreightStorage and CargoStorage .h and .cpp files, replace lines
#include "FreightStorage.h"
#include "CargoStorage.h"
To:
```
#include "Freight.h"
#include "Cargo.h"
#include "Storage.h"

// Create type aliases
using FreightStorage = Storage<Freight>;
using CargoStorage = Storage<Cargo>;
```
/OOP-V3 Directory
├── Transport.h/.cpp
├── Freight.h/.cpp
├── Cargo.h/.cpp
├── Storage.h         <-- generic template header
├── Storage.tpp       <-- template implementation
├── main.cpp          <-- includes Storage.h and type aliases

```
# OOP-V2 – Cargo & Freight Matching Simulator

> A small C++ console application that demonstrates clean object-oriented design while tackling a realistic logistics problem: **matching pieces of cargo with available freight capacity and producing a shipping schedule**.

## ✨  Key ideas

* Encapsulated domain classes (`Cargo`, `Freight`, `Transport`) and **storage singletons** that own their respective collections.  
* A two-phase **matching engine** (`Matcher` / `MatchedStorage`) that pairs compatible cargo and freight records, then persists the result.  
* Simple flat-file persistence (`*.txt`) so you can examine or edit sample data without a DB.  
* Clean separation of *model* ↔ *service* ↔ *presentation* layers to make unit testing and future GUI/API work easy.

_File map preview_ :contentReference[oaicite:0]{index=0}

.
├─ Cargo.h / .cpp // cargo item definition + helpers
├─ Freight.h / .cpp // freight offer definition + helpers
├─ Transport.h / .cpp // wraps route / vehicle data
├─ CargoStorage.* // singleton container for cargo items
├─ FreightStorage.* // singleton container for freight offers
├─ MatchedStorage.* // holds output of Matcher
├─ Matcher.* // core matching algorithm
├─ schedule.txt // example schedule output
├─ Cargo.txt / Freight.txt // example input data
└─ main.cpp // program entry-point

---

## 🚀  Getting started

### 1.  Prerequisites

* A C++17-capable compiler (GCC 9+, Clang 10+, MSVC 2019).  
* CMake 3.15+ or just a shell with `g++`/`clang++`.
* Visual Studio 2022
* GitHub Desktop

### 2.  Build & run (one-liner)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o oop_v2 \
    src/*.cpp
./oop_v2

```
OR
```bash
Copy GitHub Repo link and pull. DO NOT COMMIT. 
```
Project done by: jullion14, JunXuanSIT, Kktanker, GhosterRoller and Leepq
