#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

// The exact values is defined in file format specification
#define IMG_MAGIC 2051
#define LBL_MAGIC 2049

// Learning sample
// Note: uint8_t is used due to standard
// of MNIST-dataset provided files
struct sample {
    sample();
    sample(int width, int height);

    int w, h;
    std::vector<uint8_t> image;
    uint8_t label;

    // Sets the dimensions 'w' and 'h' explicitly
    void set_dimensions(int width, int height);
    // Prints the lable and image to the standard output
    // Internaly uses 'ascii_art()' function (see below)
    void display();
};

// Reads single image specified by 'width' and
// 'height' to the vector 'vec' representing this
// image in one-line 'pixel-brightness-values' manner.
template <class T>
void read_img(std::ifstream* file, std::vector<T>* vec, int width, int height);

// Reads set of images of the same size specified
// by 'w' and 'h' to the vector 'vec'.
// Internally utilizes thed read_imgset()' function
// described above.
template <class T>
void read_imgset(std::ifstream* file, std::vector<T>* vec, uint32_t imgnum, int w, int h);

// Reads single lable for the image
template <class T>
void read_lbl(std::ifstream* file, T* label);

// Reads 'lblnum' amount of labels to 'vec'
template <class T>
void read_lblset(std::ifstream* file, std::vector<T>* vec, uint32_t lblnum);

// Packs the train set to the vector 'vec' of
// structers 'sample' (see declaration above)
// Result - is a complete train set vector
void pack_trainset(const char* imgfile, const char* lblfile, std::vector<sample>* vec, uint32_t sz);

// Swaps the endianness of the given object.
template <class T>
void endswap(T* ptr);

// Writes the image(s) to the standard output,
// deviding at every 'width+1' character with
// '\n' in ASCII-format.
template <class T>
void ascii_art(std::vector<T>* vec, int width);