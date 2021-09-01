//
// Created by kolya on 8/28/2021.
//
#pragma once

#include <tuple>
#include <string>
#include <iostream>

namespace stomp
{

    enum class PATTERN
    {
        INTEGER,
        FLOAT,
        STRING,
        UNKNOWN
    };

    template<typename T>
    PATTERN GetPatternFromParam(const T& arg)
    {
        return PATTERN::UNKNOWN;
    }

    template<>
    PATTERN GetPatternFromParam(const int& arg)
    {
        return PATTERN::INTEGER;
    }

    template<>
    PATTERN GetPatternFromParam(const std::string& arg)
    {
        return PATTERN::STRING;
    }

    template<>
    PATTERN GetPatternFromParam(const float& arg)
    {
        return PATTERN::FLOAT;
    }

    template<int Num, typename... Args>
    auto GetFromPack(Args&&... args)
    {
        return std::get<Num>(std::forward_as_tuple(args...));
    }

    template<typename... Args>
    class Message
    {
    public:
        explicit Message(const std::string& str, const Args&... args)
        {
            uint8_t size = sizeof...(Args);
            for (uint8_t index = 0; index < size; index++)
            {
                auto arg = GetFromPack<0>(args...);
                PATTERN pattern = GetPatternFromParam(arg);
            }
        }

        std::string GetMessage() const { return m_Info; }

    protected:
        std::string m_Info;

    private:
        bool InsertAtPattern(PATTERN pattern)
        {
            return true;
        }

        int GetNextPatternLocation(PATTERN IfValid) const
        {
            return -1;
        }
    };
}