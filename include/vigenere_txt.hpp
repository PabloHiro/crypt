#ifndef VIGENERE_TXT_CRYPT_OIWENF9O4HOH34IH832
#define VIGENERE_TXT_CRYPT_OIWENF9O4HOH34IH832

#include <string>

#include "base_crypt.hpp"

namespace crypt
{
    class vigenere_txt : public base_crypt
    {
        public:
        
        std::string lock    (const std::string &text, const std::string &password) override;
        
        std::string unlock  (const std::string &text, const std::string &password) override;
        
        std::string solve   (const std::string &text, const std::string &keyword)  override;
        
    };
}

#endif // VIGENERE_TXT_CRYPT_OIWENF9O4HOH34IH832