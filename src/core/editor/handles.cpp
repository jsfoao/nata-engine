#include "handles.h"

namespace Nata
{
    NShader* Handles::Shader = nullptr;
    bool Handles::m_Enabled = false;
    NMesh* Handles::m_LineMesh = nullptr;
    std::vector<float> Handles::m_LineVertices;

    void Handles::DrawLine(const vec3& start, const vec3& end, const vec3& color)
    {
        if (!m_Enabled)
        {
            return;
        }
        std::vector<float> data =
        {
            // positions               // normals        // t coords  // tangent         // bitangent
            start.x, start.y, start.z, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            end.x,   end.y,   end.z  , 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };


        Shader->Enable();
        Shader->SetUniform3f("color", color);
        Shader->SetUniformMat4("view", NEngine::Camera->GetViewMatrix());
        Shader->SetUniformMat4("projection", NEngine::Camera->GetProjectionMatrix());
        Shader->SetUniformMat4("model", mat4(1.f));

        glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z);       
        glVertex3f(start.x, start.y, start.z);
        glVertex3f(end.x, end.y, end.z);
        glEnd();

        //NEngine::Window->GetRenderer()->Submit(m_LineMesh, true);
    }

    void Handles::DrawWireCube(const vec3& pos, const vec3& size, const vec3& color)
    {
        if (!m_Enabled)
        {
            return;
        }
        vec3 hsize = size / 2.f;
        vec3 v0 = vec3(pos.x - hsize.x, pos.y - hsize.y, pos.z - hsize.z);
        vec3 v1 = vec3(pos.x + hsize.x, pos.y - hsize.y, pos.z - hsize.z);
        vec3 v2 = vec3(pos.x + hsize.x, pos.y - hsize.y, pos.z + hsize.z);
        vec3 v3 = vec3(pos.x - hsize.x, pos.y - hsize.y, pos.z + hsize.z);

        vec3 v4 = vec3(pos.x - hsize.x, pos.y + hsize.y, pos.z - hsize.z);
        vec3 v5 = vec3(pos.x + hsize.x, pos.y + hsize.y, pos.z - hsize.z);
        vec3 v6 = vec3(pos.x + hsize.x, pos.y + hsize.y, pos.z + hsize.z);
        vec3 v7 = vec3(pos.x - hsize.x, pos.y + hsize.y, pos.z + hsize.z);

        DrawLine(v0, v1, color);
        DrawLine(v1, v2, color);
        DrawLine(v2, v3, color);
        DrawLine(v3, v0, color);

        DrawLine(v4, v5, color);
        DrawLine(v5, v6, color);
        DrawLine(v6, v7, color);
        DrawLine(v7, v4, color);

        DrawLine(v0, v4, color);
        DrawLine(v1, v5, color);
        DrawLine(v2, v6, color);
        DrawLine(v3, v7, color);
    }

    void Handles::DrawHandles(const CTransform* transform, const float size)
    {
        Handles::DrawLine(transform->Position, transform->Position + transform->Right * size, vec3(1.f, 0.f, 0.f));
        Handles::DrawLine(transform->Position, transform->Position + transform->Up * size, vec3(0.f, 1.f, 0.f));
        Handles::DrawLine(transform->Position, transform->Position + transform->Forward * size, vec3(0.f, 0.f, 1.f));
    }

    void Handles::DrawWireSphere(const vec3& pos, const float radius, const vec3& color)
    {
        if (!m_Enabled)
        {
            return;
        }
        DrawCircle(pos, 2.f, vec3(1.f, 0.f, 0.f), color);
        DrawCircle(pos, 2.f, vec3(0.f, 1.f, 0.f), color);
        DrawCircle(pos, 2.f, vec3(0.f, 0.f, 1.f), color);
    }

    void Handles::DrawCircle(const vec3& pos, const float radius, const vec3& normal, const vec3& color, const int segments)
    {
        if (!m_Enabled)
        {
            return;
        }
        vec3 vec = vec3(0.f);
        if (normal == vec3(1.f, 0.f, 0.f))
        {
            vec = vec3(0.f, 1.f, 0.f);
        }
        else if (normal == vec3(0.f, 1.f, 0.f))
        {
            vec = vec3(1.f, 0.f, 0.f);
        }
        else if (normal == vec3(0.f, 0.f, 1.f))
        {
            vec = vec3(1.f, 0.f, 0.f);
        }
        else
        {
            vec = vec3(1.f, 0.f, 0.f);
        }

        const vec3 tangent = normalize(cross(normal, vec));
        const vec3 bitangent = normalize(cross(normal, tangent));
        const float TAU = two_pi<float>();
        vec3 prevPos = vec3(0.f);
        for (unsigned int i = 0; i <= segments; i++)
        {
            float t = (float)i / (float)segments;
            float angle = t * TAU;
            vec2 dir = vec2(cos(angle), sin(angle));
            vec3 currPos = pos + (dir.x * tangent * radius) + (dir.y * bitangent * radius);
            
            if (i == 0)
            {
                prevPos = currPos;
                continue;
            }
            DrawLine(prevPos, currPos, color);
            prevPos = currPos;
        }
    }

    bool Handles::Init()
    {
        SetEnable(true);
        Shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
        return Shader != nullptr;
    }

    void Handles::SetEnable(bool enabled)
    {
        m_Enabled = enabled;
    }
}