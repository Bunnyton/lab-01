// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>
#include "print.hpp"

using json = nlohmann::json;

int main() {
  std::string jsonPath;
  std::cin >> jsonPath;
  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"unable to open json: " + jsonPath};
  }

  json data;
  file >> data;

  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    Student student;
    from_json(item, student);  // = item.get<Student>();
    students.push_back(student);
  }

  print(students, std::cout);
  return 0;
}
