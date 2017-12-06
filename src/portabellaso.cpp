#include "../include/portabellaso.hpp"

//ABCDEFGHIJKLM
//NOPQRSTUVWXYZ
// AB 0 - 13
// CD 12 - 25
// EF 11 - 24
// GH 10 - 23
// IJ 9 - 22
// KL 8 - 21
// MN 7 - 20
// OP 6 - 19
// QR 5 - 18
// ST 4 - 17
// UV 3 - 16
// WX 2- 15
// YZ 1 - 14

std::string crypt::portabellaso::lock(const std::string &text, const std::string &password)
{
    LOG_ERR("PORTABELLASO->LOCK: Text not locked\n");
    return text;
}

std::string crypt::portabellaso::unlock(const std::string &text, const std::string &password)
{
    LOG_ERR("PORTABELLASO->UNLOCK: Text not unlocked\n");
    return text;
}

std::string crypt::portabellaso::solve(const std::string &text, const std::string &keyword)
{
    if( valid(text) && valid(keyword) && min_size(keyword, 3) && min_size(text, 3) )
    {
        //Given a keyword, we must find where in the text its placed. This can be achieved by classifying
        //the letters in the text in to the first half or the last half of the alphabet. Once this is done,
        //the place where the opposite of this classification matches with the keyword will allow us to find
        //the password used to encrypt the text.
        std::vector<bool> txt_classifier;
        txt_classifier.reserve( text.size() );
        for( size_t i = 0; i < text.size(); ++i )
        {
            const int c = static_cast<int>(text[i] - 'A');
            txt_classifier.push_back( ((c > 12) ? true : false) ); // c > M
        }
        std::vector<bool> key_classifier;
        key_classifier.reserve( keyword.size() );
        for( size_t i = 0; i < keyword.size(); ++i )
        {
            const int c = static_cast<int>(keyword[i] - 'A');
            key_classifier.push_back( ((c > 12) ? false : true) ); // c > M
        }
        bool found = false;
        size_t index;
        for( index = 0; index < (text.size()-keyword.size()+1); ++index )
        {
            if (found) break;
            
            for ( size_t j = 0; j < keyword.size(); ++j )
            {
                if( txt_classifier[index+j]==key_classifier[j] )
                {
                    found = true;
                }
                else
                {
                    found = false;
                    break;
                }
            }
        }
        
        --index; //Fix index
        
        if( found )
        {
            std::string answer;
            answer.resize(text.size());
            // First we find the password used to encrypt the text
            std::vector<int> password;
            for( size_t i = 0; i < keyword.size(); ++i )
            {
                const int txt = static_cast<int>(text[index+i] - 'A');
                const int key = static_cast<int>(keyword[i] - 'A');
                const int distance = ( (txt-key) > 0 ? (txt-key) : (key-txt) );
                password.push_back(distance%13);
                //std::cerr << static_cast<char>(password[i]+'A') << ' ' << password[i] << ' ' << text[index+i] << '-' << keyword[i] << std::endl;
            }
            
            // The keyword may be longer than the password, so we adjust the password because currently is bigger than it really is
            // We assume that the password is at least 2 characters long and these 2 characters are not repeated twice in the password
            for( size_t i = 2; i < (password.size() - 2); ++i )
            {
                if ( (password[0] == password[i]) && (password[1] ==password[i+1]) )
                {
                    password.resize(i);
                    break;
                }
            }

            // We decrypt from the keyword
            // Forwards
            for ( size_t i = index; i < text.size(); ++i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                answer[i] = substitution(txt, password[(i-index)%password.size()]);
            }
            // Backwards
            for ( size_t i = index; i > 0; --i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                answer[i] = substitution(txt, password[password.size()-(index-i)%password.size()]);
            }
            const int txt = static_cast<int>(text[0] - 'A');
            answer[0] = substitution(txt, password[password.size()-index%password.size()]);
            std::string readable_password;
            readable_password.resize(password.size());
            for( size_t i = 0; i < password.size(); ++i )
            {
                const int txt = static_cast<int>(text[i] - 'A');
                const int ans = static_cast<int>(answer[i] - 'A');
                const int distance = ( (txt-ans) > 0 ? (txt-ans) : (ans-txt) );
                readable_password[i] = static_cast<char>( 26 - (2*distance)%26 + 'A');
            }
            LOG_ERR("PORTABELLASO->SOLVE: Text solved. The password is: " << readable_password << "\n");
            return answer;
        }
    }
    LOG_ERR("PORTABELLASO->SOLVE: Text not solved\n");
    return text;
}

char crypt::portabellaso::substitution (const int c, const int dist)
{
    //c > M
    if ( c > 12 )
    {
        return static_cast<char>( (c + 13 - dist)%13+ 'A');
    }
    else // c <= M
    {
        return static_cast<char>( 13 + (c + 13 + dist)%13 + 'A');
    }
}