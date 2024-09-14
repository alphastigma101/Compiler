#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <memory>

template<typename Derived>
class ThreadTracker : public std::thread {
    private:
        inline static std::vector<std::thread::id> active_threads;
        inline static std::mutex thread_mutex;
    public:
        template<typename Callable, typename... Args>
        ThreadTracker(Callable&& func, Args&&... args) : std::thread([this, f = std::forward<Callable>(func)](auto&&... params) {
            try {
                f(std::forward<decltype(params)>(params)...);
            } 
            catch (...) {
                // TODO: Log the expression that occurred!
            }
            removeThread();
            }, std::forward<Args>(args)...)
        {
            addThread();
        }
        /** ------------------------------------------------------------------
         * @brief This is a default constructor that allows you to add threads to it
         * 
         * @param newThread Pass a thread instance, which will be kept track on. It is a universial object 
         * @param other Pass in a callable object such as a function, member function, or lambda. It is a universal object 
         *
         * @details 
         * -------------------------------------------------------------------
         */
        template<typename T, typename U = std::nullptr_t, typename = std::enable_if_t<std::is_base_of_v<ThreadTracker, std::remove_reference_t<T>>>>
        ThreadTracker(T&& newThread, U&& other = nullptr) noexcept : std::thread(std::forward<T>(newThread)) {
            if constexpr (!std::is_same_v<U, std::nullptr_t>) {
                std::thread(std::forward<U>(other));
            }
            addThread();
        };
        /** ------------------------------------------
         * @brief Default deconstructor that cleans up all the remaining threads
         * 
         * 
         * -------------------------------------------
         */
        ~ThreadTracker() { if (joinable()) { join(); } };
        /** -------------------------------------------------
         * 
         * 
         */
        inline static std::size_t getActiveThreadCount() {
            std::lock_guard<std::mutex> lock(thread_mutex);
            return active_threads.size();
        };
        /** ---------------------------------
         * @brief Used for derived classes to call in methods that have a reference bound to it 
         * 
         * @param Args package/expansion that allows multiple arguments 
         * 
         * @return Calls in member function of the pointed to class instance Derived.
         */
        template<typename... Args>
        inline void run(Args&&... args) { return static_cast<Derived*>(this)->run(std::forward<Args>(args)...); }
        
    private:
        /** -----------------------------------------------------------------
         * @brief Prvate method that the cons
         *
        */
        inline void addThread() {
            std::lock_guard<std::mutex> lock(thread_mutex);
            active_threads.push_back(get_id());
        };
        inline void removeThread() {
            std::lock_guard<std::mutex> lock(thread_mutex);
            active_threads.erase(std::remove(active_threads.begin(), active_threads.end(), get_id()), active_threads.end());
        };
        inline void accessVariableByThread() {


        };
};
