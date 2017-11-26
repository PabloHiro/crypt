#ifndef CAESAR_CRYPT_23JN9ON2FO2N3J0J09JI
#define CAESAR_CRYPT_23JN9ON2FO2N3J0J09JI

#include "base_crypt.hpp"

namespace crypt
{
    class caesar : public base_crypt
    {
        public:
        
        caesar();
        ~caesar(){};
        
        std::string lock    (const std::string &text, const std::string &password) override;
        
        std::string unlock  (const std::string &text, const std::string &password) override;
        
        std::string solve   (const std::string &text, const std::string &keyword)  override;
        
    };
}

#endif // CAESAR_CRYPT_23JN9ON2FO2N3J0J09JI