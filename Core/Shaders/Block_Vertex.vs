#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable
layout (location = 1) in vec2 aTexCoord; // the texture variable
layout (location = 2) in float aLayerIndex; // the layer index variable

out vec2 TexCoords; // output a color to the fragment m_shader
out float LayerIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoords = vec2(aTexCoord.x, aTexCoord.y);
    LayerIndex = aLayerIndex;
}