#include "vex.h"
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace vex;

std::list<std::list<int>> controllerInputs;
std::string filename = "C-Team-Replay.csv";

/**
 * 
 * @brief Saves the content of a nested list to an SD Card in CSV format
 * 
 * This function will take a nested list of ints and iterate through them,
 * saving them to an SD Card inside of a VEX V5 Brain in a CSV format for replaying later
 * 
 * @return int - Exit Code
 */
void nestedListToSD()
{
  Controller1.rumble(".--.");
  std::list<std::list<int>>::iterator fullIt;
  std::list<int>::iterator rowIt;
  std::ofstream ofs(filename);

  if(!Brain.SDcard.isInserted())
  {
    Brain.Screen.print("Error Saving: NO SD CARD");
  }

  for(fullIt = controllerInputs.begin(); fullIt != controllerInputs.end(); fullIt++){
    int dataNum = 0;
    for(rowIt = fullIt->begin(); rowIt != fullIt->end(); rowIt++){
      dataNum++;
      ofs << *rowIt;
      if(dataNum != fullIt->size()){    //Adds comma if we are not at the end of the row
        ofs << ',';
      }
    }
    ofs << '\n';
  }
  ofs.close();
}

/**
 * @brief Reads data from a list to Vex motors
 * 
 * @param unorderedCSVData List containing unformatted motor data
 * @param dataSelectionSize How many elements are in a single entry in the replay
 */
void unorderedDataToMotor(std::list<int> unorderedCSVData, int dataSelectionSize)
{
  std::list<int>::iterator it;
  std::vector<int> tempStructStorage;

  //Classic iterating through a list
  for (it = unorderedCSVData.begin(); it != unorderedCSVData.end(); it++)
  {
    //If the counter does not equal our maximum selection size, do this
    if (tempStructStorage.size() != dataSelectionSize)
    {
      //Push the contents of the iterator to our temporary storage
      //Our iterator will have one of 4 values, all of them int
      tempStructStorage.push_back(*it);
    }
    if (tempStructStorage.size() == dataSelectionSize)
    {
      
      //Clear our vector to make space for the next 4 values
      tempStructStorage.clear();
      wait(0.04, seconds);
    }
  }
}

/**
 * @brief Reads data from an SD card in the Vex Brain into a list, then 
 * calls unorderedDataToMotor() with the list
 */
void readSDDataToList()
{
  int tempColumnInt;
  std::string tempLineStorageString, tempColumnString;
  std::list<int> rawCSVList;

  Brain.Screen.newLine();
  Brain.Screen.print("Replaying!");
  Controller1.rumble("_.._");

  std::ifstream inputCSV(filename, std::ifstream::in);

  //Split by newline
  while (getline(inputCSV, tempLineStorageString))
  {
    //Put our split data in a stream
    std::stringstream tempLineStorageStream(tempLineStorageString);
    //Split by comma
    while (getline(tempLineStorageStream, tempColumnString, ','))
    {
      //Put our final data in another stream
      std::stringstream tempColumnStream(tempColumnString);
      //Convert string to int
      tempColumnStream >> tempColumnInt;
      //Push our int to our list to be read into the motors
      rawCSVList.push_back(tempColumnInt);
    }
  }
  unorderedDataToMotor(rawCSVList, 7);
}