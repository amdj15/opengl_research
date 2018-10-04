#pragma once

#include <vector>

template <typename T>
struct VertexBufferElement {
  T type;
  unsigned int count;
};

class VertexBufferLayout {
  private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement<unsigned int> > m_Elements;

  public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void Push(unsigned int count);

    inline unsigned int getStride() const { return m_Stride; }
    inline const std::vector<VertexBufferElement<unsigned int> > getElements() const { return m_Elements; }
};
