#ifndef AFFINE_CRYPT_23NOI3NO34NTIO3NTOI3
#define AFFINE_CRYPT_23NOI3NO34NTIO3NTOI3

#include <string>
#include <exception>

#include "base_crypt.hpp"

namespace crypt
{
    class affine : public base_crypt
    {
        public:
        
        std::string lock    (const std::string &text, const std::string &password) override;
        
        std::string unlock  (const std::string &text, const std::string &password) override;
        
        std::string solve   (const std::string &text, const std::string &keyword)  override;
        
        private:
        
        bool valid_password (const std::string password, int &a, int &b);
    };
}

#endif // AFFINE_CRYPT_23NOI3NO34NTIO3NTOI3