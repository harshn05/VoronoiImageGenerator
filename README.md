# Voronoi Image Generator

This project generates Voronoi diagrams as images. It uses OpenMP for parallel processing to speed up the generation of the diagrams.

## Requirements

- CMake
- A C++ compiler with OpenMP support

## Building the Project

1. Clone the repository:
2. Navigate into the project directory:
3. Create a new directory for the build:
4. Run CMake to configure the project and generate a Makefile:
5. Build the project:
   
## Usage

After building the project, you can run the program with the following command:

```

./Voronoi [width] [height] [numPoints] [seed]


- `width`: Width of the image (default: 1000)
- `height`: Height of the image (default: 1000)
- `numPoints`: Number of points (default: 100)
- `seed`: Seed for the random number generator (default: 0)

The program will generate a PNG image named `voronoi.png` in the current directory.
```
