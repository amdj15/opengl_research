#include "logger.h"

using namespace Eng;
using namespace Utils;

std::shared_ptr<spdlog::logger> Logger::m_SpdLogger;

void Logger::Init() {
  m_SpdLogger = spdlog::stdout_color_mt("CORE");
  m_SpdLogger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
  m_SpdLogger->set_level(spdlog::level::trace);
}
