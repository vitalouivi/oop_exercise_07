#ifndef LOADER_H
#define LOADER_H


#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "windows.h"
#include <conio.h>
#include <stack>
#include "figure.h"

struct loader {

    std::vector<std::unique_ptr<figure>> load(std::ifstream& is);
       
    ~loader();
};
#endif