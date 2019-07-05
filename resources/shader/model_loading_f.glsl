#version 330 core
out vec4 FragColor;

const int MaxLights = 50; // maximum possible lights this shader supports
const int TextureNum = 5;
//Light Properties
struct Light {
    vec3 position;
    vec3 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;       
	float cutOff;
    float outerCutOff; 	
	int lightType;
	int fallOff;
};

// represents material properties of the surface passed by the application
struct Material {
  vec4 ambient; 
  vec4 diffuse; 
  vec4 specular;
  float shininess;

  vec4 emmisive;
  float constant; //c1
  float linear; //c2
  float quadratic; //c3
  int modelType;
};

//
in vec3 Normal;  
in vec3 FragPos; 
uniform vec3 viewPos;
uniform Light Lights[MaxLights]; // support UP TO 8 lights
uniform int lightNumber;
//
in vec2 TexCoords;

uniform vec4 texNum;
uniform sampler2D texture_normal[TextureNum];
uniform sampler2D texture_height[TextureNum];
uniform sampler2D texture_diffuse[TextureNum];
uniform sampler2D texture_specular[TextureNum];
uniform Material mat;

vec4 texNumber;

vec4 ComputePhongLight(Light light, vec3 normal, vec3 fragPos);

void main()
{
	vec4 result = vec4(0.f,0.f,0.f, 1.f);
	vec3 N = normalize(Normal);
	texNumber = texNum;
	for(int i = 0; i < lightNumber; ++i)
	{
		if(mat.modelType == 0) // Model is Normal
		{
			//result = vec4(1.f, 1.f, 1.f, 1.f);
			result += ComputePhongLight(Lights[i], N, FragPos);
			//result = texture(texture_diffuse[0], TexCoords);
		}
		else if(mat.modelType == 7) // if Model is Particle
		{
			
		}
		else if(mat.modelType == 6) // if Model is Light
			result = mat.diffuse;
		else //Model is declared figures : sphere, cone, cylinder, plane, cube
		{
			texNumber = vec4(0,0,0,0);
			vec4 temp = ComputePhongLight(Lights[i], N, FragPos);
			//if(temp.a < 0.1)
			//	discard;
			result += temp;
		}
	}
	FragColor = result;
}

vec4 ComputePhongLight(Light light, vec3 normal, vec3 fragPos)
{
	vec3 N = normal;
    vec3 V = normalize(viewPos - FragPos);
	vec3 L;
	if(light.lightType == 0) // Direction
		L = normalize(-light.direction);
	else // Point, Spot
		L = normalize(light.position - fragPos);
	vec3 R = 2.0 * dot(L, N) * N - L;
	
	vec4 ambient = vec4(0,0,0, 1);
	vec4 diffuse = vec4(0,0,0, 1);
	vec4 specular = vec4(0,0,0, 1);
	float diff = max(dot(L, N), 0);
	float spec = pow(max(dot(R, V), 0), mat.shininess);
	
	if(texNumber.x > 0)//diffuse
	{
		//texture(texture_diffuse[0], TexCoords)
		ambient = light.ambient * texture(texture_diffuse[0], TexCoords);
		diffuse = light.diffuse * diff * texture(texture_diffuse[0], TexCoords);
		//texNumber.x--;
	}
	else
	{
		ambient = light.ambient * mat.ambient;
		diffuse = light.diffuse * mat.diffuse * diff;
	}
	if(texNumber.y > 0)//specular
	{
		specular = diff * light.specular *  spec * texture(texture_specular[0], TexCoords);
		//texNumber.y--;
	}
	else
		specular = diff * light.specular * mat.specular * spec;
		
	if(texNumber.z > 0)//normal
	{}
	if(texNumber.w > 0)//height
	{}
	
	if(light.lightType == 0) // Direction
		return (ambient + diffuse + specular);
		
    float d = length(light.position - fragPos);
    float att = min(1.0, (1.0 / (mat.constant + mat.linear * d + mat.quadratic * (d * d))));
	
	if(light.lightType == 1) // Point
		return att * (ambient + diffuse + specular);
	
	float theta = dot(L, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	float spotlightEffect = pow((cos(theta)-cos(light.outerCutOff))/(cos(light.cutOff)-cos(light.outerCutOff)), light.fallOff);
	
	ambient *= att * intensity * spotlightEffect;
    diffuse *= att * intensity * spotlightEffect;
    specular *= att * intensity * spotlightEffect;
	
	if(light.lightType == 2) // Spot
		return (ambient + diffuse + specular);
}

