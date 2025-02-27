#include <iostream>
#include <memory>
#include <vector>

class Visitor;

class Node
{
public:
    virtual void Accept(Visitor &visitor) = 0;
    virtual ~Node() = default;
};

class Expression : public Node
{
public:
    void Accept(Visitor &visitor) override;
};

class Statement : public Node
{
public:
    void Accept(Visitor &visitor) override;
};

class Scope : public Node
{
public:
    void Accept(Visitor &visitor) override;
};

class Visitor
{
public:
    virtual void Visit(Expression &node) = 0;
    virtual void Visit(Statement &node) = 0;
    virtual void Visit(Scope &node) = 0;
    virtual ~Visitor() = default;
};

class Parser : public Visitor
{
public:
    void Visit(Expression &node) override;
    void Visit(Statement &node) override;
    void Visit(Scope &node) override;
};

class Analyzer : public Visitor
{
public:
    void Visit(Expression &node) override;
    void Visit(Statement &node) override;
    void Visit(Scope &node) override;
};

int main(int argc, char *argv[])
{
    auto pExpression = std::make_unique<Expression>();
    auto pStatement = std::make_unique<Statement>();
    auto pScope = std::make_unique<Scope>();
    auto pParser = std::make_unique<Parser>();
    auto pAnalyzer = std::make_unique<Analyzer>();

    std::vector<std::pair<Node &, Visitor &>> pairs{
        {*pExpression, *pParser},
        {*pStatement, *pParser},
        {*pScope, *pParser},
        {*pExpression, *pAnalyzer},
        {*pStatement, *pAnalyzer},
        {*pScope, *pAnalyzer},
    };

    for (auto &pair : pairs)
    {
        pair.first.Accept(pair.second);
    }
}

void Expression::Accept(Visitor &visitor)
{
    visitor.Visit(*this);
}

void Statement::Accept(Visitor &visitor)
{
    visitor.Visit(*this);
}

void Scope::Accept(Visitor &visitor)
{
    visitor.Visit(*this);
}

void Parser::Visit(Expression &node)
{
    std::cout << "Parsing Expression...\n";
}

void Parser::Visit(Statement &node)
{
    std::cout << "Parsing Statement...\n";
}

void Parser::Visit(Scope &node)
{
    std::cout << "Parsing Scope...\n";
}

void Analyzer::Visit(Expression &node)
{
    std::cout << "Analyzing Expression...\n";
}

void Analyzer::Visit(Statement &node)
{
    std::cout << "Analyzing Statement...\n";
}

void Analyzer::Visit(Scope &node)
{
    std::cout << "Analyzing Scope...\n";
}
