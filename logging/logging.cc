#include <logging.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <filesystem>

/**
 * @brief Rotate the logs by removing old entries from the logs directory.
 * 
 * Description:
 * This method searches through the folder called "logs" and iterates through each .json file,
 * removing old entries based on some criteria (e.g., age). If the "logs" folder does not exist,
 * it creates the folder.
 */
template<class T>
void logging<T>::rotate() {
    std::filesystem::path logDir = "logs";

    // Create logs directory if it doesn't exist
    if (!std::filesystem::exists(logDir)) {
        std::filesystem::create_directory(logDir);
    }

    // Iterate through each file in the logs directory
    for (const auto& entry : std::filesystem::directory_iterator(logDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            // Process the JSON file, for example, by checking the last modification date
            auto lastWriteTime = std::filesystem::last_write_time(entry.path());
            // Convert std::filesystem::file_time_type to std::chrono::system_clock::time_point
            auto ftime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
            );
            auto age = std::chrono::system_clock::now() - ftime;

            // Define the age threshold, e.g., 30 days
            if (age > std::chrono::hours(24 * 30)) {
                std::filesystem::remove(entry.path()); // Remove old logs
            }
        }
    }
}

/**
 * @brief Update the logs object by adding new entries.
 * 
 * Description:
 * This method updates the logs object by adding new log entries. These entries represent
 * events such as crashes or errors that have occurred within the system.
 */
template<class T>
void logging<T>::update() {
    std::string timestamp = getCurrentTimeString();
    // Insert the new log entries into the logs map under the current timestamp
    logEntries[timestamp].push_back(text);
}

/**
 * @brief Write the logs data to a .json file.
 * 
 * Description:
 * This method writes the contents of the logs object to a .json file in the "logs" directory.
 * The filename is based on the current timestamp.
 * 
 * @return bool Returns true if the write operation is successful, false otherwise.
 */
template<class T>
bool logging<T>::write() {
    std::filesystem::path logDir = "logs";
    std::string filename = logDir.string() + "/" + getCurrentTimeString() + ".json";
    
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    // Write logs in JSON-like format
    ofs << "{\n";
    for (const auto& [timestamp, entries] : logEntries) {
        ofs << "  \"" << timestamp << "\": [\n";
        for (const auto& entry : entries) {
            ofs << "    \"" << entry << "\",\n";
        }
        ofs << "  ],\n";
    }
    ofs << "}\n";

    ofs.close();
    return true;
}

/**
 * @brief Get the current time as a formatted string.
 * 
 * @return std::string The current time formatted as "YYYY-MM-DD HH:MM:SS".
 */
template<class T>
std::string logging<T>::getCurrentTimeString() {
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

