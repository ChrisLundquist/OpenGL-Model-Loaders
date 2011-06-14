#ifndef Tokenizer_h__
#define Tokenizer_h__

#include <string>
// From user vzczc 
//      post http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c 
class Tokenizer  {
public:
    static const std::string DELIMITERS;
    Tokenizer(const std::string& s);
    Tokenizer(const std::string& s, const std::string& delimiters);
    bool NextToken();
    bool NextToken(const std::string& delimiters);
    const std::string GetToken() const;
    //    void Reset();
protected:
    size_t m_offset;
    const std::string m_string;
    std::string m_token;
    std::string m_delimiters;
};
#endif // Tokenizer_h__