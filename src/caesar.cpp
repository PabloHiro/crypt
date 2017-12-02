#include "../include/caesar.hpp"

std::string crypt::caesar::lock(const std::string &text, const std::string &password)
{
    if ( valid(text) && valid(password) && (password.size() == 1) )
    {
        std::string ans;
        ans.resize( text.size() );
        int c = static_cast<int>(password[0] - 'A');
        for ( size_t i = 0; i < ans.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr += c;
            curr %= 26;
            ans[i] = 'A' + static_cast<char>(curr);
        }
       return ans;
    }
    LOG_ERR("CAESAR. Text not locked\n");
    return text;
}

std::string crypt::caesar::unlock(const std::string &text, const std::string &password)
{
    if ( valid(text) && valid(password) && (password.size() == 1) )
    {
        std::string ans;
        ans.resize( text.size() );
        int c = static_cast<int>(password[0] - 'A');
        for ( size_t i = 0; i < ans.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr -= c;
            curr = (curr < 0) ? curr+26 : curr%26;
            ans[i] = 'A' + static_cast<char>(curr);
        }
       return ans;
    }
    LOG_ERR("CAESAR. Text not unlocked\n");
    return text;
}

std::string crypt::caesar::solve(const std::string &text, const std::string &keyword)
{
    if ( valid(text) && valid(keyword) && min_size(keyword, 5) )
    {
        std::string ans(text);
        for ( int c = 0; c < 26; ++c )
        {
            for( size_t i = 0; i < text.size(); ++i )
            {
                int curr = static_cast<int>(text[i] - 'A');
                curr -= c;
                curr = (curr < 0) ? curr+26 : curr%26;
                ans[i] = 'A' + static_cast<char>(curr);
            }
            
            if ( ans.find ( keyword ) != std::string::npos )
            {
               LOG_ERR("CAESAR. The password is "<< static_cast<char>(c + 'A') << "\n");
               return ans;
            }
        }
    }
    LOG_ERR("CAESAR. Text not solved\n");
    return text;
}