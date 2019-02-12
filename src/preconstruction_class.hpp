
#ifndef PRECONSTRUCTION_CLASS_HPP
#define PRECONSTRUCTION_CLASS_HPP

#include <iostream>


template<class token_type>
class preconstruction_class
{
protected:
    token_type token;
    preconstruction_class(){}
    ~preconstruction_class(){}
public:
};

struct test_construction_token {
    int i;
    test_construction_token() = default;
    ~test_construction_token() = default;
    test_construction_token(test_construction_token&& other) = default;
    test_construction_token&& operator=(test_construction_token&& other){
        i = other.i;
        std::cout << "operator=(test_construction_token&& other)" << std::endl;
    }
    void operator=(const test_construction_token& other) = delete;
    test_construction_token(const test_construction_token& ) = delete;
};

class test : public preconstruction_class<test_construction_token>
{
public:
    test(test_construction_token&& inpt_token) {
        this->token = std::move(inpt_token);
    }
    ~test(){}
};

#endif  /* PRECONSTRUCTION_CLASS_HPP */
