#pragma once
#include <iostream>
#include <vector>
#include <string>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// OpenGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Texture library
#include "stb_image.h"

// OpenGL math library
#include "core/glm_math.h"

// Nata
#include "core/core.h"
#include "core/ecs/ecs.h"
#include "core/window.h"

// Nata :: Renderer
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/buffer.h"
#include "core/renderer/mesh.h"
#include "core/renderer/model.h"
#include "core/renderer/renderable.h"
#include "core/renderer/renderer.h"

// Nata :: Editor
#include "core/editor/handles.h"

using namespace Nata;
using namespace glm;