#version 330 core
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D bufferedTexture;

void main() {
    FragColor = texture(bufferedTexture, TexCoords);
}