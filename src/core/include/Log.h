#pragma once

#include"Core.h"
#include<spdlog/spdlog.h>
namespace CustomSpace
{
    class Log
    {
        public:
            static void Init();

            static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        private:

        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

#define CORE_TRACE(...)     ::CustomSpace::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)      ::CustomSpace::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)      ::CustomSpace::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)     ::CustomSpace::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)  ::CustomSpace::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define GAME_TRACE(...)     ::CustomSpace::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GAME_INFO(...)      ::CustomSpace::Log::GetClientLogger()->info(__VA_ARGS__)
#define GAME_WARN(...)      ::CustomSpace::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GAME_ERROR(...)     ::CustomSpace::Log::GetClientLogger()->error(__VA_ARGS__)
#define GAME_CRITICAL(...)  ::CustomSpace::Log::GetClientLogger()->critical(__VA_ARGS__)