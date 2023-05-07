// The source file for this program should be named split.c and be located in the Applications directory. The program takes as arguments the path to a valid TGA image file and the path to an out- put directory. It outputs in the output directory the three image files obtained by separating the red, green, and blue channels of the input image. If the name of the input image was myImage.tga,
//  then the output images should be named myImage [r].tga, myImage [g].tga, and
// myImage [b].tga.

#include "./include/split.h"

int main(int argc, char** argv) {

    Parsed parsed = parseArgs(argc, argv);

    RasterImage image1 = readTGA(parsed.imgPath);
    RasterImage image2 = readTGA(parsed.imgPath);
    RasterImage image3 = readTGA(parsed.imgPath);

    RasterImage imageR = getRFromImage(image1);
    RasterImage imageB = getBFromImage(image2);
    RasterImage imageG = getGFromImage(image3);

    char* imgName = getFileName(parsed.imgPath);

    char* imgRpath = (char*) calloc(strlen(parsed.dirPath) + strlen(imgName) + 6, 1);
    char* imgBpath = (char*) calloc(strlen(parsed.dirPath) + strlen(imgName) + 6, 1);
    char* imgGpath = (char*) calloc(strlen(parsed.dirPath) + strlen(imgName) + 6, 1);

    sprintf( imgRpath, "%s%s [r].tga", parsed.dirPath, imgName );
    sprintf( imgBpath, "%s%s [b].tga", parsed.dirPath, imgName );
    sprintf( imgGpath, "%s%s [g].tga", parsed.dirPath, imgName );

    writeTGA(imgBpath, &imageB);
    writeTGA(imgRpath, &imageR);
    writeTGA(imgGpath, &imageG);

    free(imageR.raster);
    free(imageB.raster);
    free(imageG.raster);

    return(0);
}
