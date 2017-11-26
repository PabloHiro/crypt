#include <iostream>
#include <string>
#include <fstream>

#include "config.h"

int get_data(const std::string file_name, std::string &crypt_class, std::string &clear_text, std::string &password, std::string &encrypted_text, std::string &keyword)
{
    enum class STATE_T : int { OUTSIDE_LABEL, START_LABEL, READING_CONTENT, DUMPING_LABEL, END_LABEL };
    std::ifstream file ( (ABSOLUTE_CODE_PATH + file_name), std::ifstream::in);
    if( !file.is_open() )
    {
        std::cerr << "Couldn't open file " << file_name << std::endl;
        return 1;
    }
    char c;
    STATE_T state = STATE_T::OUTSIDE_LABEL;
    std::string label_start;
    std::string label_end;
    std::string label_content;
    while(file.good())
    {
        (file >> std::ws).get(c);
        switch(state)
        {
            std::cerr << c;
            case STATE_T::OUTSIDE_LABEL:
            {
                if( c == '<' )
                {
                    state = STATE_T::START_LABEL;
                    label_start.clear();
                }
                break;
            }
            case STATE_T::START_LABEL:
            {
                if(label_start == "?xml")
                {
                    state = STATE_T::DUMPING_LABEL;
                }
                if( c == '>' )
                {
                    state = STATE_T::READING_CONTENT;
                    label_content.clear();
                    break;
                }
                label_start.push_back(c);
                break;
            }
            case STATE_T::READING_CONTENT:
            {
                if( c == '<' )
                {
                    state = STATE_T::END_LABEL;
                    label_end.clear();
                break;
                }
                label_content.push_back(c);
            }
            case STATE_T::DUMPING_LABEL:
            {
                if( c == '>' )
                {
                    label_start.clear();
                    state = STATE_T::OUTSIDE_LABEL;
                }
                break;
            }
            case STATE_T::END_LABEL:
            {
                if( c == '>' )
                {
                    if( label_end != ('/' + label_start) )
                    {
                        std::cerr << "Badly formated xml document in label " << label_start << std::endl;
                        return 2;
                    }
                    else
                    {
                        if( label_start == "crypt_class" )
                        {
                            crypt_class = label_content;
                        }
                        if( label_start == "clear_text" )
                        {
                            clear_text = label_content;
                        }
                        if( label_start == "password" )
                        {
                            password = label_content;
                        }
                        if( label_start == "encrypted_text" )
                        {
                            encrypted_text = label_content;
                        }
                        if( label_start == "keyword" )
                        {
                            keyword = label_content;
                        }
                        std::cerr << "Match with " << label_start << std::endl;
                    }
                    state = STATE_T::OUTSIDE_LABEL;
                    break;
                }
                label_end.push_back(c);
                break;
            }
        }
    }
    file.close();
    
    return 0;
}