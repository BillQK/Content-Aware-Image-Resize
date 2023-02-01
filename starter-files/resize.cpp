#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix.hpp"

using namespace std;


int main(int argc, char **argv) {
    string inputFile, outputFile; 
    int width, height; 

    inputFile = argv[1];
    outputFile = argv[2];
    width = stoi(argv[3]);
    height = stoi(argv[4]);

    cout << inputFile << " " << outputFile << " " << width << " " << height << endl;

    Image img; 
    ifstream ifs(inputFile);
    img.read_ppm(ifs); 


    if (width > 0 && width < (img.get_width() || width == img.get_width())) { 
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;

    }
    else if (height > 0 && height < (img.get_height() || height == img.get_height())) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    else { 
        Image new_img;
        if (height == 0) {
            new_img = seam_carve_width(img, width); 
        }
        else {
            new_img = seam_carve(img, width, height);   
        }
        ofstream ofs(outputFile); 
        new_img.print(ofs);
    }


}