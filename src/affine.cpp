#include "../include/affine.hpp"

std::string crypt::affine::lock(const std::string &text, const std::string &password)
{
    int a = 0, b = 0;
    if( valid(text) && valid_password(password, a, b) )
    {
        std::string answer;
        answer.resize(text.size());
        for(size_t i = 0; i < text.size(); ++i )
        {
            const int K = static_cast<int>(text[i] - 'A');
            answer[i] = static_cast<char>((a*K + b)%26 + 'A');
        }
        LOG_ERR("AFFINE->LOCK: Text locked\n");
        return answer;
    }
    LOG_ERR("AFFINE->LOCK: Text not locked\n");
    return text;
}

std::string crypt::affine::unlock(const std::string &text, const std::string &password)
{
    int a = 0, b = 0;
    if( valid(text) && valid_password(password, a, b) )
    {
        std::string answer;
        answer.resize(text.size());
        for(size_t i = 0; i < text.size(); ++i )
        {
            const int C = static_cast<int>(text[i] - 'A');
            int K = 0;
            // a*K + b = C
            while ( ((a*K + b)%26) != C )
            {
                ++K;
            }
            answer[i] = static_cast<char>(K + 'A');
        }
        LOG_ERR("AFFINE->UNLOCK: Text unlocked\n");
        return answer;
    }
    LOG_ERR("AFFINE->UNLOCK: Text not unlocked\n");
    return text;
}

std::string crypt::affine::solve(const std::string &text, const std::string &keyword)
{
    if( valid(text) && valid(keyword) && min_size(keyword, 3) && min_size(text, 3) )
    {
        bool found = false;
        int a = 0, b = 0;
        for(size_t i = 0; i < (text.size() - keyword.size() + 1); ++i)
        {
            if( found ) break;
            // C1 = a*K1 + b
            // C2 = a*K2 + b
            // a * (K1 - K2) = (C1 - C2)
            // b = C1 - a*K1
            const int C1 = static_cast<int>(text[i]);
            const int C2 = static_cast<int>(text[i+1]);
            const int K1 = static_cast<int>(keyword[0]);
            const int K2 = static_cast<int>(keyword[1]);
            const int dC = (C1-C2) >= 0 ? (C1-C2) : (26+(C1-C2));
            const int dK = (K1-K2) >= 0 ? (K1-K2) : (26+(K1-K2));
            a = 0;
            // a * (K1 - K2) = (C1 - C2)
            while( ((dK*a)%26 != dC) && (a<26) )
            {
                ++a;
            }
            b = (C1 - a*K1);
            while ( b < 0 )
            {
                b += 26;
            }
            b %= 26;
            for (size_t j = 2; j < keyword.size(); ++j)
            {
                const int CJ = static_cast<int>(text[i+j] - 'A');
                const int KJ = static_cast<int>(keyword[j] - 'A');
                if ( CJ != ((a*KJ + b)%26) ) // Parameters dont match
                {
                    found = false;
                    break;
                }
                else
                {
                    found = true;
                }
            }
        }
        
        if( found )
        {
            std::string answer;
            answer.resize(text.size());
            for(size_t i = 0; i < text.size(); ++i )
            {
                const int C = static_cast<int>(text[i] - 'A');
                int K = 0;
                // a*K + b = C
                while ( ((a*K + b)%26) != C )
                {
                    ++K;
                }
                answer[i] = static_cast<char>(K + 'A');
            }
            LOG_ERR("AFFINE->SOLVE: Text solved. The password is a = " << a << ", b = " << b << "\n");
            return answer;
        }
    }
    LOG_ERR("AFFINE->SOLVE: Text not solved\n");
    return text;
}

bool crypt::affine::valid_password(const std::string password, int &a, int &b)
{
    //A valid password must have the following format:
    // val_A,val_B
    std::string alpha, beta;
    size_t comma_pos = password.find(',');
    if( comma_pos != std::string::npos )
    {
        alpha = password.substr(0, comma_pos);
        beta = password.substr(comma_pos+1);
        try
        {
            a = std::stoi(alpha);
            b = std::stoi(beta);
        }
        catch (const std::invalid_argument& ia)
        {
             LOG_ERR("Invalid argument: " << ia.what() << "\n");
             return false;
        }
        catch (const std::out_of_range& oor) {
            LOG_ERR("Out of Range error: " << oor.what() << "\n");
            return false;
        }
        return true;
    }
    else return false;
}
