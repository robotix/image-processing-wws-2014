#Place it in the same folder as your .c/.cpp OpenCV files
#Open Terminal, Browse to the directory, Run command "chmod +x compile.sh"
#After that just use ./compile.sh Filename.c/cpp to compile your OpenCV files

#!/bin/bash
echo "compiling $1"
if [[ $1 == *.c ]]
then
    gcc -ggdb `pkg-config --cflags opencv` -o `basename $1 .c` $1 `pkg-config --libs opencv`;
elif [[ $1 == *.cpp ]]
then
    g++ -ggdb `pkg-config --cflags opencv` -o `basename $1 .cpp` $1 `pkg-config --libs opencv`;
else
    echo "Please compile only .c or .cpp files"
fi
echo "Output file => ${1%.*}"

