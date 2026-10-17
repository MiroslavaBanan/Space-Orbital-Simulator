# 🪐 Space-Orbital-Simulator (OrbitLab)

An interactive, high-performance 2D orbital simulation engine that models space trajectories using physics computations. The project combines low-level algorithmic efficiency with a modern, responsive web interface.

## 🚀 Live Demonstration
*(Note: Upload your custom orbital animation GIF here to impress the committee instantly!)*

![Orbit Simulation Demo](python_web/animation.gif)

## 🧠 System Architecture & Data Flow

The application is built on a hybrid architecture, bridging low-level computational speed with dynamic web rendering:

1. **Frontend (JavaScript):** Intercepts the user input using the **Fetch API / AJAX**, packaging configuration variables into a **JSON payload** without reloading the page.
2. **Web Server (Python/Flask):** Receives the JSON data, processes it into a streamlined text sequence separated by newlines (`\n`), and executes the C engine.
3. **Physics Core (C-Backend):** Runs natively to handle intense numerical gravity integration, outputs the results instantly into an optimized `orbit.csv` file, and exits.
4. **Data Processor (Pandas):** Reads the generated CSV data in Python, structures it, and maps coordinates via **Matplotlib** to compile a dynamic web-ready GIF asset returned to the frontend.

## 🔬 Physics Core & Optimization (C-Backend)

The mathematical heart of the project runs entirely on **pure C**, utilizing highly optimized custom structures for zero-overhead physical calculations:

* **Vector Mathematics:** Velocities, positions, and acceleration components are safely encapsulated into nested `Vector` and `PointObject` types.
* **Newtonian Gravity Integration:** Trajectories are solved directly based on Newton's law of universal gravitation ($a = G \cdot \frac{M}{r^2}$).
* **Memory & Pointer Optimization:** Objects are passed into computational blocks exclusively **by reference using pointers (`*obj`)**. This guarantees $O(1)$ algorithmic efficiency, avoiding redundant stack memory allocation during continuous execution loops.

## 💻 Tech Stack

* **Core Engine:** C (GCC Compilers, `<math.h>`)
* **Web Architecture:** Python 3, Flask
* **Data Processing & Analytics:** Pandas
* **Data Visualization:** Matplotlib (FuncAnimation)
* **Frontend Interface:** HTML5, CSS3 (Custom Dark Theme), JavaScript (ES6+ Asynchronous Fetch)

## 🛠️ Quick Start Guide

### 1. Compile the C Computational Engine
Navigate to your C backend folder and compile the native binary:
```bash
gcc c_backend/orbit.c -o c_backend/orbit -lm
```
```markdown
### 2. Install Python Dependencies
Install required packages for data handling and server execution:
```bash
pip3 install flask pandas matplotlib pillow
```
```markdown
### 3. Launch the Server
Run the web application locally:
```bash
python3 python_web/app.py
```
Open your web browser and navigate to: `http://127.0.0.1:8080`
```
