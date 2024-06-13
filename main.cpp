#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <omp.h>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct Point
{
    int x, y;
    unsigned char r, g, b;
};

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [width] [height] [numPoints] [seed]\n";
        std::cout << "width: Width of the image (default: 1000)\n";
        std::cout << "height: Height of the image (default: 1000)\n";
        std::cout << "numPoints: Number of points (default: 100)\n";
        std::cout << "seed: Seed for the random number generator (default: 0)\n";
        std::cout << "Example: " << argv[0] << " 2000 2000 1000 10\n";
        return 0;
    }
    int width = argc > 1 ? atoi(argv[1]) : 1000;
    int height = argc > 2 ? atoi(argv[2]) : 1000;
    int numPoints = argc > 3 ? atoi(argv[3]) : 100;
    int seed = argc > 4 ? atoi(argv[4]) : 0;

    srand(seed);

    std::vector<unsigned char> img(width * height * 3, 255);

    std::vector<Point> points;
    for (int i = 0; i < numPoints; ++i)
    {
      points.push_back({rand() % width, rand() % height, static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256)});

    }

#pragma omp parallel for
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Point p{x, y};
            float minDist = std::numeric_limits<float>::max();
            Point closestPoint;

            for (const Point &point : points)
            {
                //float dist = std::sqrt(std::pow(p.x - point.x, 2) + std::pow(p.y - point.y, 2));
                //sqrt can be dropped if dist is squared to the power of 2 and compared to minDist
                float dist = std::pow(p.x - point.x, 2) + std::pow(p.y - point.y, 2);
                if (dist < minDist)
                {
                    minDist = dist;
                    closestPoint = point;
                }
            }

            img[(y * width + x) * 3 + 0] = closestPoint.r;
            img[(y * width + x) * 3 + 1] = closestPoint.g;
            img[(y * width + x) * 3 + 2] = closestPoint.b;
        }
    }

    stbi_write_png("voronoi.png", width, height, 3, img.data(), width * 3);

    return 0;
}