#pragma once

namespace Graphic {
  enum class RenderingAPI { OpenGL };

  class Context {
    public:
      RenderingAPI m_CurrentAPI;
  };

  void CreateContext(RenderingAPI api);
  Context CurrentContext();
}
