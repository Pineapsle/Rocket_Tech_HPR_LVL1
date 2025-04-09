#ifndef VOTE_FILTER_HPP
#define VOTE_FILTER_HPP

#include <Arduino.h>
#include <vector>
#include <algorithm>
#include <cmath>

class VoteFilter {
public:
    VoteFilter(int windowSize, int stdDevThreshold);

    // Median filter method
    double applyMedianFilter(std::vector<double>& data);

    // Moving average filter method
    double applyMovingAverage(std::vector<double>& data);

    // Method to remove outliers
    void removeOutliers(std::vector<double>& data);

private:
    int windowSize;
    int stdDevThreshold;

    // Helper methods
    double calculateMean(const std::vector<double>& data);
    double calculateStandardDeviation(const std::vector<double>& data);
    void sortData(std::vector<double>& data);
};

#endif // VOTE_FILTER_HPP
