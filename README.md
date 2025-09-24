# Envelop Budget Application

## Project Overview
This project is an **Envelope Budget Management System** written in **C++**.
It implements the classic “Envelope Method” for budgeting, where the available money is divided into different envelopes for specific categories.   
Unlike most budget apps on the market that only flag overspending, this system can automatically rebalance envelopes when funds are insufficient, while respecting locked envelopes (such as savings).
This feature provides more flexibility and control compared to existing tools, and forms a solid base for future web or mobile apps.

## Project Structure
├── Class Envelop  
├── Class EnvelopManager  
├── Class FixedExpenses  
├── utils.h / utils.cpp  
├── main.cpp  
├── Makefile  


## Features
- Add, update, and remove envelopes.
- Lock/unlock envelopes to prevent balancing.
- Display all envelopes and remaining free balance.
- **Automatic balancing:** when funds are insufficient, other unlocked envelopes are scaled down proportionally.  
- **Locked envelopes:** protect specific categories (e.g., savings) from being adjusted during balancing.  
- **Transfers:** move money seamlessly between envelopes.  

## Requirements
g++ with **C++11** (or newer).  

### Linux / macOS
- Install g++ via your package manager (e.g. `sudo apt install g++ make`).

### Windows
- Option 1: Use MinGW-w64 (includes g++ and make).
- Option 2: Use Visual Studio (MSVC) and create a project with the source files.
- Option 3: Use WSL (Windows Subsystem for Linux) and follow the Linux instructions.

  
## Build & Run  
make  
./envelop
