#include "../include/caesar.hpp"

std::string crypt::caesar::lock(const std::string &text, const std::string &password)
{
    if( valid(text) && valid(password) && (password.size() == 1) && min_size(text, 2) )
    {
        std::string answer;
        answer.resize( text.size() );
        int c = static_cast<int>(password[0] - 'A');
        for ( size_t i = 0; i < answer.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr += c;
            curr %= 26;
            answer[i] = 'A' + static_cast<char>(curr);
        }
        LOG_ERR("CAESAR->LOCK: Text locked successfully\n");
       return answer;
    }
    LOG_ERR("CAESAR->LOCK: Text not locked\n");
    return text;
}

std::string crypt::caesar::unlock(const std::string &text, const std::string &password)
{
    if( valid(text) && valid(password) && (password.size() == 1) && min_size(text, 2))
    {
        std::string answer;
        answer.resize( text.size() );
        int c = static_cast<int>(password[0] - 'A');
        for ( size_t i = 0; i < answer.size(); ++i )
        {
            int curr = static_cast<int>(text[i] - 'A');
            curr -= c;
            curr = (curr < 0) ? curr+26 : curr%26;
            answer[i] = 'A' + static_cast<char>(curr);
        }
       return answer;
    }
    LOG_ERR("CAESAR->UNLOCK: Text not unlocked\n");
    return text;
}

std::string crypt::caesar::solve(const std::string &text, const std::string &keyword)
{
    if( valid(text) && valid(keyword) && min_size(keyword, 5) && min_size(text, 5) )
    {
        std::string answer(text);
        for ( int c = 0; c < 26; ++c )
        {
            for( size_t i = 0; i < text.size(); ++i )
            {
                int curr = static_cast<int>(text[i] - 'A');
                curr -= c;
                curr = (curr < 0) ? curr+26 : curr%26;
                answer[i] = 'A' + static_cast<char>(curr);
            }
            
            if ( answer.find ( keyword ) != std::string::npos )
            {
               LOG_ERR("CAESAR->SOLVE: Text solved. The password is "<< static_cast<char>(c + 'A') << "\n");
               return answer;
            }
        }
    }
    LOG_ERR("CAESAR->SOLVE: Text not solved\n");
    return text;
}