#include "Mesh.h"

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned> _indices, vector<Texture> _textures)
{
    m_vertices = _vertices;
    m_indices = _indices;
    m_textures = _textures;

    SetUpMesh();
}

void Mesh::Draw(Shader shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    unsigned int normalNr = 0;
    unsigned int heightNr = 0;
    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                                          // retrieve texture number (the N in diffuse_textureN)
        stringstream ss;
        string number;
        string name = m_textures[i].type;
        ss << "[";
        if (name == "texture_diffuse")
            ss << diffuseNr++; // transfer unsigned int to stream
        else if (name == "texture_specular")
            ss << specularNr++; // transfer unsigned int to stream
        else if (name == "texture_normal")
            ss << normalNr++; // transfer unsigned int to stream
        else if (name == "texture_height")
            ss << heightNr++; // transfer unsigned int to stream
        ss << "]";
        number = ss.str();
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    Vec4 tex(static_cast<float>(diffuseNr), static_cast<float>(specularNr), 
        static_cast<float>(normalNr), static_cast<float>(heightNr));
	//TODO(Dongho): Check the number of the textures
	if ((diffuseNr >= 2) || (specularNr >= 2) || (normalNr >= 2) || (heightNr >= 2))
		std::cout << "Check Number of Textures at Mesh!" << std::endl;
    glUniform4fv(glGetUniformLocation(shader.ID, "texNum"), 1, &tex.v[0]);
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetUpMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nor));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, biTangent));

    glBindVertexArray(0);
}
