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
uniform bool FlashLightOff = true;
uniform bool Foggy = false;
uniform vec4 uColor;
uniform sampler2D uShadowMap;
uniform sampler2D uLightMap;
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

float DirShadowCalculation(vec4 fragPosLightSpace);

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);

float near = 4.5;
float far = 10.0;
float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float steepness = 0.5;
float offset = 5.0;
float logisticDepth(float depth)
{
    float zValue = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zValue - offset))));
}

void main()
{
    if(HaveTex)
    {
        vec3 result = vec3(0.0, 0.0, 0.0);

        vec3 norm = vec3(0.0, 0.0, 0.0);

        if(HaveNormal != true)
        {
            norm = normalize(Normal);
        }
        else
        {
            norm = texture(uMaterial.normalmap, texCoord).rgb;
            norm = norm * 2.0 - 1.0;
            norm = normalize(TBN * norm);
            if(!gl_FrontFacing)
            {
                norm = norm * -1.0;
            }
        }

        vec3 viewDir = normalize(uViewPos - FragPos);

        float depth = logisticDepth(gl_FragCoord.z);

        if(HaveDirLight)
            result = CalDirLight(uDirLight, norm, viewDir);

        if(HavePointLight)
            for(int i = 0; i < uPointLightNum; i++)
                result += CalPointLight(uPointLight[i], norm, FragPos, viewDir);

        if(HaveSpotLight)
            for(int i = 0; i < uSpotLightNum; i++)
                result += CalSpotLight(uSpotLight[i], norm, FragPos, viewDir);

        if(texture(uMaterial.diffuse, texCoord).a < 0.1)
            discard;

        if(Foggy)
        {
            vec3 FinalResult = texture2D(uMaterial.diffuse, texCoord).rgb * result * (1.0 - depth) + vec3(depth * vec3(0.85, 0.85, 0.9));
            FragColor = vec4(FinalResult, texture2D(uMaterial.diffuse, texCoord).a);
        }
        else
        {
            FragColor = texture2D(uMaterial.diffuse, texCoord) * vec4(result, 1.0);
        }
        // else
        // FragColor = (texture2D(uMaterial.diffuse, texCoord) + vec4(texture2D(uLightMap, texCoord).rgb, 1.0)) * vec4(result, 1.0);
        // FragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z) / far), 1.0);
    }
    else
    {
        FragColor = uColor;
    }
}

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - uPointLight[0].position;

    float currentDepth = length(fragToLight);


    float bias = 0.15;
    float shadow = 0.0;
    int samples  = 20;
    float viewDistance = length(uViewPos - fragPos);
    float diskRadius = (1.0  + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closesDepth = texture(depthMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
        closesDepth *= far_plane;
        if(currentDepth - bias > closesDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    return shadow;
}

float DirShadowCalculation(vec4 fragPosLightSpace)
{

    float shadow = 0.0;
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closesDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(uDirLight.position - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    vec2 pixelSize = 1.0 / textureSize(uShadowMap, 0);

    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * pixelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

#ifndef BLINN
    vec3 reflectDir = reflect(-lightDir, normal);
#else
    vec3 reflectDir = normalize(lightDir + viewDir);
#endif

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    // float shadow = ShadowCalculation(fragPosLight);
    float shadow = 0.0;
    vec3 ambient = light.ambient;// * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff;// * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 specular = light.specular * spec;// * vec3(texture(uMaterial.specular, texCoord));


    return (ambient + (1.0 - shadow) * (diffuse + specular));// * texture(uMaterial.diffuse, texCoord).rgb;
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

#ifndef BLINN
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(normal, reflectDir), 0.0), uMaterial.shininess);
#else
    vec3 reflectDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, reflectDir), 0.0), uMaterial.shininess);
#endif


    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float shadow = 0.0;

    shadow = ShadowCalculation(fragPos);
    vec3 ambient = light.ambient;// * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff;// * vec3(texture(uMaterial.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if(dot(normal, lightDir) > 0)
    {
        if(theta > light.outerCutOff)
        {
            float diff = max(dot(normal, lightDir), 0.0);

#ifndef BLINN
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(normal, reflectDir), 0.0), uMaterial.shininess);
#else
    vec3 reflectDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, reflectDir), 0.0), uMaterial.shininess);
#endif

            float distance =  length(light.position - fragPos);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            vec3 ambient = light.ambient;// * vec3(texture(uMaterial.diffuse, texCoord));
            vec3 diffuse = light.diffuse * diff;// * vec3(texture(uMaterial.diffuse, texCoord));
            vec3 specular;
            if(FlashLightOff)
            {
                specular = light.specular * spec * vec3(texture(uMaterial.specular, texCoord));
            }
            else
            {
                specular = light.specular * spec * vec3(texture(uMaterial.specular, texCoord)) + vec3(texture2D(uLightMap, texCoord).rgb);
            }

            float epsilon = light.innerCutOff - light.outerCutOff;
            float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);

            ambient *= attenuation * intensity;
            diffuse *= attenuation * intensity;
            specular *= attenuation * intensity;

            return (ambient + diffuse + specular);
        }
        else
        {
            return vec3(0.0, 0.0, 0.0);
        }
    }
    else
    {
        return vec3(0.0, 0.0, 0.0);
    }
}