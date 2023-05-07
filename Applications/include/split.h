#include "./applications.h"

/**	struct to parse command line argument paths
 *	@param  imgPath  string path to the tga file
 *	@param	dirPath  string path to the output directory folder
 */
typedef struct {
    char* imgPath;
    char* dirPath;
}Parsed;

// this function parse the program arguments withing our Parsed structure
Parsed parseArgs(int argc, char** argv);

Parsed parseArgs(int argc, char** argv) {
    if (argc != 3) {
        printf("Incorrect number of argument, enter an input path and an output directory");
        exit(1);
    }
    char* imgPath = argv[1]; char* dirPath = argv[2];
    if (tgaPathIsValid(imgPath) == false) {
        printf("The first argument for the image file path is invalid");
        exit(1);
    }
    if (dirIsValid(dirPath) == false) {
        printf("The second argument for the output directory is invalid");
        exit(1);
    }
    Parsed parsed = { imgPath, dirPath };
    return parsed;
}