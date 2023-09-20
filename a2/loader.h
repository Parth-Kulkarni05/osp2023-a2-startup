#include <fstream>
#include <queue>
#include "pcb.h"

#pragma once

class Loader {
public:
    static std::queue<pcb> load_data(const std::string& filename);
};