#pragma once
#ifndef _LOGGING_H_
#define _LOGGING_H_
#include <unordered_map>                                                        
#include <map>                                                                  
#include <vector>                                                               
#include <iostream> 

namespace Logging {
    class logging {
        public:
            explicit logging(std::map<std::string, std::vector<std::string>>& old_logs): logs(old_logs) {};
            ~logging() noexcept = default;
            static std::string getCurrentTimeString();
            void rotate();
            void update();
            bool write();
            inline std::map<std::string, std::vector<std::string>> getLogs() { return logs; };
        private:
            std::map<std::string, std::vector<std::string>> logs;
    };  
};
using namespace Logging;
#endif



