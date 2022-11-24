#include "editor.h"

namespace Nata
{
    Handles::Handles()
    {
        shader = Shader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
        Init();
    }

    void Handles::DrawLine(const vec3& start, const vec3& end, const vec3& color)
	{
        //vector<float> vertices =
        //{
        //    // positions               // normals        // texture coords
        //    start.x, start.y, start.z, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f,
        //    end.x  , end.y  , end.z  , 0.0f, 0.0f, 0.0f, 0.0f,  0.0f,
        //};

        //Mesh mesh = Mesh(vertices, N_DRAW_LINES);

        //shader.Enable();
        //shader.SetUniform3f("color", color);

        //shader.SetUniformMat4("view", view);
        //shader.SetUniformMat4("projection", projection);

        //mat4 model = mat4(1.0f);
        //model = translate(model, start);
        //shader.SetUniformMat4("model", model);

        //mesh.Draw();
        //shader.Disable();
	}

    bool Handles::Init()
    {
        return true;
    }

    void Handles::Update(mat4 view, mat4 projection)
    {
        this->view = view;
        this->projection = projection;
    }
}
