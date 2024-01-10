#pragma once
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

// TODO: should probably be a class
namespace shmn::utils::stats {
    inline std::string get_stats(float delta, float running) {
        std::stringstream ss;
        ss << "Delta Time: " << delta << " Time Running: " << running << std::setprecision(5) << std::fixed;
        return ss.str();
    }
}
