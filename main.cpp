#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct universityApplicants
{
    string Fio;
    int pointsMath;
    int pointsRussin;
    int pointsInformatic;
};


vector<string> splitFields(const string& line) {
  vector<string> fields;
  size_t start = 0;

  while (true) {
    size_t separator = line.find(';', start);

    if (separator == string::npos) {
      fields.push_back(line.substr(start));
      break;
    }

    fields.push_back(line.substr(start, separator - start));
    
    start = separator + 1;
  }

  return fields;
}

bool readInt(const string& text, int& value) {
  istringstream parser(text);
  char extra;

  if (!(parser >> value) || !isfinite(value)) {
    return false;
  }

  return !(parser >> extra);
}

int main () {
  
  ifstream file("priem.txt");

  if (!file.is_open()) {
    cout << "INVALID: file not found";
    return 1;
  }

}