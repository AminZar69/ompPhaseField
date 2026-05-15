#include <iomanip>
#include <sstream>
#include <cstdio>
#include "../include/progressbar.h"

ProgressBar::ProgressBar()
    : running(false), progress(0), total(0), output_fn(nullptr) {}

ProgressBar::ProgressBar(OutputFn outputFn)
    : running(false), progress(0), total(0), output_fn(std::move(outputFn)) {}

ProgressBar::~ProgressBar() {
    if (running) {
        stop();
    }
}

void ProgressBar::set_output(OutputFn outputFn) {

    // Thread sync to ensure the read in write() and the write in set_output() never overlap
    std::lock_guard<std::mutex> lock(output_mutex);
    output_fn = std::move(outputFn);
}

void ProgressBar::start(int total_iterations) {
    total = total_iterations;
    progress = 0;
    running = true;
    start_time = std::chrono::steady_clock::now();
    // Non-static method which requires the address of object the method is in as well
    thread = std::thread(&ProgressBar::run, this);
}

void ProgressBar::update(int current) {
    progress = current;
}

// If no delegate is set, the message is ignored
void ProgressBar::write(const std::string& s) {

    // Unlocks when gone out of scope. No need for output_mutex.lock() and output_mutex.unlock()
    std::lock_guard<std::mutex> lock(output_mutex);
    if (output_fn) {
        output_fn(s);
    }
}

void ProgressBar::print_line(const std::string& msg) {
    // Clear the current bar line, then print stats with newline.
    std::ostringstream oss;
    oss << "\r" << std::string(120, ' ') << "\r"
        << msg << "\n";
    write(oss.str());
}

void ProgressBar::stop() {
    running = false;
    if (thread.joinable()) {
        thread.join();
    }
    // Clear the bar line on exit.
    std::ostringstream oss;
    oss << "\r" << std::string(120, ' ') << "\r";
    write(oss.str());
}

void ProgressBar::run() {

    while (running) {

        int current = progress.load();
        int tot = total.load();
        double pct = (tot > 0) ? (100.0 * current / tot) : 0.0;

        auto now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start_time).count();
        double remaining = (current > 0) ? elapsed * (tot - current) / current : 0.0;

        int filled = (tot > 0) ? (BAR_WIDTH * current / tot) : 0;
        std::string bar;
        bar.reserve(BAR_WIDTH);
        for (int i = 0; i < BAR_WIDTH; i++) {
            bar += (i < filled ? '#' : '-');
        }

        std::ostringstream oss;
        oss << "\r ["
            << bar << "] "
            << std::fixed << std::setprecision(1) << pct << "%  "
            << "t=" << current << "/" << tot << "  "
            << "elapsed=" << format_time(elapsed) << "  "
            << "remaining=" << format_time(remaining) << "  "
            << "  ";

        write(oss.str());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::string ProgressBar::format_time(double seconds) {
    // Removing the decimal
    int total_sec = static_cast<int>(seconds);
    int hours = total_sec / 3600;
    int mins  = (total_sec % 3600) / 60;
    int secs  = total_sec % 60;

    char buf[32];
    if (hours > 0) {
        snprintf(buf, sizeof(buf), "%dh%02dm%02ds", hours, mins, secs);
    } else if (mins > 0) {
        snprintf(buf, sizeof(buf), "%dm%02ds", mins, secs);
    } else {
        snprintf(buf, sizeof(buf), "%ds", secs);
    }
    return std::string(buf);
}