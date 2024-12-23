#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float LayerIndex;

uniform sampler2DArray ourTextureArray;

void main() {
    FragColor = texture(ourTextureArray, vec3(TexCoords, LayerIndex));
    //FragColor = vec4(TexCoords, 0.0, 1.0);
}