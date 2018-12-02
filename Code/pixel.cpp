#include "ws2812-rpi.h"
#include "CSVparser.hpp"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void findMaxMin(float data[][], float& min, float& max){

    for (int i = 0; i < maxRow; i++){
        for (int j = 0; j < maxCol; j++){
            if (data[i][j] < min){
                min = data[i][j];
            }
            if (data[i][j] > max){
                max = data[i][j];
            }
        }
    }
}

int main(int argc, char **argv){
    //create object for each strip
    NeoPixel bin1 = NeoPixel(9);
    NeoPixel bin2 = NeoPixel(9);
    NeoPixel bin3 = NeoPixel(9);
    NeoPixel bin4 = NeoPixel(9);
    NeoPixel bin5 = NeoPixel(9);
    NeoPixel bin6 = NeoPixel(9);
    NeoPixel bin7 = NeoPixel(9);
    NeoPixel bin8 = NeoPixel(9);
    NeoPixel bin9 = NeoPixel(9);
    NeoPixel bin10 = NeoPixel(9);
    NeoPixel bin11 = NeoPixel(9);
    NeoPixel bin12 = NeoPixel(9);
    NeoPixel bin13 = NeoPixel(9);
    NeoPixel bin14 = NeoPixel(9);
    NeoPixel bin15 = NeoPixel(9);
    NeoPixel bin16 = NeoPixel(9);

    //transfer values from csv file to 2d array
    string file = "fft.csv";
    csv::Parser song = csv::Parser(file);
    int maxRow = song.rowCount();
    int maxCol = song.columnCount();
    float data[maxRow][maxCol];
    for(int i = 0; i < maxRow; i++) {
        for(int j = 0; j < maxCol; j++) {
            data[i][j] = fabs(stof(song[i][j]));
        }
    }

    //find max and min value in 2d array
    float min = 0;
    float max = 0;
    findMaxMin(data, min, max);

    //create range for each bin
    float diff = max - min;
    float range = diff/16;
    bin1.rangeMin = min;
    bin1.rangeMax = min + range;
    bin2.rangeMin = min + range + 1;
    bin2.rangeMax = min + (2*range);
    bin3.rangeMin = min + (2*range)+1;
    bin3.rangeMax = min + (3*range);
    bin4.rangeMin = min + (3*range)+1;
    bin4.rangeMax = min + (4*range);
    bin5.rangeMin = min + (4*range) +1;
    bin5.rangeMax = min + (5*range);
    bin6.rangeMin = min + (5*range) + 1;
    bin6.rangeMax = min + (6*range);
    bin7.rangeMin = min + (6*range) + 1;
    bin7.rangeMax = min + (7*range);
    bin8.rangeMin = min + (7*range) + 1;
    bin8.rangeMax = min + (8*range);
    bin9.rangeMin = min + (8*range) + 1;
    bin9.rangeMax = min + (9*range);
    bin10.rangeMin = min + (9*range) + 1;
    bin10.rangeMax = min + (10*range);
    bin11.rangeMin = min + (10*range) + 1;
    bin11.rangeMax = min + (11*range);
    bin12.rangeMin = min + (11*range) + 1;
    bin12.rangeMax = min + (12*range);
    bin13.rangeMin = min + (12*range) + 1;
    bin13.rangeMax = min + (13*range);
    bin14.rangeMin = min + (13*range) + 1;
    bin14.rangeMax = min + (14*range);
    bin15.rangeMin = min + (14*range) + 1;
    bin15.rangeMax = min + (15*range);
    bin16.rangeMin = min + (15*range) + 1;
    bin16.rangeMax = max;

    //change lights based on numerical value
    float value = 0;
    while(true) {
        for(int i = 0; i < maxRow; i++) {
            for(int j = 0; j < maxCol; j++) {
                value = data[i][j];
                if(value >= bin1.rangeMin || value <= bin2.rangeMax) {

                }
            }
        }
    }
    return 0;
}