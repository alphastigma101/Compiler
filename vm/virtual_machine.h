#pragma once
#include <unistd.h>
#include <compiler/compiler.h>
#include <filesystem>
// Isolate the process from the hosts system
namespace VirtualMachine {
    class logs {
        public:
            logs(); // use the default constructor to create the log format 
            ~logs();
            static void print(std::map<std::string, std::string> log);
            static void create(std::string err);
            static void rotate();
            std::map<std::string,std::string> getLogs();
        private:
            std::map<std::string, std::string> entries;
    };
    class container: public unistd, public logs, public compile, public std::filesystem::path  {
        // PID is going to be needed for the container
        // restriction is also going to needed a lot
        // mounting is also going to be needed to mount the files in a isolated enviromnet 
        // Should copy the programming languages extensions into the environment 
        // when someone types ctrl+c automatically clean up the enviornment 
        // Need to create it's own 
        public:
            container(const *char language);
            ~container();
            // a command that will display the options as what you can do inside the enviroment
            // Simply type help when the terminal is launched
            static void help(int argc, char** argv); // user system call 
            static int q(int argc, char** argv); // close and clean up the environment
            static int viewLogs(int argc, char** argv); // wrapper around the printlogs method
            static int setup(int argc, char** argv); // automatiically gets called and sets up the environment up by linking the language. ex go hello.go it should execute the code inside /usr/bin/go
            static int clean(void); // gets automatically executed if CTRL+C signal is received or if the user clicks out of the terminal 
        protected:
            // need to include pid types here 
        private:
            static compiler c;
    };
    void run(const *char languageName); // This needs to be executed and it will call in the container and then the compiler

};



// Work with this and abstract it
/*
 *
 * libc: The standard C library (libc) provides wrappers around many system calls, including those related to Linux namespaces. You can use C++ with libc functions directly.

libnl: The Netlink library (libnl) provides a high-level API to communicate with the Linux kernel's Netlink subsystem, which is used for configuring network interfaces and other networking-related tasks.

GitHub repository: https://github.com/thom311/libnl
Boost.Process: Boost.Process provides a C++ library to manage system processes, which can be useful for interacting with namespaces and other system-level tasks.

GitHub repository: https://github.com/boostorg/process
libseccomp: The libseccomp library provides an easy-to-use, high-level interface for managing Linux Security Modules (LSM) and can be useful for restricting system calls within containers.

GitHub repository: https://github.com/seccomp/libseccomp
C++ wrappers for Linux syscalls: While not a single library, various C++ wrappers exist that provide convenient interfaces for making Linux system calls, including those related to namespaces.

syscall and unistd.h headers provide direct access to system calls. You can write C++ wrappers around these to handle namespace-related calls.*/
