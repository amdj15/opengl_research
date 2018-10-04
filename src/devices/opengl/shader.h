#include "../../graphic/shader.h"

namespace Devices {
  namespace OpenGL {
    class Shader : public Graphic::Shader {
      private:
        unsigned int m_RendererId;
        std::string m_VertexSource;
        std::string m_FragmentSource;
        unsigned int m_ShadersIds[2];
        const unsigned int m_ShadersLength = 2;

      public:
        Shader(std::string filepath);
        ~Shader();

        void Bind() const override;
        void Unbind() const override;
        void Init() override;

        void SetUniform1f(const std::string& name, float v1) override;
        void SetUniform3f(const std::string& name, float v1, float v2, float v3) override;
        void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) override;

        void SetUniformMatrix4fv(const std::string& name, float *matrix_ptr) override;
        void SetUniform1i(const std::string& name, int value) override;

        inline int GetId() const override { return m_RendererId; }

      private:
        unsigned int compile(const std::string &source, unsigned int type);
        int getUniformLocation(const std::string& name);
    };
  }
};