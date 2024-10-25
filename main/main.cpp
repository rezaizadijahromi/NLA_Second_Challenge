#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main(int argc, char *argv[])
{
    // Error if forget image path
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <image_path>" << endl;
        return 1;
    }

    // assign image path
    const char *input_image_path = argv[1];
    // 1
    // Load the image using stb_image
    int width, height, channels;
    // Force load as B&W
    unsigned char *image_data = stbi_load(input_image_path, &width, &height, &channels, 1);

    // error loading image
    if (!image_data)
    {
        cerr << "Error: Could not load image " << input_image_path
             << endl;
        return 1;
    }

    // print image parameters
    cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << endl;

    // Prepare Eigen matrix for B&W channel
    MatrixXd original(height, width);

    // Fill the matrices with image data
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 1; // 1 channels (B&W)
            original(i, j) = static_cast<double>(image_data[index]) / 255.0;
        }
    }

    // Free memory
    stbi_image_free(image_data);

    MatrixXd result = original.transpose() * original;
    float norm = result.norm();

    cout << "The norm is: " << norm << endl;

    return 0;
}