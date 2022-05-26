//
// Created by MRV on 5/26/2022.
//
#ifndef YMPTHREADSASYNC_TIMER_H
#define YMPTHREADSASYNC_TIMER_H
#include <vector>
class Timer{
protected:
    time_t start;
    std::vector<time_t> points;
public:
    Timer(){
        start = time(0);
    }
    void mark(){
        points.push_back(time(0) - start);
    }
    void reset(){
        start = time(0);
        points.clear();
    }
    const std::vector<time_t> &get_points() const {
        return points;
    }
};
#endif //YMPTHREADSASYNC_TIMER_H
