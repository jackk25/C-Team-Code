#include "vex.h"

#include "replay.h"
#include <iostream>

void writeReplay(std::vector<std::vector<int>> velocityData, std::string fileName);
void readReplay(std::string fileName);
void controlMotors(std::vector<std::vector<int>> csvData);

/**
 * @brief Saves the data from the controller to a CSV file on the SD card
 *
 * @param velocityData The data from the controller
 * @param fileName The name of the file to save the data to (MUST INCLUDE .csv)
 */
void writeReplay(std::vector<std::vector<int>> velocityData,
               std::string fileName) {

  std::ofstream ofs("/usd/" + fileName, std::ofstream::out);

  // Save the data to the SD card
  for (std::vector<int> row : velocityData) {
    int dataNum = 0;
    for (int col : row) {
      dataNum++;
      ofs << col;
      if (dataNum !=
          row.size()) { // Adds comma if we are not at the end of the row
        ofs << ',';
      }
    }
    ofs << '\n';
  }
  ofs.close();
}

int stoi(const char *s)
{
    long i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}

/**
 * @brief Starts the recorded replay
 */
void readReplay(std::string fileName) {
  std::string rowString, colString;
  std::vector<std::vector<int>> csvData;

  std::ifstream inputCSV("/usd/" + fileName, std::ifstream::in);

  // Split by newline
  while (getline(inputCSV, rowString)) {
    // Put our split data in a stream
    std::stringstream lineStream(rowString);
    std::vector<int> rowData;
    // Split by comma
    while (getline(lineStream, colString, ',')) {
      char inputChar = colString.at(0);
      int colInt = stoi(&inputChar);
      rowData.push_back(colInt);
    }
    csvData.push_back(rowData);
  }
  controlMotors(csvData);
}

/**
 * @brief Reads data from a vector to Vex motors
 *
 * @param csvData Vector of vectors of ints. The first vector is the
 * header, which contains the motor ports. The second vector is the first
 * entry in the replay, and so on.
 */
void controlMotors(std::vector<std::vector<int>> csvData) {
  std::vector<int> header = csvData[0];
  csvData.erase(csvData.begin());
  for (int i : header) {
    std::cout << i << std::endl;
  }
  for (std::vector<int> row : csvData) {
    for (int i = 0; i < row.size(); i++) {
      int motorNum = header[i];
      int motorVelocity = row[i];
      motor(motorNum).setVelocity(motorVelocity, rpm);
    }
    // Clear our vector to make space for the next 4 values
    vex::wait(20, msec);
  }
}