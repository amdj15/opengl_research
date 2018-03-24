#pragma once

#include <vector>

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
};

class VertexBufferLayout {
  private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;

  public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void push(unsigned int count);

    inline unsigned int getStride() const {
      return m_Stride;
    }

    inline const std::vector<VertexBufferElement> getElements() const {
      return m_Elements;
    }
};
