#pragma once

namespace Graphic {
  class IndexBuffer {
    protected:
      unsigned int m_RendererId;
      unsigned int m_Count;

    public:
      virtual ~IndexBuffer() = default;

      static IndexBuffer* Create();

      virtual void SetData(const unsigned int* data, unsigned int count) = 0;
      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      inline unsigned int getCount() const { return m_Count; }
      inline unsigned int getRendererId() const { return m_RendererId; }
  };
};