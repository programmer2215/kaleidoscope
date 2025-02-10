#include <string>
#include <iostream>
#include "./constants.hpp"
enum Token{
    __tok_eof = -1,

    // commands
    __tok_def = -2,
    __tok_extern = -3,

    //primary
    __tok_identifier = -4,
    __tok_number = -5

};



static std::string IdentifierStr;
static double NumVal;


static int gettok(){
    static int LastChar = ' ';

    while (isspace(LastChar)){
        LastChar = getchar();
    }

    if (isalpha(LastChar) || LastChar == UNDERSCORE){
        IdentifierStr = LastChar;
        while (isalnum(LastChar = getchar()) || LastChar == UNDERSCORE)
            IdentifierStr += LastChar;
        if (IdentifierStr == DEF_KEYWORD)
            return Token::__tok_def;
        if (IdentifierStr == EXTERN_KEYWORD)
            return Token::__tok_extern;
        return Token::__tok_identifier;        
    }

    if (isdigit(LastChar) || LastChar == PERIOD){
        std::string NumStr;
        NumStr += LastChar;
        bool readDecimal = (LastChar == PERIOD) ? true : false;
        while (isdigit(LastChar) || LastChar == PERIOD){
            if (LastChar == PERIOD && readDecimal)
                return -1;    
            NumStr += LastChar;
            LastChar = getchar();
        }
        NumVal = strtod(NumStr.c_str(), 0);
        return Token::__tok_number;
        
    }

    if (LastChar == '#'){
        do LastChar = getchar();
        while (LastChar != '\n' && LastChar != '\r' && LastChar != EOF);        
        if (LastChar != EOF){
            return gettok();
        }
    }

    if (LastChar == EOF)
        return Token::__tok_eof;

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

int main() {
    int token =  gettok();
    std::cout << "Token: " << token << std::endl;
    if (token == -4){
        std::cout << "Identifier: " << IdentifierStr << std::endl;
    }else if (token == -5){
        std::cout << "Number: " << NumVal << std::endl;
    }
    return 0;
}


