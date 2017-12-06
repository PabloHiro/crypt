#include <iostream>
#include <string>
#include <memory>

#include "crypt.hpp"

int get_data(const std::string file_name, std::string &crypt_class, std::string &clear_text, std::string &password, std::string &encrypted_text, std::string &keyword); // In custom_xml_parser.cpp

crypt::base_crypt* factory(const std::string crypt_class)
{
    if(crypt_class == "caesar")
    {
        return new crypt::caesar;
    }
    
    if(crypt_class == "affine")
    {
        return new crypt::affine;
    }
    
    if(crypt_class == "vigenere_txt")
    {
        return new crypt::vigenere_txt;
    }
    
    if(crypt_class == "transposition")
    {
        return new crypt::transposition;
    }
    
    if(crypt_class == "portabellaso")
    {
        return new crypt::portabellaso;
    }
    return nullptr;
}

int main ( int argc, char **argv )
{
    if( argc != 2 )
    {
        std::cerr << "usage: " << argv[0] << " crypt_class.xml" << std::endl;
        return 1;
    }
    
    const std::string file_name(argv[1]);
    std::string crypt_class, clear_text, password, encrypted_text, keyword;
    
    if(get_data(file_name, crypt_class, clear_text, password, encrypted_text, keyword))
    {
        std::cerr << "parsing not succesfull" << std::endl;
        return 1;
    }
    
    std::cerr << "crypt_class is: " << crypt_class << std::endl;
    std::cerr << "clear_text is: " << clear_text << std::endl;
    std::cerr << "password is: " << password << std::endl;
    std::cerr << "encrypted_text is: " << encrypted_text << std::endl;
    std::cerr << "keyword is: " << keyword << std::endl;
    std::cerr << std::endl;
    
    std::unique_ptr<crypt::base_crypt> my_crypt( factory(crypt_class) );
    
    std::string curr_encr;
    std::string curr_clr1;
    std::string curr_clr2;
    
    curr_encr = my_crypt->lock(clear_text, password);
    curr_clr1 = my_crypt->unlock(encrypted_text, password);
    curr_clr2 = my_crypt->solve(encrypted_text,keyword);
    
    if( curr_encr != encrypted_text )
    {
        std::cout << "function lock doesn't work properly: " << std::endl;
        std::cout << "\t output: " << curr_encr << std::endl;
        std::cout << "\t expected output: " << encrypted_text <<std::endl;
    }
    if( curr_clr1 != clear_text )
    {
        std::cout << "function unlock doesn't work properly: " << std::endl;
        std::cout << "\t output: " << curr_clr1 << std::endl;
        std::cout << "\t expected output: " << clear_text << std::endl;
    }
    if( curr_clr2 != clear_text )
    {
        std::cout << "function solve doesn't work properly: " << std::endl;
        std::cout << "\t output: " << curr_clr2 << std::endl;
        std::cout << "\t expected output: " << clear_text << std::endl;
    }
    return 0;
}