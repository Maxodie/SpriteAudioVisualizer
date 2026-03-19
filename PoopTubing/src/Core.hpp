#pragma once
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <filesystem>
#include <vector>
#include <array>
#include <memory>
#include <typeindex>
#include <functional>
#include <fstream>
#include <assert.h>
#include <regex>
#include <queue>

#include "Log/Log.hpp"

#define PT_INLINE inline

#ifdef PT_ASSERT
#   define PT_CORE_ASSERT(exp, msg)\
do\
{\
if(!(exp))\
{CORE_LOG_ERROR(msg); assert(0);}\
}while(0)

#   define PT_CLIENT_ASSERT(exp, msg)\
do\
{\
if(!(exp))\
{assert(0); CLIENT_LOG_ERROR(msg);}\
}while(0)
#else
#   define PT_CORE_ASSERT(exp, msg)
#   define PT_CLIENT_ASSERT(exp, msg)
#endif

#define PT_BIND_FUN0(fun) std::bind(&fun, this)
#define PT_BIND_FUN1(fun) std::bind(&fun, this, std::placeholders::_1)
#define PT_BIND_FUN2(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2)
#define PT_BIND_FUN3(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define PT_BIND_FUN4(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define PT_BIND_FUN5(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

#define PT_BIND_OTHER_FUN0(fun, instance) std::bind(&fun, instance)
#define PT_BIND_OTHER_FUN1(fun, instance) std::bind(&fun, instance, std::placeholders::_1)
#define PT_BIND_OTHER_FUN2(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2)
#define PT_BIND_OTHER_FUN3(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define PT_BIND_OTHER_FUN4(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define PT_BIND_OTHER_FUN5(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)


#define BIT(x) 1 << x

using TypeID = std::type_index;
using TypeIDptr = uintptr_t;

template<typename T>
TypeIDptr GetTypeIDptr()
{
    return reinterpret_cast<uintptr_t>(&typeid(T));
}

template<typename T>
TypeID GetTypeID()
{
    return typeid(T);
}
