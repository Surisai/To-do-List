# To-do-List

![screenshot](image/Screenshot%202025-09-19%20at%201.51.09%E2%80%AFAM.png)

A simple cross-platform to-do list app built with C++ and wxWidgets.

## Features
- Add, delete, and clear tasks
- Mark tasks as done
- Move tasks up and down
- Responsive UI (sizer-based)

## Build
Requires wxWidgets and a C++17 compiler.

```
g++ -std=c++17 App.cpp MainFram.cpp Task.cpp -o todo_app `wx-config --cxxflags --libs`
```

## Run
```
./todo_app
```

## Author
Surisai