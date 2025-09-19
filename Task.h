#pragma once

#include <string>
#include <vector>

struct Task
{
    std::string description;
    bool done;

};

void saveTaskToFile(const std::vector<Task>& task, const std::string& fileName);
std::vector<Task> loadTasksFromFile(const std::string& fileName);
