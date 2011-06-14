#include "Tokenizer.h"
// From user vzczc 
//      post http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c 


const std::string Tokenizer::DELIMITERS(" \t\n\r");

Tokenizer::Tokenizer(const std::string& s) :
    m_string(s), 
    m_offset(0), 
    m_delimiters(DELIMITERS) {}

Tokenizer::Tokenizer(const std::string& s, const std::string& delimiters) :
m_string(s), 
    m_offset(0), 
    m_delimiters(delimiters) {}

bool Tokenizer::NextToken() 
{
    return NextToken(m_delimiters);
}

const std::string Tokenizer::GetToken() const{
    return m_token;
}

bool Tokenizer::NextToken(const std::string& delimiters) 
{
    size_t i = m_string.find_first_not_of(delimiters, m_offset);
    if (std::string::npos == i) 
    {
        m_offset = m_string.length();
        return false;
    }

    size_t j = m_string.find_first_of(delimiters, i);
    if (std::string::npos == j) 
    {
        m_token = m_string.substr(i);
        m_offset = m_string.length();
        return true;
    }

    m_token = m_string.substr(i, j - i);
    m_offset = j;
    return true;
}