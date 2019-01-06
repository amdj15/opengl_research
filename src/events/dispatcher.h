#pragma once

#include <map>
#include <vector>
#include "event.h"

namespace Eng {
  namespace Events {
    class Dispatcher {
      private:
        static std::map<std::string, std::vector<std::function<void(SharedEvent event)>>> m_Handlers;

      public:
        static void AddEventListener(std::string eventName, std::function<void(SharedEvent event)> fn);
        static void RemoveEventListener(std::string eventName, std::function<void(SharedEvent event)> fn);
        static void Emit(std::string eventName, SharedEvent event);
    };
  }
}
