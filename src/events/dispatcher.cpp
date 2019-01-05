#include "dispatcher.h"
#include <functional>

using namespace Eng;
using namespace Events;

std::map<std::string, std::vector<std::function<void(SharedEvent event)>>> Dispatcher::m_Handlers;

void Dispatcher::AddEventListener(std::string eventName, std::function<void(SharedEvent event)> fn) {
  m_Handlers[eventName].push_back(fn);
}

void Dispatcher::Emit(std::string eventName, SharedEvent event) {
  auto handlers = m_Handlers[eventName];

  for(auto &handler : handlers) {
    handler(event);
  }
}
