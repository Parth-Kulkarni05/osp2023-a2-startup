#include <iostream>
#include "simulator.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [fifo|sjf|rr] <args...>" << std::endl;
        return 1;
    }

    std::string algorithm = argv[0];

    if (algorithm == "./fifo") {
        if (argc > 2) {
            std::cerr << "Usage: " << argv[0] << " fifo <datafile>" << std::endl;
            return 1;
        }
        std::string datafile = argv[1];
        Simulator simulator (datafile);
        simulator.run_fifo();
    } 

    else if (algorithm == "./sjf"){
        if (argc > 2){
            std::cerr << "Something has gone wrong with your command" << std::endl;
            return 0;
        }

        std::string datafile = argv[1];
        Simulator simulator (datafile);
        simulator.run_sjf();


    }

    else if (algorithm == "./rr") {
        if (argc > 3) {
            std::cerr << "Usage: " << argv[0] << " rr <quantum> <datafile>" << std::endl;
            return 1;
        }
        int quantum = std::stoi(argv[1]);
        std::string datafile = argv[2];
        Simulator simulator (datafile);
        simulator.run_rr(quantum);
    } 

    /*

    else if (algorithm == "sjf") {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " sjf <datafile>" << std::endl;
            return 1;
        }
        std::string datafile = argv[2];
        simulator = Simulator(datafile);
        simulator.run_sjf();
    } 
    else if (algorithm == "rr") {
        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " rr <quantum> <datafile>" << std::endl;
            return 1;
        }
        int quantum = std::stoi(argv[2]);
        std::string datafile = argv[3];
        simulator = Simulator(datafile);
        simulator.run_rr(quantum);
    } 

    */
    else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    return 0;
}
