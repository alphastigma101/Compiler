#ifndef _LOGGING_H_
#define _LOGGING_H_
#include <definitions.h>
namespace Logging {
    template<class T>
    class logging {
        public:
            logging() = default;
            logging<T>(const logTable<std::map<std::string, std::vector<std::string>>>& old_logs, const std::string& text): logEntries(old_logs), text(this->text) {};
            ~logging() noexcept = default;
            static std::string getCurrentTimeString();
            void rotate();             
            void update();             
            bool write();
            inline std::map<std::string, std::vector<std::string>> getLogs() { return logEntries; };
        private:
            logTable<std::map<std::string, std::vector<std::string>>> logEntries;
            std::string text;
    };  
};
using namespace Logging;
#endif



