#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

class Timer {
public:
  void start() {
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_bRunning = true;
  }

  void stop() {
    m_EndTime = std::chrono::high_resolution_clock::now();
    m_bRunning = false;
  }

  int64_t elapsedMicrosec() const {
    //    std::chrono::time_point<std::chrono::system_clock> endTime;
    /*
        if (m_bRunning) {
          endTime = std::chrono::system_clock::now();
        } else {
          endTime = m_EndTime;
        }
    */
    return std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime -
                                                                 m_StartTime)
        .count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
  bool m_bRunning = false;
};

#endif