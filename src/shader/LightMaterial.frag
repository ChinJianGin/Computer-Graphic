#version 330 core
#define BLINN
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normalmap;
    float shininess;
};

struct DirLight{
    vec3 position;
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

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;
// in vec4 fragPosLight;

uniform bool HaveTex = true;
uniform bool HaveNormal = false;
uniform bool HaveDirLight = false;
uniform bool HavePointLight = false;
uniform bool HaveSpotLight = false;
uniform vec4 uColor;
uniform float U_a = 1.0;
// uniform sampler2D uShadowMap;
uniform samplerCube depthMap;

uniform float far_plane;

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

float ShadowCalculation(vec3 fragPos);

// float near = 0.1;
// float far = 10.0;
// float linearizeDepth(float depth)
// {
//     return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
// }

void main()
{
    if(HaveTex)
    {
        vec3 result = vec3(0.0, 0.0, 0.0);

        vec3 norm = vec3(0.0, 0.0, 0.0);

        // vec3 color = texture(uMaterial.diffuse, texCoord).rgb;

        if(HaveNormal != true)
        {
            norm = normalize(Normal);
        }
        else
        {
            norm = texture(uMaterial.normalmap, texCoord).rgb;
            norm = norm * 2.0 - 1.0;
            norm = normalize(TBN * norm);
        }

        vec3 viewDir = normalize(uViewPos - FragPos);

        // if(HaveDirLight)
        //     result = CalDirLight(uDirLight, norm, viewDir);

        if(HavePointLight)
            for(int i = 0; i < uPointLightNum; i++)
                result += CalPointLight(uPointLight[i], norm, FragPos, viewDir);

        // if(HaveSpotLight)
        //     for(int i = 0; i < uSpotLightNum; i++)
        //         result += CalSpotLight(uSpotLight[i], norm, FragPos, viewDir);


        FragColor = vec4(result, 1);
        // FragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z) / far), 1.0);
    }
    else
    {
        FragColor = uColor;
    }
}

float ShadowCalculation(vec3 fragPos)
{
    // vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    vec3 fragToLight = fragPos - uPointLight[0].position;

    // projCoords = projCoords * 0.5 + 0.5;

    // float closesDepth = texture(uShadowMap, projCoords.xy).r;
    float closesDepth = texture(depthMap, fragToLight).r;
    closesDepth *= far_plane;

    // float currentDepth = projCoords.z;
    float currentDepth = length(fragToLight);

    // vec3 normal = normalize(Normal);
    // vec3 lightDir = normalize(uPointLight.position - FragPos);
    // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float bias = 0.05;
    float shadow = 0.0;
    // vec2 pixelSize = 1.0 / textureSize(uShadowMap, 0);

    // for(int x = -1; x <= 1; ++x)
    // {
    //     for(int y = -1; y <= 1; ++y)
    //     {
    //         float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * pixelSize).r;
    //         shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    //     }
    // }
    // shadow /= 9.0;

    // if(projCoords.z > 1.0)
    //     shadow = 0.0;

    shadow = currentDepth - bias > closesDepth ? 1.0 : 0.0;
    return shadow;
}

// vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir)
// {
//     vec3 lightDir = normalize(light.position - FragPos);
//     float diff = max(dot(normal, lightDir), 0.0);

// #ifndef BLINN
//     vec3 reflectDir = reflect(-lightDir, normal);
// #else
//     vec3 reflectDir = normalize(lightDir + viewDir);
// #endif

//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

//     // float shadow = ShadowCalculation(fragPosLight);
//     float shadow = 0.0;
//     vec3 ambient = light.ambient;// * vec3(texture(uMaterial.diffuse, texCoord));
//     vec3 diffuse = light.diffuse * diff;// * vec3(texture(uMaterial.diffuse, texCoord));
//     vec3 specular = light.specular * spec;// * vec3(texture(uMaterial.specular, texCoord));


//     return (ambient + (1.0 - shadow) * (diffuse + specular)) * texture(uMaterial.diffuse, texCoord).rgb;
// }

vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

#ifndef BLINN
    vec3 reflectDir = reflect(-lightDir, normal);
#else
    vec3 reflectDir = normalize(lightDir + viewDir);
#endif

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float shadow = ShadowCalculation(fragPos);
    // float shadow = 0.0;
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

// vec3 calspotlight(spotlight light, vec3 normal, vec3 fragpos, vec3 viewdir)
// {
//     vec3 lightdir = normalize(light.position - fragpos);
//     float theta = dot(lightdir, normalize(-light.direction));
//     if(dot(lightdir, normal) > 0)
//     {
//         if(theta > light.outercutoff)
//         {
//             float diff = max(dot(normal, lightdir), 0.0);
            
// #ifndef blinn
//                 vec3 reflectdir = reflect(-lightdir, normal);
// #else
//                 vec3 reflectdir = normalize(lightdir + viewdir);
// #endif
//             float spec = pow(max(dot(viewdir, reflectdir), 0.0), umaterial.shininess);

//             float distance = length(light.position - fragpos);
//             float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

//             vec3 ambient = light.ambient * vec3(texture(umaterial.diffuse, texcoord));
//             vec3 diffuse = light.diffuse * diff * vec3(texture(umaterial.diffuse, texcoord));
//             vec3 specular = light.specular * spec * vec3(texture(umaterial.specular, texcoord));

//             float epsilon = (light.innercutoff - light.outercutoff);
//             float intensity = smoothstep(0.0, 1.0, (theta - light.outercutoff) / epsilon);
//             // float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0, 1.0);
//             float shadow = 0.0;
//             ambient *= attenuation * intensity;
//             diffuse *= attenuation * intensity * (1.0 - shadow);
//             specular *= attenuation * intensity * (1.0 - shadow);
//             return(ambient + diffuse + specular);
//         }
//         else
//         {
//             return vec3(0.0, 0.0, 0.0); 
//         }
//     }
//     else
//     {
//         return vec3(0, 0, 0); 
//     }
// }