#include "../include/vigenere_txt.hpp"

std::string crypt::vigenere_txt::lock(const std::string &text, const std::string &password)
{
    //LOG_ERR("VIGENERE_TXT->LOCK: Text locked successfully\n");
    LOG_ERR("VIGENERE_TXT->LOCK: Text not locked\n");
    return text;
}

std::string crypt::vigenere_txt::unlock(const std::string &text, const std::string &password)
{
    LOG_ERR("VIGENERE_TXT->UNLOCK: Text not unlocked\n");
    return text;
}

std::string crypt::vigenere_txt::solve(const std::string &text, const std::string &keyword)
{
    if( valid(text) && valid(keyword) && min_size(keyword, 3) && min_size(text, 3) )
    {
        // We don't know the size of the initial password, so we have to try for
        // every size. We assume that this size is at least 2 and smaller than the
        // keyword.
        // We have to find a text, that given a password size, would have the keyword
        // in it. This can be verified because the keyword will be encrypting itslef
        // as long as it is bigger than the password used, this is a property of the
        // text-autokey vigenere version.
        bool found = false;
        size_t index = 0;
        size_t pwd_size = 0;
        for( pwd_size = 2; pwd_size < keyword.size(); ++pwd_size )
        {
            if(found) break;
            
            for( size_t i = pwd_size; i < (text.size() - keyword.size() + 1); ++i )
            {
                if(found) break;
                for( size_t j = 0; j < (keyword.size() - pwd_size); ++j )
                {
                    // The keyword works as the password
                    const int txt = static_cast<int>(text[i+j] - 'A');
                    const int pwd = static_cast<int>(keyword[j] - 'A');
                    const int key = static_cast<int>(keyword[pwd_size+j] - 'A');
                    if( key == ( (txt-pwd >= 0)? (txt-pwd) : (26+txt-pwd) ) )
                    {
                        found = true;
                        index = i;
                    }
                    else
                    {
                        found = false;
                        break;
                    }
                }
            }
        }
        --pwd_size; //Fix size
        
        if(found)
        {
            std::string answer;
            answer.resize(text.size());
            // We decrypt from the keyword
            // First we place the first part of the keyword in the text to enable our algorithm
            for ( size_t i = 0; i < pwd_size; ++i )
            {
                answer[index - pwd_size + i] = keyword[i];
            }
            // Forwards
            for ( size_t i = index; i < text.size(); ++i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                const int pwd = static_cast<int>(answer[i-pwd_size] - 'A');
                answer[i] = static_cast<char>( ((txt-pwd >= 0)? (txt-pwd) : (26+txt-pwd)) + 'A');
            }
            // Backwards
            for ( size_t i = index-1; i >= pwd_size; --i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                const int pwd = static_cast<int>(answer[i] - 'A');
                answer[i-pwd_size] = static_cast<char>( ((txt-pwd >= 0)? (txt-pwd) : (26+txt-pwd)) + 'A');
            }
            std::string password;
            for ( size_t i = 0; i < pwd_size; ++i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                const int ans = static_cast<int>(answer[i] - 'A');
                password += static_cast<char>( ((txt-ans >= 0)? (txt-ans) : (26+txt-ans)) + 'A');
            }
            LOG_ERR("VIGENERE_TXT->SOLVE: Text solved. The password is " << password << "\n");
            return answer;
        }
    }
    LOG_ERR("VIGENERE_TXT->SOLVE: Text not solved\n");
    return text;
}