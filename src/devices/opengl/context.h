#pragma once

#include "../../graphic/api/rendering_context.h"

namespace Devices {
  class GLContext : public Graphic::Context {
    public:
      GLContext();
      ~GLContext();
  };
}
