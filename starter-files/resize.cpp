#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix.hpp"

using namespace std;

int main(int argc, char **argv)
{
    (void)argc;
    string inputFile, outputFile;
    int width, height;

    inputFile = argv[1];
    outputFile = argv[2];
    width = stoi(argv[3]);
    if (stoi(argv[4]))
    {
        height = stoi(argv[4]);
    }
    else
    {
        height = 0;
    }

    cout << inputFile << " " << outputFile << " " << width << " " << height << endl;

    Image img;

    ifstream ifs(inputFile);
    if (ifs.is_open())
    {
        img.read_ppm(ifs);
    }
    else
    {
        cout << "Error opening file: " << inputFile << endl;
        return 0;
    }

    if (width > img.get_width() || (height > 0 && height > img.get_height()))
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    else
    {
        Image new_img;
        if (height == 0)
        {
            new_img = seam_carve_width(img, width);
        }
        else
        {
            new_img = seam_carve(img, width, height);
        }
        ofstream ofs(outputFile);
        new_img.print(ofs);
    }

    return 0;
}