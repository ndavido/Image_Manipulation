//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
#include <valarray>

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
    ifstream ifs(filename);
    if(ifs.good()){
        ifs >> w;
        ifs >> h;
        for(int i = 0; i < w*h; i++){
            float r, g, b;
            ifs >> r >> g >> b;
            pixels[i].r =  pow(r, 1/2.2) * 255;
            pixels[i].g =  pow(g, 1/2.2) * 255;
            pixels[i].b =  pow(b, 1/2.2) * 255;
        }
        ifs.close();
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
        ofs.open(filename, std::ios::binary);
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3];
        // loop over each pixel in the image, convert to byte format
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
        //eliminate green and blue pixels
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for(int i = 0; i < w*h; i++)
    {
        //eliminate red and blue pixels
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for(int i = 0; i < w*h; i++)
    {
        //eliminate red and green pixels
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}

void Image::greyScale()
{
    for (int i = 0; i < w*h; i++)
    {
        //adding all the pixels together and dividing by three to average out the rgb
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

    //loop through the image
    for(int x = 0; x < w/2; x++){
        for(int y = 0; y < h; y++){
            //position of current pixel
            pixel1 = x + y * w;
            //position of the pixel from the other side of the image
            pixel2 = (w - 1 - x) + y * w;

            //swap the original pixel with the new pixel
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

    //loop through the image
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h/2; y++){
            //position of current pixel
            pixel1 = x + y * w;
            //position of the pixel from the other side of the image
            pixel2 = x + (h - 1 - y) * w;

            //swap the original pixel with the new pixel
            swap(pixels[pixel1].r, pixels[pixel2].r);
            swap(pixels[pixel1].g, pixels[pixel2].g);
            swap(pixels[pixel1].b, pixels[pixel2].b);
        }
    }
}

void Image::AdditionalFunction1()
{
    //looping through the image
    for (int i = 0; i < w * h; i++) {
        //swapping pixels in an anticlockwise manner
        swap(pixels[i].r, pixels[i].b);
        swap(pixels[i].g, pixels[i].r);
    }
}
void Image::AdditionalFunction2()
{
    //looping through the image
    for (int i = 0; i < w*h; i++)
    {
        //setting pixels white
        if(this->pixels[i].r>(255/2)){
            this->pixels[i] = 255;
        }
        //setting pixels black
        else{
            this->pixels[i] = 0;
        }
    }
}
void Image::AdditionalFunction3()
{
    //looping through the image
    for (int i = 0; i < w*h; i++)
    {
        //inverting the colour of the image
        this->pixels[i].r = 255 - this->pixels[i].r;
        this->pixels[i].g = 255 - this->pixels[i].g;
        this->pixels[i].b = 255 - this->pixels[i].b;
    }
}



void Image::scaling(int width, int height)
{
    int newW = width;
    int newH = height;
    Rgb *temp = new Rgb[newW *newH];
    //getting the correct aspect ratio
    double ratioX = (double) w / newW;
    double ratioY = (double) h / newH;
    double cy = 0;
    //looping through the image
    for (int y = 0; y < newH; y++) {
        double cx = 0;
        for (int x = 0; x < newW; x++) {
            //current pixels
            int nextX = cx;
            int nextY = cy;
            //points to current pixel and changes to new one
            temp[x + y * newW] = pixels[nextX + nextY * w];
            cx += ratioX; //current
        }
        cy += ratioY;
    }
    //applies changes
    pixels = temp;
    w = newW;
    h = newH;
    temp = nullptr;
    delete[] temp;
}

void Image::setMask(string s)
{
    this->mask = s;
}

void Image::AdvancedFeature()
{
   Image i;
   i.load(mask);
   //applying scaling to Image i
   i.scaling(w,h);
   //loop through the image
   for(int y = 0; y < h; y++)
   {
       for(int x = 0; x < w; x++)
       {
           //current pixel
           int pixel_x = y*w+x;
           if(x < i.w && y < i.h)
           {
               //masks pixel
               int mask_x = y*i.w+x;
               //anything lower than 20 in the masks image becomes black, other transparent
               if (i.pixels[mask_x].r < 20 && i.pixels[mask_x].g < 20 && i.pixels[mask_x].b < 20)
               {
                   pixels[pixel_x].r = 0;
                   pixels[pixel_x].g = 0;
                   pixels[pixel_x].b = 0;
               }
           }
           else
           {
               pixels[pixel_x].r = 0;
               pixels[pixel_x].g = 0;
               pixels[pixel_x].b = 0;
           }
       }
   }
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