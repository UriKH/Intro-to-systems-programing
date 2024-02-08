#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#ifdef _WIN32
#define WIN true
#endif

#ifdef defined(__unix__) || defined(__ANDROID__) || defined(TARGET_OS_MAC)
#define WIN false
#endif

int main(int argc, char* argv[]){
    if (!system(NULL)){
        throw std::runtime_error("could not interact with system");
    }

    std::vector<std::string> commands;
    for (size_t i = 1; i < argc - 1; i++)
        commands.push_back(std::string(commands[i]));

    // analyz arguments -   [--help]
    //                      [--run-tests] : [folder of tests, output folder(optional), errors(optional)]
    //                      [--single] : [single_test_path, output (optional), errors(optional)]                     
    //                      [--diff] : [inputfolder, outputfolder, output_to (optional)]
    //                      [--diff --single] : [test_out, test_res]
}

bool run_tests(){
}