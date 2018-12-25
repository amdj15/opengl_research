#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Eng {
  namespace Utils {
    class Logger {
      public:
        static std::shared_ptr<spdlog::logger> m_SpdLogger;

      public:
        inline static std::shared_ptr<spdlog::logger> GetLogger() { return m_SpdLogger; }

        static void Init();
    };
  }
}

#define LOG_DEBUG(...) Eng::Utils::Logger::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Eng::Utils::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Eng::Utils::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Eng::Utils::Logger::GetLogger()->error(__VA_ARGS__)
