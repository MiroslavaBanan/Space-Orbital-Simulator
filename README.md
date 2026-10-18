# 🪐 Space-Orbital-Simulator (OrbitLab)

OrbitLab is an interactive 2D orbital simulation engine that models space trajectories using physics computations. OrbitLab uses C to calculate orbital motion, then passes the results to Python, Flask, and JavaScript to turn the coordinates into visual trajectories in an interactive web interface.

## Live Demonstration

![Orbit Simulation Demo](python_web/animation.gif)

## System Architecture & Data Flow

The application is built on a hybrid architecture, bridging low-level computational speed with dynamic web rendering:

1. **Browser (JavaScript):** The user enters coordinates in a form, and JavaScript sends them to the Python server as JSON without reloading the page.
2. **Web Server (Python/Flask):** Flask receives the JSON data, converts the parameters into newline-separated input, and passes them to the C engine.
3. **Physics Core (C-Backend):** Python runs the C engine through the command line, passes it the input data, captures its console output and errors, while C calculates the trajectories and writes the resulting coordinates to `orbit.csv` file.
4. **Visualization (Pandas and Matplotlib):** Python uses Pandas to read the coordinates from `orbit.csv` and Matplotlib to turn them into a GIF displayed in the browser.

## The Physics Behind the Orbits

OrbitLab models a satellite orbiting Earth using Newton's law of universal gravitation. Earth stays fixed at coordinates (0, 0), while the satellite moves under its gravitational pull. Its acceleration is calculated using:

$$
a = \frac{GM}{r^2}
$$

* **Vector and PointObject:** To keep the code organized, I created a `PointObject` structure that stores position, velocity, and acceleration as `Vector` values with `x` and `y` components. This reduces repetitive variable declarations and keeps `main()` clean by moving the setup into a separate function.
* **Memory & Pointer:** I used pointers to modify objects directly inside functions, while passing time values and constants by value to keep the code straightforward.

## Tech Stacks

* **Physics engine:** C, GCC, `<math.h>`
* **Web server:** Python3, Flask
* **Data Processing:** Pandas
* **Data Visualization:** Matplotlib + FuncAnimation, Pillow
* **Frontend Interface:** HTML5, CSS3, JavaScript

## Quick Start Guide

You'll need Python 3, GCC, and pip installed.

### 1. Compile the C engine
Run this command from the project root:
```bash
gcc c_backend/orbit.c -o c_backend/orbit -lm
```
```markdown
### 2. Install Python Dependencies
```bash
pip3 install flask pandas matplotlib pillow
```
```markdown
### 3. Launch the Server
```bash
python3 python_web/app.py
```
Open in your browser. `http://127.0.0.1:8080`
```
