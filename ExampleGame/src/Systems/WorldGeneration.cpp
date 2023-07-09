#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(const std::string& path)
{
    LWE_PROFILE_FUNCTION();

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = nullptr;
    {
        LWE_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");

        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    }

    LWE_CORE_ASSERT(data, "STB_IMAGE::LOAD_FAILED");

    m_Width = width;
    m_Height = height;
    m_Channels = channels;

    if (m_Channels == 3 || m_Channels == 4)
    {
        for (int i = 0; i < m_Width; i++)
        {
            for (int j = 0; j < m_Height; j++)
            {
                int index = (j * m_Width + i) * m_Channels;

                float r = static_cast<float>(data[index]);
                float g = static_cast<float>(data[index + 1]) ;
                float b = static_cast<float>(data[index + 2]);
                float a = (m_Channels == 4) ? static_cast<float>(data[index + 3]) : 1.0f;

                m_MapTiles.push_back(glm::vec4(r, g, b, a));

            }
        }
    }

    stbi_image_free(data);
}

