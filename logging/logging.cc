#include <logging.h>
#include <string>

/*
 * (rotate) Description: 
    Search through the folder called logs and iterate through each .json file removing old entries. if folder logs does not exists then create it
 * 
 * 
*/
void logging::rotate() {

}

/*
 * (update) Description:
    Update the object logs by adding new entries aka other crashes that occured somewhere 
*/
void logging::update() {



}

/*
 * (write) Description:
    Write the object logs data to a .json file 
*/
bool logging::write() {


    return false;
}

auto logging::getCurrentTimeString() -> std::string {
    // Get current time as time_point
    auto now = std::chrono::system_clock::now();

    // Convert time_point to time_t to get a C-style time
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to tm structure for local time
    std::tm* now_tm = std::localtime(&now_c);

    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

    // Return the formatted time as a string
    return oss.str();
}
