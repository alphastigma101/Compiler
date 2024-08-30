#ifndef _LOGGING_H_
#define _LOGGING_H_
#include <definitions.h>
namespace Logging {
    template<class T>
    class logging {
        public:
            logging() = default;
            logging<T>(const logTable<std::map<std::string, std::vector<std::string>>>& old_logs, const std::string& text): currentEntries(logEntries) {
                this->text = text;
            };
            ~logging() noexcept = default;
            static std::string getCurrentTimeString();
            static void rotate();             
            static void update();             
            static bool write();
            void printLogs();
            static std::string getText() {
                return text;
            };
            inline std::map<std::string, std::vector<std::string>> getLogs() { return currentEntries; };
        private:
            logTable<std::map<std::string, std::vector<std::string>>> currentEntries;
            static std::string text;
    };  
};
using namespace Logging;
#include <logging.cc>
#endif



