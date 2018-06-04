#pragma once

class IndexBuffer {
  private:
    unsigned int m_RendererId;
    unsigned int m_Count;
  public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer();
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    void SetData(const unsigned int* data, unsigned int count);

    inline unsigned int getCount() const {
      return m_Count;
    }

    inline unsigned int getRendererId() const {
      return m_RendererId;
    }
};
