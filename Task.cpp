#include "Task.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

void saveTaskToFile(const std::vector<Task>& task, const std::string& fileName)
{
    //output file stream
    std::ofstream ostream(fileName);

    //number of tasks
    ostream << task.size();
    //loop all the task
    for(const Task& task : task){
        std::string description = task.description;
        //replace all the new line with space
        std::replace(description.begin(), description.end(), ' ', '_');
        //write to file
        ostream << '\n'<<description << ' ' <<task.done;
    }
}

std::vector<Task> loadTasksFromFile(const std::string& fileName)
{
    //test file exists
    if(!std::filesystem::exists(fileName)){
        return std::vector<Task>();
    }

    std::vector<Task> tasks;
    std::ifstream isstream(fileName);

    int n;
    isstream >> n;

    for(int i = 0 ; i < n; i++){
        std::string description;
        bool done;
        isstream >> description >> done;
        tasks.push_back(Task{description, done});
    }
    return tasks;
}