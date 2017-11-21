#ifndef CRYPT_093O9FN4NFINOINOIN12
#define CRYPT_093O9FN4NFINOINOIN12

#include <iostream>
#include <mutex>

#ifndef LOG_VERBOSE
#define LOG_ERR(err_txt)
#else
inline std::mutex& err_mutex()
{
    static  std::mutex mtx;
    return mtx;
}
#define LOG_ERR(err_txt) ( err_mutex().lock(), std::cerr << err_txt ), err_mutex().unlock()
#endif

#endif // CRYPT_093O9FN4NFINOINOIN12