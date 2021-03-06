#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float innerCutOff;
    float outerCutOff;
};

out vec4 color;

uniform bool HaveTex = true;
uniform bool HaveDirLight = false;
uniform bool HavePointLight = false;
uniform bool HaveSpotLight = false;
uniform vec4 uColor;
uniform float U_a = 1.0;
uniform mat4 uVP;
uniform mat4 uMV;
uniform mat3 uULMM;

// Light variables
uniform vec3 uViewPos;
uniform Material uMaterial;

// Direction light
uniform DirLight uDirLight;

// Point light
#define NR_POINT_NUM 1
uniform PointLight uPointLight[NR_POINT_NUM];
uniform int uPointLightNum = NR_POINT_NUM;

// Spot light
#define NR_SPOT_NUM 3
uniform SpotLight uSpotLight[NR_SPOT_NUM];
uniform int uSpotLightNum = NR_SPOT_NUM;

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 VertPos = (uMV * vec4(vPosition, 0.0)).xyz;
    vec3 Normal = uULMM * vNormal;
    if(HaveTex)
    {
        vec3 result = vec3(0.0, 0.0, 0.0);

        vec3 norm = normalize(Normal);

        vec3 viewDir = normalize(uViewPos - VertPos);

        if(HaveDirLight)
            result = CalDirLight(uDirLight, norm, viewDir);

        if(HavePointLight)
            for(int i = 0; i < uPointLightNum; i++)
                result += CalPointLight(uPointLight[i], norm, VertPos, viewDir);

        if(HaveSpotLight)
            for(int i = 0; i < uSpotLightNum; i++)
                result += CalSpotLight(uSpotLight[i], norm, VertPos, viewDir);

        color = vec4(result, 1.0);
        color.a *= U_a;
    }
    else
    {
        color = uColor;
    }
    gl_Position = uVP * uMV * vec4(vPosition, 1.0);
}

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord));
    return (ambient + diffuse + specular);
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    if(dot(lightDir, normal) > 0)
    {
        if(theta > light.outerCutOff)
        {
            float diff = max(dot(normal, lightDir), 0.0);
            
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

            float distance = length(light.position - fragPos);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord));
            vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord));
            vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord));

            float epsilon = (light.innerCutOff - light.outerCutOff);
            float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);
            // float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
            ambient *= attenuation * intensity;
            diffuse *= attenuation * intensity;
            specular *= attenuation * intensity;
            return(ambient + diffuse + specular);
        }
        else
        {
            return vec3(0.0, 0.0, 0.0); 
        }
    }
    else
    {
        return vec3(0, 0, 0); 
    }
}