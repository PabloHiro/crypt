#ifndef LOGGING_CRYPT_20939FNF4O94INF
#define LOGGING_CRYPT_20939FNF4O94INF

#include <iostream>
#include <mutex>

#ifndef LOG_ERR
    #define LOG_ERR(err_txt)
    #else
        inline std::mutex& err_mutex()
        {
            static  std::mutex mtx;
            return mtx;
        }
    #define LOG_ERR(err_txt) ( err_mutex().lock(), std::cerr << err_txt ), err_mutex().unlock()
#endif // LOG_ERR

#endif //LOGGING_CRYPT_20939FNF4O94INF