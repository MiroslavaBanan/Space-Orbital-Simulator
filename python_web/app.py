import matplotlib
matplotlib.use('Agg') 

import io
import base64
import subprocess
from flask import Flask, render_template, request, jsonify
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent
C_BACKEND = BASE_DIR.parent / "c_backend"
CSV_PATH = C_BACKEND / "orbit.csv"
GIF_PATH = BASE_DIR / "animation.gif"

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/run", methods=["POST"])
def run_simulation():
    # 1. Taking values frim json
    x_position = request.json.get("x_position")
    y_position = request.json.get("y_position")
    x_velocity = request.json.get("x_velocity")
    y_velocity = request.json.get("y_velocity")
    delta_time = request.json.get("delta_time")
    simulation_time = request.json.get("simulation_time")

    # Making a string for C
    input_string = f"{x_position}\n{y_position}\n{x_velocity}\n{y_velocity}\n{delta_time}\n{simulation_time}\n"


    # Send this string to C
    result = subprocess.run(
    ["./orbit"],
    input=input_string,
    capture_output=True,
    text=True,
    cwd=C_BACKEND
)

    print("Код возврата Си:", result.returncode)

    # Print an error if something wrong
    if result.returncode != 0:
        print("Error inside C code:", result.stderr)
        print("Output of C program:", result.stdout)

        return {
            "status": "error",
            "message": "C simulation failed"
        }, 500

    # Read orbit.csv in python
    df = pd.read_csv(CSV_PATH)

    if not CSV_PATH.exists():
        print("File orbit.csv wasn't found!")
        return jsonify({"status": "error", "message": "CSV file not found"}), 404

    # Make a graph with dark background
    site_bg = '#060A12'
    fig, ax = plt.subplots(facecolor=site_bg)
    ax.set_facecolor(site_bg)

    # Setting a blue shining line
    line, = ax.plot([], [], color='#007aff', linewidth=3)
    earth = plt.Circle((0, 0), 6371000, color='#1a365d', alpha=0.8)

    ax.add_patch(earth)
    dot, = ax.plot([], [], 'o', color='#00ffff', markersize=6)

    max_val = max(
        df['x'].abs().max(), 
        df['y'].abs().max(), 
        6371000
    ) if len(df) > 0 else 7000000

    view_limit = max_val * 1.2

    ax.set_xlim(-view_limit, view_limit)
    ax.set_ylim(-view_limit, view_limit)

    ax.set_aspect('equal', adjustable='box')
    ax.axis('off')


    def update(frame):
        if frame >= len(df):
            frame = len(df) - 1
        
        line.set_data(df['x'].iloc[:frame + 1], df['y'].iloc[:frame + 1])
        dot.set_data([df['x'].iloc[frame]], [df['y'].iloc[frame]])
        
        return line, dot

    ani = FuncAnimation(fig, update, frames=len(df) + 2, interval=30, blit=True)

    ani.save(GIF_PATH, writer='pillow', fps=30)
    plt.close()

    with open(GIF_PATH, 'rb') as gif_file:
        gif_bytes = gif_file.read()
        
    gif_base64 = base64.b64encode(gif_bytes).decode('utf-8')

    return jsonify({
        "status": "success",
        "animation": f"data:image/gif;base64,{gif_base64}"
    })

if __name__ == "__main__":
    app.run(debug=True, port=8080)