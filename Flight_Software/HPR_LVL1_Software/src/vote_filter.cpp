#include <vote.hpp>
#include <Arduino.h>
#include <numeric>

// Constructor
VoteFilter::VoteFilter(int windowSize, int stdDevThreshold)
    : windowSize(windowSize), stdDevThreshold(stdDevThreshold) {}

// Median filter: removes spikes by using the median of a window of values
double VoteFilter::applyMedianFilter(std::vector<double>& data) {
    sortData(data);
    int size = data.size();
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;
    } else {
        return data[size / 2];
    }
}

// Moving average: reduces noise by averaging a window of values
double VoteFilter::applyMovingAverage(std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Removes outliers that are more than stdDevThreshold standard deviations from the mean
void VoteFilter::removeOutliers(std::vector<double>& data) {
    double mean = calculateMean(data);
    double stdDev = calculateStandardDeviation(data);

    data.erase(std::remove_if(data.begin(), data.end(),
                [mean, stdDev, this](double val) {
                    return std::abs(val - mean) > this->stdDevThreshold * stdDev;
                }), data.end());
}

// Helper method to calculate the mean of the data
double VoteFilter::calculateMean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Helper method to calculate the standard deviation of the data
double VoteFilter::calculateStandardDeviation(const std::vector<double>& data) {
    double mean = calculateMean(data);
    double variance = 0.0;
    for (double val : data) {
        variance += std::pow(val - mean, 2);
    }
    return std::sqrt(variance / data.size());
}

// Helper method to sort data for median calculation
void VoteFilter::sortData(std::vector<double>& data) {
    std::sort(data.begin(), data.end());
}
