#include "../include/transposition.hpp"

std::string crypt::transposition::lock(const std::string &text, const std::string &password)
{
    LOG_ERR("TRANSPOSITION. Text not locked\n");
    return text;
}

std::string crypt::transposition::unlock(const std::string &text, const std::string &password)
{
    LOG_ERR("TRANSPOSITION. Text not unlocked\n");
    return text;
}

std::string crypt::transposition::solve(const std::string &text, const std::string &keyword)
{
    LOG_ERR("TRANSPOSITION. Text not sikved\n");
    return text;
}