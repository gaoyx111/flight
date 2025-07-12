# Flight ✈️

This project is a Qt-based flight management system written in **C++**, featuring a graphical user interface, back-end logic, and a SQL database. It supports flight search, ticket booking, payment, refund/rescheduling, and both user and administrator workflows. GUI is designed using `.ui` files and integrates embedded images and multilingual support via Qt's translation system.

---

## 🚀 Features

### 👤 User Features

- **Flight Search** by city, date, duration, or price
- **Booking** with cabin class options and unique ticket IDs
- **Order Management**: upcoming, unpaid, completed
- **Refund / Reschedule** with confirmation dialogs
- **Payment Options**: credit card, Alipay, WeChat Pay
- **Profile Editing**: name, nickname, birthday

### 🛠️ Admin Features

- Flight management (create, edit, delete, search)
- Admin profile update

---

## 🧱 Tech Stack

| Component         | Description                    |
|------------------|--------------------------------|
| Language          | C++ (C++17 standard)            |
| GUI Framework     | Qt (with `.ui` forms + widgets) |
| Database          | SQL via `QSqlQuery`             |
| Translation       | Qt Linguist (`FlightProject_zh_CN.ts`) |
| Resource Handling | Qt Resource System (`flight_images.qrc`) |

---

## 🛠️ Build & Run Instructions

### 💡 Prerequisites

- **Qt 5.x or 6.x**
- **Qt Creator** or `qmake + make`
- C++17 compatible compiler

### 🔧 Build with Qt Creator (Recommended)

1. Open `FlightProject.pro` in Qt Creator
2. Configure the Kit (Desktop, MinGW/GCC/Clang as applicable)
3. Click `Build` → `Run`

### 🔧 Build with command line

```bash
qmake FlightProject.pro
make        # or mingw32-make on Windows
./FlightProject
