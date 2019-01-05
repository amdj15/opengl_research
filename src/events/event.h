#pragma once

#include <string>
#include "../utils/logger.h"

namespace Eng {
  namespace Events {
    class Event {
      private:
        std::string m_Name;

      public:
        Event(std::string name);
        ~Event();

        inline std::string& GetName() { return m_Name; }
    };
  }
}

typedef std::shared_ptr<Eng::Events::Event> SharedEvent;
