# Minesweeper Plugin

A tech demo for GeoTech

## Why this project matters

This project is designed as a **technical showcase**. The goal is to demonstrate my ability to:

* Work with **Unreal Engine 5.5** at the C++ level.
* Build custom editor tools using **Slate**.
* Implement complete gameplay logic (state handling, win/lose conditions, recursive cell reveal).
* Structure a plugin that integrates cleanly into the UE editor (toolbar button, menu entry, and custom tab).

In short: this project shows both **engine-level knowledge** and **UI/gameplay implementation skills**

---

## What is this

This is a technical test requested by GeoTech.
The purpose is to demonstrate my capabilities with Unreal Engine, with a particular focus on **Slate** and **C++**.

If interested, you can find the original task [here](https://docs.google.com/document/d/1doJ_hro5Ryb7pl4heRcIPLJmQL8LKhdZX1elJ4PjZCs/edit?tab=t.0).

### Ok, but really, what is this?

This project, built with **Unreal Engine 5.5**, contains a plugin that adds a clone of the classic Microsoft Minesweeper game to your project.
That’s it.

---

## How to use it

The project is built using Unreal Engine 5.5.
You can clone this repository and build the solution without any additional steps required.
Alternatively, you can take only the `Plugins` folder and add it to one of your existing projects without further setup.

Inside the editor there are two ways to open the Minesweeper window:

* From the menu: **Window → Minesweeper** (at the very bottom)
* From the **toolbar**, by clicking directly on the Minesweeper button

---

## The game window

From the game window you can set the **height**, **width**, and **number of mines**.
The **Create new game** button will use these values to generate a new game instance every time it is pressed.

The game logic is the one we all know:

* If you click on a mine, you lose.
* If you clear the field, you win.
* Numbers indicate how many mines are present in the 8 surrounding cells.

---

# About AI / LLM

I have been working with Unreal Engine since the old **Unreal 3** and **UnrealScript**.
In the last three years, I’ve worked full time on UI under UE5, with **UMG and Widgets as my daily tools**.

This is to say that I know what I am doing first of all.
That said, I also use **LLM-based tools daily** (for over a year now).

I can understand why some people might be skeptical, but I am firmly convinced that if you know what you are doing, these tools can significantly **enhance productivity and workflow**.

### How did I use AI in this project?

* To format some parts of Slate, for example to check how to achieve the grid layout visible in this project.
* To speed up repetitive editing of Slate code (usually a tedious trial-and-error process).
* To act as a “second pair of eyes” on the overall project. After finishing, I ask the AI for a review: despite occasional hallucinations (where expertise really matters), useful insights always emerge.
* To polish and properly format this README file.
