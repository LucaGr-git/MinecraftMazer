# 🧩 Minecraft Maze Generator & Solver (C++)

A fully immersive **C++ application** that **generates**, **solves**, and optionally **removes** a procedural maze inside a live **Minecraft world** using the mccp library– all **without altering the surrounding terrain** once completed.



---

## 👥 Group Details

| GitHub Username    | Student Name       |
|--------------------|--------------------|
| Akhan-SE        | Alysha Khan         |
| LucaGr-git         | Luca Grosso         |
| TommyNgucode       | Tommy Nguyen        |

**Video Code Demo:**  
https://rmiteduau-my.sharepoint.com/:v:/g/personal/s4095471_student_rmit_edu_au/EVLrLFv_4eFGqD4tPLNDb6MB-A2hawAcKiCDr0lODQbPmQ?e=4IN7Yz

- Enhancement features shown are not finalised

---

## 🚀 Key Features

| Category               | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Maze Generation     | Generates a maze structure using a maze generation algorithm in Minecraft   |
| Maze Solver         | Automatically finds the shortest path from start → finish                   |
| Cleanup Mode        | Removes **only** the maze blocks afterwards, restoring original terrain     |
| Immersive Gameplay  | Entire maze is rendered in the live Minecraft world  |


---

## 🎯 Task Allocation

| Student          | Tasks                                                                 |
|------------------|-----------------------------------------------------------------------|
| **Luca Grosso**  | Build Maze + Cleanup (E1) • Testing Alysha’s Code                      |
| **Alysha Khan**  | Maze Solving Functions (E2) • Testing Tommy’s Code                     |
| **Tommy Nguyen** | Maze Generation Functions (E3) • Testing Luca’s Code                   |

---


---

## ⚙️ How to Compile & Run

```bash
# Compile
g++ -std=c++17 -o mazeRunner main.cpp

# Run (Normal Mode)
./mazeRunner

```

> Note that you will need to set up a Minecraft spigot server that runs on a compatible version with the mccp library 

---

