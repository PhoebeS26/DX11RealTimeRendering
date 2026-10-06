# DX11 Real-Time Rendering

A C++ and DirectX 11 real-time rendering project exploring 3D graphics, lighting, textures, cameras and rendering pipeline features.

## Overview

This project was developed using **C++ and DirectX 11** to explore real-time 3D rendering and the DirectX 11 graphics pipeline.

The project includes custom rendering code, HLSL shaders, textured 3D objects, multiple cameras, lighting systems and a skybox. Scene and lighting information can also be loaded from JSON files.

## Features

* DirectX 11 rendering pipeline setup
* C++ vertex and index buffer management
* HLSL vertex and pixel shaders
* 3D transformations including translation, rotation and scaling
* Texture loading and texture sampling
* Ambient, diffuse and specular lighting
* Spotlight lighting
* Multiple cameras, including a flying camera
* Skybox rendering
* OBJ model loading
* JSON-based scene and lighting configuration
* Solid and wireframe rendering modes
* Transparency and blending
* Depth and rasterizer state configuration

## Controls

### Camera Selection

* **1** — Access static camera 1
* **2** — Access static camera 2
* **3** — Access the flying camera

### Flying Camera

* **WASD** — Move the flying camera
* **Arrow Keys** — Look around with the flying camera

## Technical Skills

**Languages**

* C++
* HLSL

**Technologies & Tools**

* DirectX 11
* Visual Studio
* GitHub

## What I Worked On

I worked with the DirectX 11 rendering pipeline, including device and swap-chain setup, render targets, depth buffers, shaders, input layouts and GPU buffers.

I implemented and worked with HLSL shaders for textured 3D objects and lighting effects. The rendering system supports ambient, diffuse, specular and spotlight lighting.

I also worked with scene configuration through JSON, allowing objects, textures and lighting properties to be loaded from external files rather than being entirely hard-coded.

The project includes multiple cameras, animated world transformations, OBJ model loading, skybox rendering and different rasterizer and blending states.

## Project Structure

The main rendering code is contained within the `DX11Framework` directory, alongside shader files, model data and JSON configuration files.

Key components include:

* `DX11Framework.cpp` — DirectX 11 setup, rendering pipeline and frame rendering
* `GameObject.cpp` — reusable 3D object rendering and transformation handling
* `SimpleShaders.hlsl` — main object vertex and pixel shaders
* `SkyboxShader.hlsl` — skybox shaders
* `SceneLoader.cpp` — scene and object loading
* `OBJLoader.cpp` — OBJ model loading
* `Lights.json` — lighting and material configuration
* `Scene.json` — scene object configuration

## What I Learned

This project gave me practical experience working with C++ and DirectX 11, particularly around the graphics pipeline, shaders, buffers, transformations, lighting and rendering states.

It also helped me develop a better understanding of how different parts of a real-time rendering system work together.

<img width="1259" height="752" alt="image" src="https://github.com/user-attachments/assets/cd16c915-1133-472f-9b6b-9cb13a0306e8" />
