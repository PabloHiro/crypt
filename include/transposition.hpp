#ifndef TRANSPOSITION_CRYPT_3T4NINO3J2I30I2
#define TRANSPOSITION_CRYPT_3T4NINO3J2I30I2

#include <string>

#include "base_crypt.hpp"

namespace crypt
{
    class transposition : public base_crypt
    {
        public:
        
        std::string lock    (const std::string &text, const std::string &password) override;
        
        std::string unlock  (const std::string &text, const std::string &password) override;
        
        std::string solve   (const std::string &text, const std::string &keyword)  override;
        
    };
}

#endif // TRANSPOSITION_CRYPT_3T4NINO3J2I30I2