#include <queue>
#include "pcb.h"
#include "loader.h"

#pragma once

class Simulator {
private:
    std::queue<pcb> ready_queue;

public:
    Simulator(const std::string& filename);
    void run_fifo();
    void display_process_stats(const pcb &process);
    void display_average_stats(osp2023::time_type total_turnaround_time, osp2023::time_type total_waiting_time, int num_processes);
    void display_average_stats_rr(const std::vector<osp2023::time_type> &response_times, osp2023::time_type total_turnaround_time, osp2023::time_type total_waiting_time, int num_processes);
    void run_sjf();
    void run_rr(osp2023::time_type quantum);
};
