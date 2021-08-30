//
// Created by kolya on 8/28/2021.
//
#pragma once

#include <tuple>
#include <string>
#include <iostream>

template<int Num, typename ...Args>
auto GetFromPack(Args&&... args)
{
    return std::get<Num>(std::forward_as_tuple(args...));
}

template<typename ...Args>
class Message
{
public:
    Message(const std::string& str, const Args&... args)
    {
        auto first = GetFromPack<0>(args...);
        std::cout << first;
    }

    std::string GetMessage() const { return m_Info; }

protected:
   std::string m_Info;
};
