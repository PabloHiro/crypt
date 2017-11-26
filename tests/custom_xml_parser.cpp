#include <iostream>
#include <string>
#include <fstream>

int get_data(const std::string file_name, std::string &crypt_class, std::string &clear_text, std::string &password, std::string &encrypted_text, std::string &keyword);
{
    enum class STATE_T : int (OUTSIDE_LABEL, START_LABEL, READING_CONTENT, DUMPING_LABEL, END_LABEL)
    std::ifstream file (file_name, std::ifstream::in);
    char c;
    STATE_T state = OUTSIDE_LABEL;
    std::string label_start;
    std::string label_end;
    std::string label_content;
    while(file.good())
    {
        file.get(c);
        switch(state)
        {
            case OUTSIDE_LABEL:
            {
                if( c == '<' )
                {
                    state = START_LABEL;
                    label_start.clear();
                }
                break;
            }
            case START_LABEL:
            {
                if(label_start == "?xml")
                {
                    state = DUMPING_LABEL;
                }
                if( c == '>' )
                {
                    state = READING_CONTENT;
                    label_content.clear();
                    break;
                }
                label_start.push_back(c);
                break;
            }
            case READING_CONTENT:
            {
                if( c == '<' )
                {
                    state = END_LABEL;
                    label_end.clear();
                break;
                }
                label_content.push_back(c);
            }
            case DUMPING_LABEL:
            {
                if( c == '>' )
                {
                    label_start.clear();
                    state = OUTSIDE_LABEL;
                }
                break;
            }
            case END_LABEL:
            {
                if( c == '>' )
                {
                    if( label_end != ('/' + label_start) )
                    {
                        std::cerr << "Badly formated xml document in label " << label_start << std::endl;
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
                        if( label_start == "key_word" )
                        {
                            key_word = label_content;
                        }
                        std::cerr << "Match with " << label_start << std::endl;
                    }
                    state = OUTSIDE_LABEL;
                    break;
                }
                label_end.push_back(c);
                break;
            }
        }
    }
    file.close();
}