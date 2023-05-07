
// This header contains functions and structures used by our crop program

#include "./applications.h"
#include "../../ImageLibrary/include/rasterImage.h"

/**	struct to parse command line argument paths 
 *	@param	tgaPath  string path to the tga file
 *	@param	dirPath  string path to the output directory 
 */
typedef struct {
    char* tgaPath;
    char* dirPath;
} Parsed;

/**	struct to of a crop rectangle **********************
 *	@param	x  x of the upper left crop rectangle corner
 *	@param	y  y of the upper left crop rectangle corner
 *	@param	width   width of the crop rectangle
 *	@param	height  height of the crop rectangle
 */
typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
} Crop;

// this function creates a crop structure using the coordinates x, y, the width and the height of the crop
Crop newCrop(int x,  int y, int width, int height);

// this function returns true if an a crop is in a raster image range and false  if it is not
bool isInBound(RasterImage* image, Crop* crop);

// this function parse the program arguments withing our Parsed structure
Parsed parseArgs (int argc, char** argv);

// checks whether arg is an unsigned integer or not, returns true or false respectively
bool argIsValid(char *arg);

Crop newCrop(int x,  int y, int width, int height) {
    Crop crop;
    crop.x = (unsigned int) x;
    crop.y = (unsigned int) y;
    crop.width = (unsigned int) width;
    crop.height = (unsigned int) height;
    return crop;
}

bool isInBound(RasterImage* image, Crop* crop) {
    unsigned int highestCropX = crop->x + crop->width;
    unsigned int highestCropY = crop->y + crop->height;
    
    if (image->width >= highestCropX && image->height >= highestCropY) { return true; } else { return false; }
}

Parsed parseArgs (int argc, char** argv) {
    if (argc != 7) {
        printf("Incorrect number of arguments");
        exit(BAD_NUM_ARGS);
    }
    
    char* tgaPath = argv[1]; char* dirPath = argv[2];

    if(!isaTGAfile(tgaPath)) {
        printf("The argument is not a tga file: %s", tgaPath);
        exit(BAD_FILE_TYPE);
    }
    if (!tgaPathIsValid(tgaPath)) {
        printf("File not found: %s", tgaPath);
        exit(UNKNOWN_ARGUM);
    }
    if (!dirIsValid(dirPath)) {
        printf("The second argument for the output directory is invalid");
        exit(UNKNOWN_ARGUM);
    }
    Parsed parsed = { tgaPath, dirPath };

    for(int i = 3; i < 7; i++) {
        if (!argIsValid(argv[i])) {
            printf("The arguments defning the cropping rectangle must be positive integers.");
            exit(UNKNOWN_ARGUM);
        }
    }
    return parsed;
}   

bool argIsValid(char *arg) {
    for (int i = 0; i < strlen(arg); i++){
        if(!isdigit(arg[i])){
            return false;
        }
    }
    float argf = atof(arg); unsigned int argi = argf;
    if (argi != argf) { return false; }
    else { return true; }
}