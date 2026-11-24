#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

std::string pad_utf8(const std::string& str, size_t width, bool align_left = true) {
    size_t char_count = 0;
    size_t byte_pos = 0;

    while (byte_pos < str.size() && char_count < width) {
        unsigned char c = static_cast<unsigned char>(str[byte_pos]);
        size_t char_len = 1;

        if ((c & 0x80) == 0) char_len = 1;           // ASCII (1 байт)
        else if ((c & 0xE0) == 0xC0) char_len = 2; // Кириллица и др. (2 байта)
        else if ((c & 0xF0) == 0xE0) char_len = 3; // 3 байта
        else if ((c & 0xF8) == 0xF0) char_len = 4; // Эмодзи и др. (4 байта)

        if (byte_pos + char_len > str.size()) break;

        byte_pos += char_len;
        char_count++;
    }

    std::string trimmed = str.substr(0, byte_pos);
    std::string spaces(width - char_count, ' ');

    return align_left ? (trimmed + spaces) : (spaces + trimmed);
}
struct universityApplicants
{
  string Fio;
  int pointsMath;
  int pointsRussin;
  int pointsInformatic;
  double meanValue;
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
  string lineFile;
  vector<string> fields;
  universityApplicants user;
  vector<universityApplicants> userStudent;
  double meanValueMath = 0.0, meanValueRussion = 0.0, meanValueInfarmatic = 0.0;
  double maxBallUser = 0.0, minBallUser = 100.0;
  
  ifstream file("priem.txt");

  if (!file.is_open()) {
    cout << "INVALID: file not found";
    return 1;
  }

  getline(file, lineFile);

  while (getline(file, lineFile)) {
    fields = splitFields(lineFile);

    if (fields.size() != 4) {
      continue;
    }

    user.Fio = fields[0];

    if (!readInt(fields[1], user.pointsMath)) {
      continue;
    }
    if (!readInt(fields[2], user.pointsRussin)) {
      continue;
    }
    if (!readInt(fields[3], user.pointsInformatic)) {
      continue;
    }

    userStudent.push_back(user);
  }

  for(auto& element: userStudent) {
    element.meanValue = (element.pointsInformatic + element.pointsMath + element.pointsRussin) / 3.0;

    if (element.meanValue > maxBallUser) {
      maxBallUser = element.meanValue;
    } else if(element.meanValue < minBallUser) {
      minBallUser = element.meanValue;
    }
  }

  double countElementVector = userStudent.size();

  for(auto& element: userStudent) {
    meanValueMath += element.pointsMath;
  }

  for(auto& element: userStudent) {
    meanValueInfarmatic += element.pointsInformatic;
  }

  for(auto& element: userStudent) {
    meanValueRussion += element.pointsRussin;
  }

  meanValueMath /= countElementVector;
  meanValueInfarmatic /= countElementVector;
  meanValueRussion /= countElementVector;

  cout << "MAX bal\n";

  for(auto& element: userStudent) {
    if(element.meanValue == maxBallUser) {
      printf("%s %i %i %i SR:%.2f\n", pad_utf8(element.Fio, 20, true).c_str(), element.pointsMath, element.pointsRussin, element.pointsInformatic, element.meanValue);
    }
  }

  cout << "\nMIN bal\n";

  for(auto& element: userStudent) {
    if(element.meanValue == minBallUser) {
      printf("%s %i %i %i SR:%.2f\n",pad_utf8(element.Fio, 20, true).c_str(), element.pointsMath, element.pointsRussin, element.pointsInformatic, element.meanValue);
    }
  }

  FILE* outFile = std::fopen("result.txt", "w");

  if (outFile == nullptr) {
    return 1;
  }
  
  fprintf(outFile,"%s %8s %8s %8s\n", pad_utf8("ФИО", 20, true).c_str(), pad_utf8("Математика", 8, true).c_str(), pad_utf8("Русский", 8, true).c_str(), pad_utf8("Информатика", 8, true).c_str());


  for(auto& element: userStudent) {
    fprintf(outFile,"%s %5i    %5i    %5i    SR:%.2f\n",pad_utf8(element.Fio, 20, true).c_str(), element.pointsMath, element.pointsRussin, element.pointsInformatic, element.meanValue);
  }

  fprintf(outFile,"%20s SR:%-5.2f SR:%-5.2f SR:%-5.2f ",  " ", meanValueMath, meanValueRussion, meanValueInfarmatic);

}