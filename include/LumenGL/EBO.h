#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <cstddef>
#include <vector>

class EBO {
    public:
        //Constructors and ownership managment-----------
       
        EBO();

        EBO(const EBO&) = delete;
        EBO& operator=(const EBO&) = delete;

        EBO(EBO&&) noexcept = default;
        EBO& operator=(EBO&&) noexcept = default;
        
        ~EBO();

        //Getters and setters----------------------------
        
        //Core interface---------------------------------
        
        void SetIndices(GLuint* indices, size_t size, GLenum drawUsage) const;
        void SetIndices(const std::vector<GLuint>& indices, GLenum drawUsage) const;
        void Bind() const;
        void Unbind() const;
        void Delete() const;
    
    private:
        void create();
        void destroy();

        GLuint m_ID = 0;
};

#endif
