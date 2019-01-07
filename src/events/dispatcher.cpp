#include "dispatcher.h"
#include <functional>

using namespace Eng;
using namespace Events;

std::map<std::string, std::vector<std::function<void(SharedEvent event)>>> Dispatcher::m_Handlers;
std::vector<SharedEvent> Dispatcher::m_Events;

void Dispatcher::AddEventListener(std::string eventName, std::function<void(SharedEvent event)> fn) {
  m_Handlers[eventName].push_back(fn);
}

void Dispatcher::RemoveEventListener(std::string eventName, std::function<void(SharedEvent event)> fn) {
  auto handlers = m_Handlers[eventName];

  for(int i = 0; i < handlers.size(); i++) {
    if (fn.target<void(SharedEvent event)>() == handlers[i].target<void(SharedEvent event)>()) {
      handlers.erase(handlers.begin() + i);
    }
  }

  m_Handlers[eventName] = handlers;
}

void Dispatcher::Emit(std::string eventName, SharedEvent event) {
  auto handlers = m_Handlers[eventName];

  for(auto &handler : handlers) {
    event->SetName(eventName);
    handler(event);
  }

  Dispatcher::m_Events.push_back(event);
}

void Dispatcher::ClearEvents() {
  m_Events.clear();
}
