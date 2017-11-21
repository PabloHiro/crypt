#include "cesar.hpp"

crypt::caesar::std::string lock(const std::string &text, const std::string &password)
{
    if ( valid(text) && valid(password) && (password.size == 1) )
    {
        std::string ans;
        std::string ans.resize( text.size() );
        int c = static_cast<int>(password[0]);
        for ( size_t i = 0; i < ans.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr += static_cast<int>(c);
            curr %= 26;
            ans[i] = 'A' + static_cast<char>(curr);
        }
       return ans;
    }
    LOG_ERR("CAESAR. Text not locked" << std::endl);
    return text;
}

crypt::caesar::std::string unlock(const std::string &text, const std::string &password)
{
    if ( valid(text) && valid(password) && (password.size == 1) )
    {
        std::string ans;
        std::string ans.resize( text.size() );
        int c = static_cast<int>(password[0]);
        for ( size_t i = 0; i < ans.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr -= static_cast<int>(c);
            curr = (curr < 0) ? curr+26 : curr%26;
            ans[i] = 'A' + static_cast<char>(curr);
        }
       return ans;
    }
    LOG_ERR("CAESAR. Text not unlocked" << std::endl);
    return text;
}

crypt::caesar::std::string solve(const std::string &text, const std::string &keyword)
{
    if ( valid(text) && valid(keyword) && valid_size(keyword, 5) )
    {
        std::string ans(text);
        for ( char c = 'A'; c <= 'Z'; ++c )
        {
            for( size_t i = 0; i < text.size(); ++i )
            {
                int curr = static_cast<int>(text[i] - 'A');
                curr += static_cast<int>(c);
                curr %= 26;
                ans[i] = 'A' + static_cast<char>(curr);
            }
            
            if ( ans.find ( key_word ) != std::string::npos )
            {
               LOG_ERR("CAESAR. The password is "<< 'Z' - c + 'A' << std::endl);
               return ans;
            }
        }
    }
    LOG_ERR("CAESAR. Text not solved" << std::endl);
    return text;
}