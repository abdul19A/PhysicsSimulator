#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class DataLogger
{
public:
    DataLogger(std::string name) : dataName(std::move(name)) {}

    void Log(T newData)
    {
        dataPoints.push_back(newData);
    }

    std::vector<T> &getData() const { return dataPoints; }

    bool WriteToFile() const
    {
        const std::string filename = dataName + ".dataLog";
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        file << dataName << ";\n";
        for (size_t i = 0; i < dataPoints.size(); ++i)
        {
            file << dataPoints[i] << ";\n";
        }
        return true;
    }

private:
    std::string dataName;
    std::vector<T> dataPoints;
};
