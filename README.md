# Assignment 2: GDExtension Sprite2D Demonstration

## Overview

This project demonstrates extending the Godot 4 `Sprite2D` node using **GDExtension in C++**. The custom node `Pseudo3DRotatingSprite` introduces new features including:

- **Pseudo-3D rotation** with squish effect
- **Fade-in and fade-out animation**
- **Play, pause, and stop methods** for animation control

These features are exposed to the Godot editor and interact via signals to demonstrate both **emitting and receiving signals**, fulfilling the rubric requirements.

---

## Features

### 1. Pseudo-3D Rotation (Squish)

- The sprite visually rotates in 2D while appearing to squish along its x-axis.
- **Editor-exposed property:** `rotation_speed` (controls rotation speed)
- **Editor-exposed property:** `max_squash` (controls the maximum horizontal squash)
- Emits the signal `rotation_completed` after completing one full rotation.
- Can be reset externally with the `reset_rotation()` method.

---

### 2. Fade-In / Fade-Out Animation

- Sprite can fade in and out over time during rotation.
- **Editor-exposed properties:** 
  - `fade_enabled` (enable/disable fade)
  - `fade_intensity` (control the strength of fading)
- Provides visual animation **without using the built-in AnimationPlayer**.
- Can be controlled programmatically via `play()`, `pause()`, and `stop()`.

---

### 3. Signal Interaction

- Each `Pseudo3DRotatingSprite` node emits `rotation_completed` after a full rotation.
- Each node can **react to signals from other nodes** by pausing itself and starting the next node, demonstrating signal-to-method interaction.

Example of alternating rotation between two nodes:

- `Rotator1` finishes → emits `rotation_completed` → triggers `Rotator2.play()` → `Rotator1.pause()`
- `Rotator2` finishes → emits `rotation_completed` → triggers `Rotator1.play()` → `Rotator2.pause()`

This demonstrates **both emitting a signal** and **triggering a method in another node**.

---

### 4. Play / Pause / Stop Methods (Extra Credit)

- Methods `play()`, `pause()`, `stop()` control the node’s rotation and animation.  
- These allow runtime control of sprite animation, fulfilling the **interesting animations extra credit requirement**.

---

## Scene Setup

1. Add multiple `Pseudo3DRotatingSprite` nodes to a `Node2D` scene.  
2. Assign `next_rotator` NodePath in the Inspector to alternate rotations.  
3. Optionally, attach a small parent script to start the first node automatically:

```gdscript
extends Node2D

@onready var rot1 = $Rotator1

func _ready():
    rot1.play()
