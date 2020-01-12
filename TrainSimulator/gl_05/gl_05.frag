#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
  
out vec4 color;

uniform sampler2D Texture0;
//uniform sampler2D Texture1;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;

uniform Light light;

void main()
{
    //color = mix(texture(Texture0, TexCoord), texture(Texture1, TexCoord),0.4);
    //color = texture(Texture0, TexCoord);
    //color = vec4(1.0f, 0.0f, 0.0f, 0.0f);


	// ambient
    vec3 ambient = light.ambient * texture(Texture0, TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(Texture0, TexCoord).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec;// * texture(Texture0, TexCoord).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}
