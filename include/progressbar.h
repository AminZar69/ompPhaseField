#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <functional>

class ProgressBar {
public:
    // Alias for the output callback function appearing as a private field
    using OutputFn = std::function<void(const std::string&)>;

    // Default constructor. No output display
    ProgressBar();

    // Constructor with output delegate.
    explicit ProgressBar(OutputFn outputFn);

    ~ProgressBar();

    void start(int total_iterations);
    void update(int current);

    // Print a line above the bar without disrupting it
    void print_line(const std::string& msg);

    void stop();

    // Allow the caller to change the output delegate at any time
    void set_output(OutputFn outputFn);

private:
    static constexpr int BAR_WIDTH = 30;

    void run();
    void write(const std::string& s);   // routes to output_fn under mutex
    static std::string format_time(double seconds);

    std::atomic<bool> running;
    std::atomic<int>  progress;
    std::atomic<int>  total;
    std::thread       thread;
    std::chrono::steady_clock::time_point start_time;
    std::mutex        output_mutex;
    OutputFn          output_fn;
};

#endif