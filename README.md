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
TO BE UPLOADED

- Enhancement features shown are not finalised

<img width="1714" height="987" alt="image" src="https://github.com/user-attachments/assets/09825c62-e3ee-4131-af50-949a27c16fff" />


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
| **Luca Grosso**  | Build Maze + Cleanup  • Testing Alysha’s Code                      |
| **Alysha Khan**  | Maze Solving Functions  • Testing Tommy’s Code                     |
| **Tommy Nguyen** | Maze Generation Functions  • Testing Luca’s Code                   |

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
> https://github.com/rozukke/mcpp 

---

