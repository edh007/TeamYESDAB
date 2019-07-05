#pragma once

#include "glew.h"
#include "../math/Math.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "base/Component.h"
#include "imgui.h"
#include "vector2.h"
// Freetype lib
#include <ft2build.h>
#include FT_FREETYPE_H
#pragma comment(lib,"freetype26.lib")

namespace gi
{
    typedef aiVector2t<float> vec2;
    // Holds all state information relevant to a character as loaded using FreeType
    struct Character {
        GLuint TextureID;   // ID handle of the glyph texture
        vec2 Size;    // Size of glyph
        vec2 Bearing;  // Offset from baseline to left/top of glyph
        GLuint Advance;    // Horizontal offset to advance to next glyph
    };

    typedef std::unordered_map<GLchar, Character> Characters;

    //! FontData struct
    struct FontData {
        FT_Face m_face;
        FT_Library m_ftlib;
        Characters m_chars;
        unsigned m_fontSize;
    };

    //struct FontData;
    class ComponentText : public Component
    {
    public:
        static const std::string COMPONENT_ID;

        static ComponentText* CreateComponentText(Entity* pOwner, unsigned _size);

        void InitModelByPath(std::string const& _path);

        unsigned TextureFromFile(const char* path, const std::string& directory);
        //private:
        explicit ComponentText(Entity* pObject, unsigned _size);
        virtual ~ComponentText();

        void DrawComponent();

        //! Text functions
        void SetText(const char* text, ...);
        const std::string& GetText(void) const;

        //! Font data functions
        FontData& GetFontData(void) {
            m_fd.m_chars = m_chars;
            m_fd.m_face= m_face;
            m_fd.m_fontSize= m_fontSize;
            m_fd.m_ftlib = m_ft;
            return m_fd;
        }
        

        void SetColor(const Vec4& color);
        Vec4 GetColor(void) const;
        void SetFontSize(unsigned size);



        /******************************************************************************/
        /*!
        \brief - setting the whole font to use with the fontSize
        \param fontSize - size of the font
        */
        /******************************************************************************/
        void SetFont(unsigned fontSize)
        {
            m_fontSize = fontSize;

            // All functions return a value different than 0 whenever an error occurred
            if (FT_Init_FreeType(&m_ft))
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

            // Load font as face
            //FT_Face face;
            if (FT_New_Face(m_ft, "../../resources/font/Default.ttf", 0, &m_face))
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

            // Set size to load glyphs as
            FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);

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
                    vec2(static_cast<float>(m_face->glyph->bitmap.width), static_cast<float>(m_face->glyph->bitmap.rows)),
                    vec2(static_cast<float>(m_face->glyph->bitmap_left), static_cast<float>(m_face->glyph->bitmap_top)),
                    static_cast<GLuint>(m_face->glyph->advance.x)
                };
                m_chars.insert(std::pair<char, Character>(c, character));
            }

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        /******************************************************************************/
        /*!
        \brief - Get the characters
        \return m_chars - return characters
        */
        /******************************************************************************/
        Characters& GetCharacters(void)
        {
            return m_chars;
        }

        /******************************************************************************/
        /*!
        \brief - Return the freetype face
        \return m_face - return freetype face
        */
        /******************************************************************************/
        const FT_Face& GetFT_Face(void) const
        {
            return m_face;
        }

        /******************************************************************************/
        /*!
        \brief - Get freetype library
        \return m_ft - return value
        */
        /******************************************************************************/
        const FT_Library& GetFT_Lib(void) const
        {
            return m_ft;
        }

        /******************************************************************************/
        /*!
        \brief - Get freetype font size
        \return m_fontSize - return value
        */
        /******************************************************************************/
        unsigned GetFontSize(void) const
        {
            return m_fontSize;
        }


    private:
        Vec4 m_color;
        std::string m_text;
        //FontData m_data;
        char m_textStorage[1024];


        FontData m_fd;
        //// FreeType
        FT_Library m_ft;			// FreeType
        FT_Face	   m_face;			// Freetype face
        FT_UInt	   m_fontSize;		// font size
        Characters m_chars;			// Ascii storage
    };
}