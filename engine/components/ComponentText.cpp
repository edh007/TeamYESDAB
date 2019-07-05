#include "components/ComponentText.h"
#include <imgui.h>
const std::string gi::ComponentText::COMPONENT_ID = "gi_cmp_text";

using namespace gi;

gi::ComponentText::ComponentText(Entity* pObject, unsigned _size)
	: Component(pObject)
{
    SetFont(_size);
}

gi::ComponentText::~ComponentText()
{
	m_pOwner = nullptr;
}

gi::ComponentText* gi::ComponentText::CreateComponentText(Entity* pOwner, unsigned _size)
{
  ComponentText* pModel = new ComponentText(pOwner, _size);

	return pModel;
}

/******************************************************************************/
/*!
\brief - Setting the color of the text with parameter color
\param color - Setting value of the text's color
*/
/******************************************************************************/
void ComponentText::SetColor(const Vec4& color)
{
    m_color = color;
}

/******************************************************************************/
/*!
\brief - Getting the color of the text class
\return m_color - return the color of the Text
*/
/******************************************************************************/
Vec4 ComponentText::GetColor(void) const
{
    return m_color;
}

/******************************************************************************/
/*!
\brief - Set the text inside the class
\param text - setting the text to print out.
*/
/******************************************************************************/
void ComponentText::SetText(const char* text, ...)
{
    va_list ap;

    va_start(ap, text);
    vsprintf_s(m_textStorage, text, ap);
    va_end(ap);

    m_text = m_textStorage;
}

/******************************************************************************/
/*!
\brief - Get the text of this component
\return m_text - return the text data of this component
*/
/******************************************************************************/
const std::string& ComponentText::GetText(void) const
{
    return m_text;
}

/******************************************************************************/
/*!
\brief - Set the font size with input
\param size - setting the fontsize
*/
/******************************************************************************/
void ComponentText::SetFontSize(unsigned size)
{
    if (m_fontSize == size)
        return;

    m_chars.clear();

    FT_Set_Pixel_Sizes(m_face, 0, size);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            vec2(static_cast<float>(m_face->glyph->bitmap.width),
            static_cast<float>(m_face->glyph->bitmap.rows)),
            vec2(static_cast<float>(m_face->glyph->bitmap_left),
            static_cast<float>(m_face->glyph->bitmap_top)),
            static_cast<GLuint>(m_face->glyph->advance.x)
        };
        m_chars.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    m_fontSize = size;
}



void gi::ComponentText::DrawComponent()
{
    if (ImGui::CollapsingHeader("Text Component"))
    {
        ImGui::PushItemWidth(160);
        {
            float textWidth;
            float buttonSpacing;

            if (ImGui::GetWindowWidth() < 700)
            {
                textWidth = 300 - (700 - ImGui::GetWindowWidth());
                buttonSpacing = textWidth + 10;
            }
            else
            {
                textWidth = 300;
                buttonSpacing = 310;
            }

            // Actor name + active state
            {
                static char buf2[32] = "";
                ImGui::Text("Text: %s\n", m_text.c_str());
                ImGui::PushItemWidth(textWidth);
                {
                    if (ImGui::InputText("TXT", buf2, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                    {
                        buf2[0] = '\0';
                        SetText(buf2);
                    }
                    ImGui::PopItemWidth();
                }
                //ImGui::SameLine(buttonSpacing);

            }

            ImGui::InputFloat("Color R", &m_color.x, 0.f, 1.f, 3);
            ImGui::InputFloat("Color G", &m_color.y, 0.f, 1.f, 3);
            ImGui::InputFloat("Color B", &m_color.z, 0.f, 1.f, 3);
            ImGui::InputFloat("Color A", &m_color.w, 0.f, 1.f, 3);

            
            float size =  static_cast<int> (m_fontSize);
            ImGui::InputFloat("Size", &size, 1.f, 10.f, 2);
            //ImGui::InputInt("Size", &size, 0, 1, 3);
            SetFontSize(static_cast<unsigned int>(size));
            m_fontSize = static_cast<FT_UInt>(size);
        }
        ImGui::PopItemWidth();
    }
    
    
}