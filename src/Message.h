//
// Created by kolya on 8/28/2021.
//
#pragma once

#include <tuple>
#include <string>
#include <iostream>

namespace stomp::log
{

    enum class PATTERN
    {
        INTEGER,
        FLOAT,
        STRING,
        UNKNOWN
    };

    template<class T>struct tag_t{};
    template<class T>constexpr tag_t<T> tag{};

    template<class T, class...Ts>
    constexpr bool is_string_like(tag_t<T>, Ts&&...){ return false; }
    template<class T, class A>
    constexpr bool is_string_like( tag_t<std::basic_string<T,A>> ){ return true; }

    template<class T>
    constexpr bool detect_string=is_string_like(tag<T>); // enable ADL extension

    template<class T, class...Ts>
    constexpr bool is_char_like(tag_t<T>, Ts&&...){ return false; }
    constexpr bool is_char_like( tag_t<char> ){ return true; }
    constexpr bool is_char_like( tag_t<wchar_t> ){ return true; }

    template<class T>
    constexpr bool detect_char=is_char_like(tag<T>); // enable ADL extension

    template<typename T>
    PATTERN GetPatternFromParam(T arg)
    {
        typedef typename std::remove_cv<T>::type type;
        std::cout << typeid(T).name() << " " << typeid(type).name();
        if constexpr (detect_char<type>) return PATTERN::STRING;
        if constexpr (detect_string<type>) return PATTERN::STRING;
        if constexpr (std::is_floating_point_v<type>) return PATTERN::FLOAT;
        if constexpr (std::is_arithmetic_v<type>) return PATTERN::INTEGER;
        return PATTERN::UNKNOWN;
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