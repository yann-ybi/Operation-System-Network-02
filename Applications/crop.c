// The program takes as arguments the path to a valid TGA image file, the path to an output directory, the x and y coordinates of a cropping rectangle within the image, and the width and height of that cropping rectangle. It writes in the output directory a new image file that contains the sub-image defined by the crop rectangle.
// The name of the output image should be that of the input image, with the [crop] suffix. For example, if the input image is named myImage.tga, then the output image should be named myImage [crop].tga.

#include "./include/crop.h"

int main(int argc, char** argv) {
    
    Parsed parsed = parseArgs(argc, argv);

    RasterImage image = readTGA(parsed.tgaPath);

    Crop crop = newCrop(atoi(argv[4]), atoi(argv[3]), atoi(argv[5]), atoi(argv[6]));
    
    if (!isInBound(&image, &crop)) {
        printf("The cropping rectangle extends outside the image");
        exit(UNKNOWN_ARGUM);
    }

    RasterImage result = cropImage(&image, crop.x, crop.y, crop.width, crop.height);

    char* fname = getFileName(parsed.tgaPath);
    char* cropPath = (char*) calloc(strlen(parsed.dirPath) + strlen(fname) + 10, 1);
    sprintf( cropPath, "%s%s [crop].tga", parsed.dirPath, fname );

    int numCopy = 1;
    while (tgaPathIsValid(cropPath)) {
        numCopy++;
        sprintf( cropPath, "%s%s [crop %u].tga", parsed.dirPath, fname, numCopy);
    }
    
    writeTGA(cropPath, &result);
    free(cropPath);

    return 0;
}

