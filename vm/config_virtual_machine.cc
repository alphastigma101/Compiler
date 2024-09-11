#include "virtual_machine.h"
using VirtualMachine;

// container that launches a custom terminal that includes pids
// includes systemcalls 

container::container(const *char language) {
    // use the getter function to get the table 
    auto table = getTable(); // inherited from compiler which compiler inherited from ast
    // create the directories:
    // /usr/bin/<language>
    // restrict the container and it's premissions heavily, such that it can only execute the linked variables of the program language
    try {
         for (;;) {
             std::cout << "(" + language + ")" + " ";
             std::string line;
             std::getline(std::cin, line); // get user input
             if (line[0] == '\0' || line.empty()) break;
             //run(line);
         }
    }
    catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " "[" << e.code() << "] meaning " "[" << e.what() << "]\n";
    }
}



void VirtualMachine::run(const *char languageName) {
    // Before calling in this method, there should be additional code to check and see if there is only one file extension, exit if there are more than one supported file extension
    // use the unorded map that has haerdcoded links odf downloads for each languageName
    // Download it, and then verify the hash of it.
    //std::filesystem::path = put the path here
    // Call in container
    container(languageName, folder_path);

}



