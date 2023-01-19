#pragma once
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>


struct Configuration{
    private:
        std::vector<std::pair<std::string, double>> config{
            std::make_pair("Measure Period", 0),
            std::make_pair("Delay Valves/Mix", 0),
            std::make_pair("Mixture Period", 0),
            std::make_pair("Ph Valve Period", 0),
            std::make_pair("Ec Valve Period", 0),
            std::make_pair("Ph min", 0),
            std::make_pair("Ph max", 0),
            std::make_pair("Ec min", 0),
            std::make_pair("Ec Max", 0)
        };

    public:
        std::vector<std::pair<std::string, double>> getConfig() { return this->config; }
        void saveConfig(size_t id, double value);
        bool loadFromEEPROM();
        void loadDefault();
};
