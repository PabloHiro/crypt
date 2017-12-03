#ifndef PORTABELLASO_CRYPT_9382RN3ONONOI3NON2T09
#define PORTABELLASO_CRYPT_9382RN3ONONOI3NON2T09

#include <string>

#include "base_crypt.hpp"

namespace crypt
{
    class portabellaso : public base_crypt
    {
        public:
        
        std::string lock    (const std::string &text, const std::string &password) override;
        
        std::string unlock  (const std::string &text, const std::string &password) override;
        
        std::string solve   (const std::string &text, const std::string &keyword)  override;
        
    };
}

#endif // PORTABELLASO_CRYPT_9382RN3ONONOI3NON2T09