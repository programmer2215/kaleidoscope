#include <string>
#include <memory>
#include <vector>



class Expression {
public:
  virtual ~Expression() = default;
};

class NumberExpression : public Expression {
    double Val;
public:
    NumberExpression(double val): Val(val) {}
    
};

class VariableExpression : public Expression {
    std::string Name;
public:
    VariableExpression(std::string name): Name(name){}
};

class BinaryExpression : public Expression {
    char Opr;
    std::unique_ptr<Expression> Left, Right;

public:
    BinaryExpression(char opr, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : Opr(opr), Left(std::move(left)), Right(std::move(right)) {}

};

class CallExpression : public Expression {
    std::string Callee;
    std::vector<std::unique_ptr<Expression>> Args;

public:
    CallExpression (std::string callee, std::vector<std::unique_ptr<Expression>> args)
        : Callee(callee), Args ( std:: move ( args)) {}

};

class Prototype : public Expression {
    std::string Name;
    std::vector<std::unique_ptr<Expression>> Args;

public:
    Prototype (const std::string &name, std::vector<std::unique_ptr<Expression>> args)
        : Name(name), Args ( std:: move ( args)) {}

    const std::string &getname() const { return Name;}
};

class Function {
  std::unique_ptr<Prototype> Proto;
  std::unique_ptr<Expression> Body;

public:
  Function(std::unique_ptr<Prototype> proto,
              std::unique_ptr<Prototype>body)
    : Proto(std::move(proto)), Body(std::move(body)) {}
};