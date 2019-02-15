#pragma once

#include <string>
#include "../utils/logger.h"

namespace Eng {
  namespace Events {
    class Event {
      private:
        std::string m_Name;

      public:
        Event();
        ~Event();

        inline std::string& GetName() { return m_Name; }
        inline void SetName(const std::string &name) { m_Name = name; }
    };
  }
}

typedef std::shared_ptr<Eng::Events::Event> SharedEvent;
