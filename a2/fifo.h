// Header file for the fifo.h
#include <iostream>
#include "simulator.h"

#pragma once

class fifo{
public:
    static void run_fifo(std::queue<pcb>& readyQueue, osp2023::time_type& total_turnaround_time, osp2023::time_type& total_waiting_time);
    static inline void display_process_stats(const pcb& process);

};
