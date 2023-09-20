#include <iostream>
#include "types.h"

#pragma once  // tells the compiler to only include this file once
              /**
 * the process control block - represents a process that needs to be executed in
 * our simulator. Please note the I used some custom types of osp2023::time_type
 * and osp2023::id_type. these are just aliases to long integers but they are
 * more meaningful type names, hinting at how they will be used. Please see
 * their definitions in types.h.
 **/
class pcb {
    // the unique process id
    osp2023::id_type id;
    // the total time that a process / job should run for
    osp2023::time_type total_time;
    // the time that has been used so far for this process
    osp2023::time_type time_used;
    // the priority level for this process
    // how much time has this process spent waiting for the cpu?
    osp2023::time_type total_wait_time;
    // what time was this process last on the cpu?

   public:
    // max and min duration for a process in our system.
    static constexpr osp2023::time_type MAX_DURATION = 100;
    static constexpr osp2023::time_type MIN_DURATION = 10;

    // Create the constrructor here.. 

    pcb(osp2023::id_type pid, osp2023::time_type t_time) 
    : id(pid), total_time(t_time), time_used(0), total_wait_time(0) {}

    // Create the getters and setters

    osp2023::id_type get_process_id() const {
        return id;
    }

    osp2023::time_type get_total_burst_time() const {
        return total_time;
    }

    osp2023::time_type get_consumed_used() const {
        return time_used;
    }

    void increment_time_used(osp2023::time_type increment) {
        time_used += increment;
    }

    osp2023::time_type get_total_wait_time() const {
        return total_wait_time;
    }

    void increment_wait_time(osp2023::time_type increment) {
        total_wait_time += increment;
    }

};
