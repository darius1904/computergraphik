# 🖼️ Image Filtering Exercises – Computer Graphics WS 2025/26

![C++](https://img.shields.io/badge/Language-C++-blue?logo=c%2B%2B)
![OpenGL](https://img.shields.io/badge/OpenGL-4.3+-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Windows-yellow)

**Course:** Computer Graphics WS 2025/26  
**Discussion Dates:** 12–14 Jan 2026  

This repository contains implementations of **image filtering operations** on CPU and GPU, including **edge detection**, **Gaussian blur**, and border policies, using a simple OpenGL-based viewer.

---

## 📂 Project Structure

ImageFilter/ # Source folder
├─ Image.h # Image class definition
├─ ImageFilter.h # Filter kernels & operations (header)
├─ ImageFilter.cpp # Kernel implementations
├─ ImageViewer.cpp # Main program / GUI viewer
├─ shaders/ # GPU compute shaders
├─ bilder/ # Sample images (PPM format)
└─ CMakeLists.txt # Build configuration

yaml
Copy code

---

## 🛠️ Build Instructions (Windows + MinGW)

Open **Windows Terminal** and run the following:

```powershell
cd C:\path\to\your\project
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
.\ImageViewer.exe
⚡ GPU mode is significantly faster for separated Gaussian filtering.

🖱️ Usage
GUI Mode
Launch ImageViewer.exe

Select an input .ppm image

Choose CPU or GPU mode

Select a filter (Edge Detection, Gaussian Blur, Separated Gaussian)

Adjust parameters (kernel size, sigma) and click Update

Command-Line Mode
powershell
Copy code
.\ImageViewer.exe ../bilder/gingko.ppm ../bilder/gingko_edge.ppm
Paths are relative to the current working directory. Use image viewers like GIMP or Photoshop to open .ppm outputs.

🔹 Exercises Covered
Aufgabe 1 – Framebuffer
Define framebuffer and its purpose.

Explain 16-bit highcolor (5 bits R/B, 6 bits G) and why green is favored.

Calculate memory usage for 4K video, 36-bit color, 24 FPS, 1 hour.

Aufgabe 2 – Image Representation
Explain aliasing and why it occurs.

Methods to reduce aliasing.

List three types of aliasing in discretization.

Aufgabe 3 – CPU Filter Operations
filterImage: Applies kernel to image with per-channel accumulation.

buildEdgeDetectionKernel: Implements 3×3 Laplacian edge detection.

edgeDetection2D: Applies edge detection and converts to absolute values.

setGaussianValues: Computes and normalizes 2D Gaussian kernel entries:

cpp
Copy code
g(x,y) = 1/(2πσ²) * e^(-(x² + y²)/(2σ²))
gaussian2D & seperatedGaussian2D: Apply full 2D or separated Gaussian filtering.

Border Policies:

CLAMP_TO_EDGE: Already implemented

MIRROR: Reflect at image edges

REPEAT: Repeat the image at borders

Experiment with kernel size, σ, and border policies to see different filtering results.
⚠️ Combining Edge Detection with REPEAT may produce artifacts at edges.

⚡ Notes on GPU Filtering
GPU acceleration is implemented with OpenGL 4.3 Compute Shaders.

Separated Gaussian filtering on GPU is much faster than full 2D convolution on CPU.

Requires OpenGL 4.3+ compatible GPU.

CPU filtering is suitable for testing or environments without GPU support.