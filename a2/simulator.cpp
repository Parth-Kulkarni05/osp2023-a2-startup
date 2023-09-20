#include "simulator.h"
#include <iostream>
#include <algorithm> // for std::min function in RR
#include "fifo.h"

Simulator::Simulator(const std::string& filename) {
    // In the constructor here we load the data from loader..
    ready_queue = Loader::load_data(filename);
}

void Simulator::run_fifo() {

    // This method is used for FIFO

    osp2023::time_type total_turnaround_time = 0;
    osp2023::time_type total_waiting_time = 0;
    
    int num_processes = ready_queue.size();  // Storing the initial number of processes

    osp2023::time_type current_time = 0;

    while(!ready_queue.empty()) {

        // Take the first process from the queue
        pcb& current = ready_queue.front();

        // Calculate waiting time
        current.increment_wait_time(current_time);

        // Process runs to completion (FIFO)
        current_time += current.get_total_burst_time();
        current.increment_time_used(current.get_total_burst_time());

        // Update total waiting time and turnaround time
        total_waiting_time += current.get_total_wait_time();
        total_turnaround_time += current.get_total_wait_time() + current.get_total_burst_time();

        // Display stats for this process
        Simulator::display_process_stats(current);

        ready_queue.pop();

        Simulator::display_average_stats(total_turnaround_time, total_waiting_time, num_processes);
    }


}


void Simulator::run_sjf() {
    // This method is used to run SJF

    osp2023::time_type current_time = 0;
    osp2023::time_type total_turnaround_time = 0;
    osp2023::time_type total_waiting_time = 0;
    
    int num_processes = ready_queue.size();  // Storing the initial number of processes

    // We need to sort the queue.. so to acheive this will convert it into a vector then back into a queue

    std::vector<pcb> vector_processes;
    while(!ready_queue.empty()){
        vector_processes.push_back(ready_queue.front());
        ready_queue.pop();
    }

    // We will now sort the vector...
    std::sort(vector_processes.begin(), vector_processes.end(), [](const pcb& a, const pcb& b) {
        return a.get_total_burst_time() < b.get_total_burst_time();
    });

    // We will now convert back into a queue and use the same algorithm as FIFO
    std::queue<pcb> ready_queue_sorted;
    for(const auto& process : vector_processes) {
        ready_queue_sorted.push(process);
    }

    while(!ready_queue_sorted.empty()) {

        // Take the first process from the queue
        pcb& current = ready_queue_sorted.front();

        // Calculate waiting time
        current.increment_wait_time(current_time);

        // Process runs to completion (FIFO)
        current_time += current.get_total_burst_time();
        current.increment_time_used(current.get_total_burst_time());

        // Update total waiting time and turnaround time
        total_waiting_time += current.get_total_wait_time();
        total_turnaround_time += current.get_total_wait_time() + current.get_total_burst_time();

        // Display stats for this process
        Simulator::display_process_stats(current);

        ready_queue_sorted.pop();

        Simulator::display_average_stats(total_turnaround_time, total_waiting_time, num_processes);
    }

}

void Simulator::run_rr(osp2023::time_type quantum) {

    // This method is used to run the rr

    osp2023::time_type total_time = 0;
    osp2023::time_type total_turnaround_time = 0;
    osp2023::time_type total_waiting_time = 0;
    
    int num_processes = ready_queue.size();
    
    // We will use this vector to keep track of the response times
    std::vector<osp2023::time_type> response_times(num_processes, -1);  // Initialised with -1
    
    while(!ready_queue.empty()) {

        // Gets item in front of queue and the time left in process
        pcb& current = ready_queue.front();
        osp2023::time_type time_left = current.get_total_burst_time() - current.get_consumed_used();

        // If this process has not been scheduled before we can set its response time
        // Since the process id are sequential numbers, can just use them as indexes..
        if (response_times[current.get_process_id() - 1] == -1) {
            response_times[current.get_process_id() - 1] = total_time;
        }


        // If the time left for this process is less than or equal to the quantum, 
        // it means this process can still complete in the current time slice

        if(time_left <= quantum) {
            total_time += time_left;
            current.increment_time_used(time_left);
            
            total_waiting_time += total_time - current.get_total_burst_time();
            total_turnaround_time += total_time;
            
            display_process_stats(current);
            
            ready_queue.pop();
        } 
        
        // The process needs for time slices to be completed, we will update the time used and move it to the end of 
        // the queue. Its then popped because we already moved it to the end of the queue.
        else {

            total_time += quantum;
            current.increment_time_used(quantum);
            

            ready_queue.push(current);
            ready_queue.pop();
        }
    }

    Simulator::display_average_stats_rr(response_times, total_turnaround_time, total_waiting_time, num_processes);
}

void Simulator::display_process_stats(const pcb& process){

    // Contains the "stats" of each process that is called in the method above...
    std::cout << "Process ID: " << process.get_process_id()
              << ", Burst time: " << process.get_total_burst_time()
              << ", Turnaround time: " << process.get_total_wait_time() + process.get_total_burst_time()
              << ", Waiting time: " << process.get_total_wait_time()
              << ", Response time: " << process.get_total_wait_time() // Since arrival time is 0 for all
              << std::endl;
}


void Simulator::display_average_stats(osp2023::time_type total_turnaround_time, osp2023::time_type total_waiting_time, int num_processes) {
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / num_processes;
    double avg_waiting_time = static_cast<double>(total_waiting_time) / num_processes;
    double avg_response_time = avg_waiting_time;  // Since arrival time is 0 for all

    std::cout << "Average Turnaround Time: " << avg_turnaround_time << " ms" << std::endl;
    std::cout << "Average Waiting Time: " << avg_waiting_time << " ms" << std::endl;
    std::cout << "Average Response Time: " << avg_response_time << " ms" << std::endl;
}

void Simulator::display_average_stats_rr(const std::vector<osp2023::time_type>& response_times, osp2023::time_type total_turnaround_time, osp2023::time_type total_waiting_time, int num_processes) {
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / num_processes;
    double avg_waiting_time = static_cast<double>(total_waiting_time) / num_processes;
    
    double avg_response_time = 0;
    for (const auto& rt : response_times) {
        avg_response_time += rt;
    }
    avg_response_time /= num_processes;

    std::cout << "Average Turnaround Time: " << avg_turnaround_time << " ms" << std::endl;
    std::cout << "Average Waiting Time: " << avg_waiting_time << " ms" << std::endl;
    std::cout << "Average Response Time: " << avg_response_time << " ms" << std::endl;
}