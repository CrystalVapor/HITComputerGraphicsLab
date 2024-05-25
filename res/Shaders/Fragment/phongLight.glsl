#version 330 core
out vec4 Fragcolor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 WorldPos;
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
     //ambient
      vec3 objColor = texture(texture1, TexCoord).rgb;
      float ambientstrength = 0.1;
      vec3 ambient = ambientstrength * lightColor;
     //diffuse
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos - WorldPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * lightColor;

     //specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - WorldPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;
     //output
     vec3 result = (ambient + diffuse) * objColor + specular;
     Fragcolor = vec4(result, 1.0);
}