#include "ws2812-rpi.h"
#include "CSVparser.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <sys/time.h> //for gettimeofday()

using namespace std;

void findMaxMin(int maxRow, float frequencies[][16], float &min, float &max)
{

    for (int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (frequencies[i][j] < 0)
            {
                frequencies[i][j] *= -1;
            }
            if (frequencies[i][j] < min)
            {
                min = frequencies[i][j];
            }
            if (frequencies[i][j] > max)
            {
                max = frequencies[i][j];
            }
        }
    }
}

/**

char programName(char **argv) //return string of program name without ./
{
    const char *argName = argv[0];
    int i = 0;
    int namelength = 0;
    while (argName[i] != 0)
    {
        namelength++;
        i++;
    }

    char programName[namelength];

    i = 0;

    while (argName[i + 2] != 0)
    {
        programName[i] = argName[i + 2];
        i++;
    }

    return *programName;
}

int config(NeoPixel data[])
{
    FILE *configFile;
    configFile = fopen("/home/pi/settings.txt", "r");

    if (!configFile)
    {
        perror("Config File could not be opened");
        return -1;
    }

    fprintf(configFile, "");
    return 0;
}

void watchDog()
{
    FILE *wDog;
    wDog = fopen("/dev/watchdog", "w");
    fprintf(wDog, "ping");
}

void watchDogOff()
{
    FILE *dogOff;
    dogOff = fopen("/dev/watchdog", "w");
    fprintf(wDog, 'V');
}

void log()
{
    FILE *logFile;
    logFile = fopen("/home/ pi/log.txt", "a");
}

//This function will get the current time using the gettimeofday function
void getTime(char *buffer)
{
    //Create a timeval struct named tv
    struct timeval tv;

    //Create a time_t variable named curtime
    time_t curtime;

    //Get the current time and store it in the tv struct
    gettimeofday(&tv, NULL);

    //Set curtime to be equal to the number of seconds in tv
    curtime = tv.tv_sec;

    //This will set buffer to be equal to a string that in
    //equivalent to the current date, in a month, day, year and
    //the current time in 24 hour notation.
    strftime(buffer, 30, "%m-%d-%Y  %T.", localtime(&curtime));
}

**/

int main(int argc, char **argv)
{
    //create object for each strip
    NeoPixel lights = NeoPixel(144);

    //transfer values from csv file to 2d array
    string file = "fft.csv";
    csv::Parser song = csv::Parser(file);
    int maxRow = song.rowCount();
    int maxCol = song.columnCount();
    float data[maxRow][1024];
    for (int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            data[i][j] = fabs(stof(song[i][j]));
        }
    }

    //data is split into 1024 frequencies, frequencies are split into 16 bins, making each bin 64 vals
    int bins[] = {
        64,
        128,
        192,
        256,
        320,
        384,
        446,
        512,
        576,
        640,
        704,
        768,
        832,
        896,
        960,
        1024};

    float frequencies[maxRow][16];
    //splitting data into the bins
    float value = 0;
    for (int i = 0; i < maxRow; i++)
    {
        for (int p = 0; p < 16; p++)
        {
            frequencies[i][p] = 0;
        }
        for (int j = 0; j < 16; j++)
        {
            value = data[i][j];
            if (j <= bins[0])
            {
                frequencies[i][0] += value;
            }
            else if (j <= bins[1])
            {
                frequencies[i][1] += value;
            }
            else if (j <= bins[2])
            {
                frequencies[i][2] += value;
            }
            else if (j <= bins[3])
            {
                frequencies[i][3] += value;
            }
            else if (j <= bins[4])
            {
                frequencies[i][4] += value;
            }
            else if (j <= bins[5])
            {
                frequencies[i][5] += value;
            }
            else if (j <= bins[6])
            {
                frequencies[i][6] += value;
            }
            else if (j <= bins[7])
            {
                frequencies[i][7] += value;
            }
            else if (j <= bins[8])
            {
                frequencies[i][8] += value;
            }
            else if (j <= bins[9])
            {
                frequencies[i][9] += value;
            }
            else if (j <= bins[10])
            {
                frequencies[i][10] += value;
            }
            else if (j <= bins[11])
            {
                frequencies[i][11] += value;
            }
            else if (j <= bins[12])
            {
                frequencies[i][12] += value;
            }
            else if (j <= bins[13])
            {
                frequencies[i][13] += value;
            }
            else if (j <= bins[14])
            {
                frequencies[i][14] += value;
            }
            else if (j <= bins[15])
            {
                frequencies[i][15] += value;
            }
        }
    }
    //find max and min value in 2d array
    float min = 0;
    float max = 0;
    findMaxMin(maxRow, frequencies, min, max);

    //(9 / log(max))

    int x = 0;
    int y = 0;
    while (x < maxRow)
    {
        while (y < 16)
        {
            int numLeds = log(frequencies[x][y]);
            if (y == 0)
            {
                for (int i = 0; i < numLeds; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds; i < 9; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 1)
            {
                for (int i = 9; i < numLeds + 9; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 9; i < 18; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 2)
            {

                for (int i = 18; i < numLeds + 18; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 18; i < 27; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 3)
            {
                for (int i = 27; i < numLeds + 27; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 27; i < 36; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 4)
            {
                for (int i = 36; i < numLeds + 36; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 36; i < 45; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 5)
            {
                for (int i = 45; i < numLeds + 45; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 45; i < 54; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 6)
            {
                for (int i = 54; i < numLeds + 54; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 54; i < 63; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 7)
            {
                for (int i = 63; i < numLeds + 63; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 63; i < 72; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 8)
            {
                for (int i = 72; i < numLeds + 72; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 72; i < 81; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 9)
            {
                for (int i = 81; i < numLeds + 81; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 81; i < 90; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 10)
            {
                for (int i = 90; i < numLeds + 90; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 90; i < 99; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 11)
            {
                for (int i = 99; i < numLeds + 99; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 99; i < 108; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 12)
            {
                for (int i = 108; i < numLeds + 108; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 108; i < 117; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 13)
            {
                for (int i = 117; i < numLeds + 117; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 117; i < 126; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 14)
            {
                for (int i = 126; i < numLeds + 126; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 126; i < 135; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            else if (y == 15)
            {
                for (int i = 135; i < numLeds + 135; i++)
                {
                    lights.setPixelColor(i, 255, 255, 255);
                }
                for (int i = numLeds + 135; i < 144; i++)
                {
                    lights.setPixelColor(i, 0, 0, 128);
                }
            }
            y++;
        }
        usleep(250000); //.25s delay before change lights
        x++;
    }
    return 0;
}