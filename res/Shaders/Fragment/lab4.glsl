#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform int WindowWidth;
uniform int WindowHeight;

float SquaredDistance(vec2 a, vec2 b){
    vec2 diff = a - b;
    return dot(diff, diff);
}

void main(){
    // transform the texture from [0, 1] to [-1, 1]
    vec2 CenteredPos = TexCoords * 2.0 - 1.0;
    CenteredPos.x *= float(WindowWidth) / float(WindowHeight);
    float _SquaredDistance = SquaredDistance(CenteredPos, vec2(0.0));
    if(_SquaredDistance < 0.5*0.5 && _SquaredDistance > 0.49*0.49){
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }else {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}