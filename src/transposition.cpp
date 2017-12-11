#include "../include/transposition.hpp"

std::string crypt::transposition::lock(const std::string &text, const std::string &password)
{
    if( valid(text) && valid(password) && min_size(password, 3) && min_size(text, 3) )
    {
        std::string answer;
        answer.resize(text.size());
        // First, we find the order of the columns
        std::vector<unsigned> col_order = order_of_columns(password);
        size_t pwd_size = password.size();
        size_t max_column_size = 1 + (text.size()/pwd_size);
        size_t curr_column_size;
        //Number of columns larger than the rest. These will be the first columns once the text is ordered
        unsigned larger_columns = text.size()%pwd_size;
        size_t index = 0;
        for( size_t i = 0; i < pwd_size; ++i )
        {
            for( size_t j = 0; j < pwd_size; ++j )
            {
                //We look for the first column to be printed
                if( col_order[j] == i )
                {
                    curr_column_size = (j >= larger_columns)? max_column_size - 1 : max_column_size;
                    for( size_t k = 0; k < curr_column_size; ++k )
                    {
                        answer[index] = text[k*pwd_size+j];
                        ++index;
                    }
                    break;
                }
            }
        }
        LOG_ERR("TRANSPOSITION->LOCK: Text locked\n");
        return answer;
    }
    LOG_ERR("TRANSPOSITION->LOCK: Text not locked\n");
    return text;
}

std::string crypt::transposition::unlock(const std::string &text, const std::string &password)
{
    if( valid(text) && valid(password) && min_size(password, 3) && min_size(text, 3) )
    {
        // In this case the input is the password of the text, not a keyword contained in the text
        // We assume that the password doesnt have repeated letters
        // First, we find the order of the columns
        std::vector<unsigned> col_order = order_of_columns(password);
        
        // Now we divide the text in n substrings, where n is the size of the text divided by the size of the password
        std::vector<std::string> columns;
        
        size_t pwd_size = password.size();
        size_t column_size = 1 + (text.size()/pwd_size);
        
        //Number of columns larger than the rest. These will be the first columns once the text is ordered
        unsigned larger_columns = text.size()%pwd_size;
        size_t total_size = 0;
        for( size_t i = 0; i < pwd_size; ++i )
        {
            size_t curr_size;
            if( get_pos( col_order, i ) >= larger_columns ) //This column will be shorter
            {
                curr_size = column_size - 1;
            }
            else
            {
                curr_size = column_size;
            }
            
            std::string sub_text( (text.begin() + total_size) , (text.begin() + total_size + curr_size) );
            columns.push_back(sub_text);
            total_size += curr_size;
        }
        
        // Once we have all the columns stored, we have to print them in the correct order
        std::string answer;
        answer.resize(text.size());
        for( size_t i = 0; i < pwd_size; ++i )
        {
            for( size_t j = 0; j < pwd_size; ++j )
            {
                if( col_order[i] == j )
                {
                    for( size_t k = 0; k < columns[j].size(); ++k )
                    {
                        answer[k*pwd_size+i] = columns[j][k];
                    }
                    break;
                }
            }
        }
        //LOG_ERR("TRANSPOSITION->UNLOCK: Text unlocked\n");
        return answer;
    }
    LOG_ERR("TRANSPOSITION->UNLOCK: Text not unlocked\n");
    return text;
}

std::string crypt::transposition::solve(const std::string &text, const std::string &keyword)
{
    if( valid(text) && valid(keyword) && min_size(keyword, 3) && min_size(text, 3) )
    {
        std::string password;
        std::string answer;
        for( size_t pwd_size = 3; pwd_size < keyword.size(); ++pwd_size )
        {
            password.clear();
            LOG_ERR("Trying with password size " << pwd_size << "\n");
            for( size_t i = 0; i < pwd_size; ++i )
            {
                password.push_back('A' + i);
            }
            do {
                answer = this->unlock( text, password );
                if ( answer.find( keyword ) != std::string::npos )
                {
                    LOG_ERR("TRANSPOSITION->SOLVE: Text solved. The password is: " << password << "\n");
                    return answer;
                }
            } while( std::next_permutation(password.begin(), password.end()) );
        }
    }
    LOG_ERR("TRANSPOSITION->SOLVE: Text not solved\n");
    return text;
}

size_t crypt::transposition::get_pos( const std::vector<unsigned> &col_order , const unsigned col )
{
    for ( size_t i = 0; i < col_order.size(); ++i )
    {
        if( col_order[i] == col )
        {
            return i;
        }
    }
    return col_order.size(); // Not found
}

std::vector<unsigned> crypt::transposition::order_of_columns( const std::string &password )
{
    std::vector<unsigned> col_order;
    for( size_t i = 0; i < password.size(); ++i )
    {
        unsigned place = 0;
        for ( size_t j = 0; j < password.size(); ++j )
        {
            if ( password[i] > password[j] )
            {
                place++;
            }
        }
        col_order.push_back ( place );
    }
    return col_order;
}