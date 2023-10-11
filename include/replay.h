#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>

extern void writeReplay(std::vector<std::vector<int>> velocityData, std::string fileName);
extern void readReplay(std::string fileName);
