#include <iostream>
#include <fstream>
#include "fileProcessor.h"

using namespace std;

int main()
{
    //enter the path to the file
    char* filename = "example.txt";

    modifyFile(filename,0,"Hello");
    readFile(filename);
    return 0;
}
