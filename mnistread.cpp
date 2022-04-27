#include "mnistread.h"

// 'sample' struct member functions definitions
sample::sample() {
    w = 0;
    h = 0;
    label = 10; // Artificial value
}

sample::sample(int width, int height) {
    w = width;
    h = height;
    label = 10; // Artificial value
}

void sample::set_dimensions(int width, int height) {
    w = width;
    h = height;
}

void sample::display() {
    std::cout << "\n" << "---|" << (int)label << "|---";
    ascii_art(&image, w);
}

template <class T>
void read_img(std::ifstream* file, std::vector<T>* vec, int width, int height) {
    T curval;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file->read(reinterpret_cast<char*>(&curval), sizeof(T));
            vec->push_back(curval);
        }
    }
}

template <class T>
void read_imgset(std::ifstream* file, std::vector<T>* vec, int imgnum, int w, int h) {
    for (int i = 0; i < imgnum; i++) {
        read_imgset(file, vec, w, h);
    }
}

template <class T>
void read_lbl(std::ifstream* file, T* label) {
    file->read(reinterpret_cast<char*>(label), sizeof(T));
}

template <class T>
void read_lblset(std::ifstream* file, std::vector<T>* vec, int lblnum) {
    T curlbl;
    for (int i = 0; i < lblnum; i++) {
        file->read(reinterpret_cast<char*>(&curlbl), sizeof(T));
        vec->push_back(curlbl);
    }
}

void pack_trainset(const char* imgfile, const char* lblfile, std::vector<sample>* vec, uint32_t sz) {
    uint32_t img_magic, lbl_magic, max_img, max_lbl, w, h;
    
    std::ifstream imgfs(imgfile, std::ios::binary);
    // Reading img-header
    imgfs.read(reinterpret_cast<char*>(&img_magic), 4);
    imgfs.read(reinterpret_cast<char*>(&max_img), 4);
    imgfs.read(reinterpret_cast<char*>(&w), 4);
    imgfs.read(reinterpret_cast<char*>(&h), 4);
    if (img_magic != IMG_MAGIC) {
        endswap(&img_magic);
        endswap(&max_img);
        endswap(&w);
        endswap(&h);
    }

    std::ifstream lblfs(lblfile, std::ios::binary);
    // Reading lbl-header
    lblfs.read(reinterpret_cast<char*>(&lbl_magic), 4);
    lblfs.read(reinterpret_cast<char*>(&max_lbl), 4);
    if (lbl_magic != LBL_MAGIC) {
        endswap(&lbl_magic);
        endswap(&max_lbl);
    }

    // Checking if size is alright
    if (sz > max_img || sz > max_lbl) {
        std::cout << "Given size exceeds the limit!" << std::endl;
        std::cout << "Given size: " << sz << std::endl;
        std::cout << "Max. images: " << max_img << " Max. labels: " << max_lbl << std::endl;
    } else {
        for (int i = 0; i < sz; i++) {
            (*vec).push_back(sample((int)w, (int)h));
            read_img(&imgfs, &(vec->back().image), (int)w, (int)h);
            read_lbl(&lblfs, &(vec->back().label));
        }
    }

    imgfs.close();
    lblfs.close();
}

template <class T>
void endswap(T* ptr) {
    unsigned char* mem = reinterpret_cast<unsigned char*>(ptr);
    std::reverse(mem, mem + sizeof(T));
}

template <class T>
void ascii_art(std::vector<T>* vec, int width) {
    int i = 0;
    for (T elem : *vec) {
        if (i % width == 0) {
            std::cout << "\n";
        }
        
        if (elem >= 0 && elem <= 15) {
            std::cout << ".";
        } else if (elem >= 16 && elem <= 31) {
            std::cout << ":";
        } else if (elem >= 32 && elem <= 63) {
            std::cout << "[";
        } else if (elem >= 64 && elem <= 127) {
            std::cout << "T";
        } else if (elem >= 128 && elem <= 191) {
            std::cout << "V";
        } else if (elem >= 192 && elem <= 255) {
            std::cout << "@";
        }

        i++;
    }
}

