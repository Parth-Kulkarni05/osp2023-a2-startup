#include "loader.h"
#include <sstream>

std::queue<pcb> Loader::load_data(const std::string& filename) {

    // Here we initalised the queue, read the file accordingly and return the queue

    std::queue<pcb> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return processes;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        osp2023::id_type pid;
        osp2023::time_type t_time;

        if (ss >> pid && ss.get() && ss >> t_time) {  // Read an integer, then a comma, then another integer
            processes.push(pcb(pid, t_time));
        }
    }

    file.close();
    return processes;
}
