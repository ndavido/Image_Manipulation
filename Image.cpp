//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"

bool Image::load(string filename)
{
    ifstream ifs(filename, std::ios::binary);
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256, '\n');
    if(p==255)
    {
        delete[] pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for(int i = 0; i < w*h; i++)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
            if(i < 100) {
            }
        }
        return true;
    }
    return false;

}
bool Image::loadRaw(string filename)
{
    ifstream input(filename);
    if(input.good()){
        input >> w;
        input >> h;
        for(int i = 0; i < w*h; i++){
            float r, g, b;
            input >> r >> g >> b;
            pixels[i].r = (unsigned char) (r*255);
            pixels[i].g = (unsigned char) (g*255);
            pixels[i].b = (unsigned char) (b*255);
            cout << r << pixels[i].r << endl;
        }
        input.close();
        return true;
    }
    return false;
}
bool Image::savePPM(string filename)
{
    if (w == 0 ||h == 0) {
        return false;
    }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3];
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < w * h; i++) {
            pix[0] = static_cast<unsigned char>(this->pixels[i].r);
            pix[1] = static_cast<unsigned char>(this->pixels[i].g);
            pix[2] = static_cast<unsigned char>(this->pixels[i].b);
            ofs.write(reinterpret_cast<char *>(pix), 3);
        }
        ofs.close();

    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return true;
}


void Image::filterRed()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}

void Image::greyScale()
{
    for (int i = 0; i < w*h; i++)
    {
        unsigned char greyscaleValue = ((this->pixels[i].r) + (this->pixels[i].g) + (this->pixels[i].b))/3;
        this->pixels[i].r = greyscaleValue;
        this->pixels[i].g = greyscaleValue;
        this->pixels[i].b = greyscaleValue;
    }
}

void Image::flipHorizontal()
{
    unsigned int pixel1;
    unsigned int pixel2;

    for(int x = 0; x < w/2; x++){
        for(int y = 0; y < h; y++){
            pixel1 = x + y * w;
            pixel2 = (w - 1 - x) + y * w;

            swap(pixels[pixel1].r, pixels[pixel2].r);
            swap(pixels[pixel1].g, pixels[pixel2].g);
            swap(pixels[pixel1].b, pixels[pixel2].b);

        }
    }
}
void Image::flipVertically()
{
    unsigned int pixel1;
    unsigned int pixel2;

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h/2; y++){
            pixel1 = x + y * w;
            pixel2 = x + (h - 1 - y) * w;

            swap(pixels[pixel1].r, pixels[pixel2].r);
            swap(pixels[pixel1].g, pixels[pixel2].g);
            swap(pixels[pixel1].b, pixels[pixel2].b);
        }
    }
}

void Image::AdditionalFunction1()
{
    for (int i = 0; i < w * h; i++) {
        swap(pixels[i].r, pixels[i].g);
        swap(pixels[i].b, pixels[i].r);
    }
}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}


/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}