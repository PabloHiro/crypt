#ifndef BASE_CRYPT_23I2NFO2MJ32JK3ONO2N3R
#define BASE_CRYPT_23I2NFO2MJ32JK3ONO2N3R

#include <string>

#include "logging/logging.hpp"

namespace crypt
{
    class base_crypt
    {
        public:
        
        virtual ~base_crypt() {};
        
        virtual std::string lock    (const std::string &text, const std::string &password) = 0;
        
        virtual std::string unlock  (const std::string &text, const std::string &password) = 0;
        
        virtual std::string solve   (const std::string &text, const std::string &keyword)  = 0;
        
        protected:
        
        virtual bool valid(const std::string &text);                           //It has a default implementation
        
        virtual bool min_size(const std::string &password, size_t min_length); //It has a default implementation
        
    };
}


#endif // BASE_CRYPT_23I2NFO2MJ32JK3ONO2N3R