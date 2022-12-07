// https://github.com/RedGuff/ColoredTextureGenerator/edit/master/main.cpp enhanced:
#include <iostream>
#include <cstdlib> // https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Standard_C_Library/Functions/system
#include <fstream>
#include <math.h>
#include <time.h> // enough
#include <vector>
using namespace std;

int maxHz = 128; // pixels of the half image, the size of the futur pattern.
int maxVt = 128; // pixels of the half image, the size of the futur pattern.
const int nbComposantRGB = 3;
const int minRGB = 0; // Each. // 0 min, 65535 max.
const int maxRGB = 65535; // Each. // 0 min, 65535 max.
// const int maxRGB = 65535; // Each. // 0 min, 65535 max..
int rgb = 1; // R = 1, G = 2, B = 3.
vector<vector<vector<int> > > imageTableauRGB_int(2*maxHz, vector<vector<int> >(2*maxVt, vector<int>(nbComposantRGB, 0)));





int vector2ppm(vector<vector<vector<int>>>& imageTableauRGB_int, string name_noext = "file") { // colors // Rewrite with size()!
    string name_ext = name_noext + ".ppm";
    ofstream replaceFile(name_ext.c_str()); // remplace!
    if(!replaceFile) {
        cerr << "Impossible to open the file " << name_ext << " in order to write in it!" << endl;
    } else {
        string whiteS = "              "; // Log et répét ?
        replaceFile << "P3" << endl; // PPM format...
        replaceFile << imageTableauRGB_int.size() << " " << imageTableauRGB_int[0].size() << endl;
        replaceFile << maxRGB << endl << endl;
        for(int h = 0; h < imageTableauRGB_int.size(); h++) {
            for(int v = 0; v < imageTableauRGB_int[0].size(); v++) {
                for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
                    replaceFile << imageTableauRGB_int[h][v][rgb] << " " ;
                }
                replaceFile  << endl;
            }
            cout << whiteS + "\r" << h << "/" << maxVt;
            replaceFile << endl; // For a new line eache line.
        }
    }
    replaceFile.close();
    return 0;
}






void initMatrixRandomDD(vector<vector<vector<int>>>& imageTableauRGB_int) { // Rewrite with size()!
    int c = 0;
    for(int h = 0; h < maxVt; h++) {
        for(int v = 0; v < maxHz; v++) {
            for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
                    c=minRGB + rand() % maxRGB;;
                imageTableauRGB_int[h][v][rgb] = c;
               imageTableauRGB_int[h][v+maxHz][rgb] = c;
                imageTableauRGB_int[h+maxVt][v][rgb] = c;
                imageTableauRGB_int[h+maxVt][v+maxHz][rgb] = c;
            }
        }
    }
}

int main() { // Rewrite with size()!
    srand(time(NULL));       // No need for better init. // May be need to be reproductible.
    if(maxRGB >= 65536) {
        printf("\033[%dm", 31); // GNU/Linux only!
        cerr << "Err: maxRGB can't be more than 65536 for PPM." << endl;
        printf("\033[%dm", 0);
        cout << "End." << endl;
    } else {
        cout << "Pseudo-random tilable texture (ASCII PPM image)." << endl;
        cout << "maxHz = " << maxHz << " pixels." << endl;
        cout << "maxVt = " << maxVt << " pixels." << endl;
        cout << "maxRGB = " << maxRGB << " < 65536: ok." << endl;
        cout << "nbComposantRGB = " << nbComposantRGB << "." << endl;
        cout << "When needed, give the name without the extension, and with optional relative or absolute path." << endl;
// Create seamless trivial image (solid color), (init):



// Convert to file:
        string name_noext = "";
        while(name_noext == "") {
            cout << "\a\nThe name without extension, please?" << endl;
            getline(cin, name_noext);
        }

        initMatrixRandomDD(imageTableauRGB_int);
        vector2ppm(imageTableauRGB_int, name_noext);


        clog << "\nFile ok: " << name_noext;
    }
    return 0;
}
