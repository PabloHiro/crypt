#include <iostream>
#include <string>
#include <memory>

#include <crypt.hpp>

int get_data(const std::string file_name, std::string &crypt_class, std::string &clear_text, std::string &password, std::string &encrypted_text, std::string &keyword); // In custom_xml_parser.cpp

crypt::base_crypt* factory(const std::string crypt_class)
{
    if(crypt_class == "caesar")
    {
        return new crypt::caesar;
    }
    return nullptr;
}

int main ( int argc, char **argv )
{
    // 1: crypt_class
    if( argc != 2 )
    {
        std::cerr << "usage: " << argv[0] << "crypt_class.xml" << std::endl;
        return 1;
    }
    
    const std::string file_name(argv[1]);
    std::string crypt_class, clear_text, password, encrypted_text, keyword;
    
    if(get_data(file_name, crypt_class, clear_text, password, encrypted_text, keyword))
    {
        std::cerr << "parsing not succesfull" << std::endl;
        return 1;
    }
    
    std::cerr << "clear_text is: " << clear_text << std::endl;
    std::cerr << "password is: " << password << std::endl;
    std::cerr << "encrypted_text is: " << encrypted_text << std::endl;
    std::cerr << "keyword is: " << keyword << std::endl;
    
    unique_ptr<crypt::base_crypt> my_crypt( factory(crypt_class) );
    crypt::my_crypt->solve(encrypted_text,keyword);
    return 0;
}