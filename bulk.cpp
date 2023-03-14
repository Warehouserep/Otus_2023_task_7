#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

std::vector<std::string> commands;
std::time_t first_command;

void print_commands(){
    if(commands.size() > 0){
        std::string filename = "bulk" + std::to_string(first_command) + ".log";
        std::ofstream file_out(filename);
        std::string res;
        res +=  "bulk:";
        for (int i = 0; i < commands.size(); i++){
            res +=  " " + commands[i];
            if(i!=commands.size()-1){
                res += ",";
            }
        }
        res +=  "\n";
        commands.clear();
        std::cout << res;
        file_out << res;
        file_out.close();
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Enter 1 argument" << std::endl;
        return 1;
    }

    int block_size = std::atoi(argv[1]);
    if (block_size <= 0){
        std::cout << "Argument must be more than 0";
        return 0;
    }
    std::string curr_command;
    int cnt_bracket = 0;
    std::cin >> curr_command;
    while (!std::cin.eof()){
        if(curr_command == "{"){
            if(cnt_bracket == 0)
                print_commands();
            cnt_bracket++;
        }
        else if(curr_command == "}"){
            cnt_bracket--;
            if(cnt_bracket == 0){
                print_commands();
            }
            if(cnt_bracket < 0) 
                cnt_bracket = 0; 
        }
        else {
            if(commands.size() == 0){
                first_command = time(nullptr);
            }
            commands.push_back(curr_command);
            if(cnt_bracket == 0 && commands.size() == block_size){
                print_commands();
            }
        }

        std::cin >> curr_command;

    }
    if(cnt_bracket == 0){
        print_commands();
    }
    
    return 0;
}