#include "../include/base_crypt.hpp"

bool crypt::base_crypt::valid(const std::string &text)
{
    for( size_t i = 0; i < text.size(); ++i )
    {
        if(text[i] < 'A' || text[i] > 'Z')
        {
            LOG_ERR("Not valid characters. Only characters from 'A' to 'Z' are valid\n");
            return false;
        }
    }
    return true;
}

bool crypt::base_crypt::min_size(const std::string &password, size_t min_length)
{
    if( password.size() < min_length )
    {
        LOG_ERR("Word must be " << min_length << "characters long enough\n");
        return false;
    }
    else return true;
}