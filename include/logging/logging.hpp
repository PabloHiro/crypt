#ifndef LOGGING_CRYPT_20939FNF4O94INF
#define LOGGING_CRYPT_20939FNF4O94INF

#include <iostream>
#include <mutex>

#ifndef LOG_VERBOSE
    #define LOG_ERR(txt)
#else
    inline std::mutex& err_mutex()
    {
        static std::mutex mtx;
        return mtx;
    }
    #define LOG_ERR(txt) ( err_mutex().lock(), std::cerr << txt ), err_mutex().unlock()
#endif // LOG_VERBOSE

#endif //LOGGING_CRYPT_20939FNF4O94INF