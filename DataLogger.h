#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "AdditionalVectorMethods.h"

template <typename T>
class DataLogger {
public:
    explicit DataLogger(std::string name) : dataName(std::move(name)), timeElapsed(0.0f) {}

    void Log(T newData, float dt) {
        dataPoints.push_back(newData);
        timePoints.push_back(timeElapsed);
        timeElapsed += dt;
    }

    std::vector<T> getData() const { return dataPoints; }
    std::vector<float> getTimePoints() const { return timePoints; }

    bool WriteToFile() const {
        const std::string filename = dataName + ".dataLog";
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        file << "time," << dataName << "\n";
        for (size_t i = 0; i < dataPoints.size(); ++i) {
            file << timePoints[i] << "," << dataPoints[i] << "\n";
        }
        return true;
    }

private:
    std::string dataName;
    std::vector<T>     dataPoints;
    std::vector<float> timePoints;
    float timeElapsed;
};