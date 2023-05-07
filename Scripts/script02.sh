# take in two arguments: The path to a directory where to find images in the uncompressed TGA file format, and the path to an output directory.

# execute our build script
./Scripts/build.sh

# loop through the tga files inside of the arg directory for images
# call split executable once and rotate executable twice with respectivaly a left and right option modifier
for img in $1/*.tga
do
    echo executing split for $img ;
    ./split $img $2
    echo executing rotate l for $img ;
    ./rotate l $img $2
    echo executing rotate r for $img ;
    ./rotate r $img $2
done
