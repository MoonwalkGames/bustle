#version 330 core

//Vertex attributes
in vec4 vPosition;
in vec3 vNormal;
in vec2 vUV;

//Product of the material and light elements
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

//Matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Other light values
uniform vec4 LightPosition;
uniform float Shininess;

//Values to be passed to the fragment shader
out vec4 lightColor; //Final sum of the light components
out vec2 UV; //The UV coord

void main()
{
	//Create the combined model view matrix
	mat4 model_view = view * model;

	//Get vertex position in eye coordinates
	vec3 pos = (model_view * vPosition).xyz; //The position of the vertex after it has been transformed by the model view, not the projection

	//Get vector from point (in eye coordinates) to the light
	vec3 L = normalize(LightPosition.xyz - pos);
	
	//Get vector pointing to the eye (eye is now the origin)
	vec3 E = normalize(-pos);

	//Calculate the halfway vector
	vec3 H = normalize(L + E);

	/* ----- Calculate the light components ----- */
	//Calculate the ambient component
	vec4 ambient = AmbientProduct;
	
	//Convert the normal into eye-coordinates (ie: after model & view but before projection)
	vec3 N = normalize(model_view * vec4(vNormal, 0.0f)).xyz;  //Need to convert vNormal to a vec4 so we can multiply it by the 4x4 model_view matrix

	//Calculate the diffuse component
	float diffuseIntensity = max(dot(L, N), 0); //AKA Kd...max returns whatever value is higher so we ensure we don't get negative light, we get 0 instead
	vec4 diffuse = DiffuseProduct * diffuseIntensity;

	//Calculate the specular component
	float specularIntensity = pow(max(dot(N, H), 0.0f), Shininess); //The cosine of the angle between N and H, once again prevented from being negative. Also to the power of the shininess co-efficient we passed in earlier
	vec4 specular = SpecularProduct * specularIntensity;
	/* ----- Calculate the light components ----- */

	//Transform the vertex to its final position in world space
	gl_Position = projection * model_view * vPosition;

	//Pass the light colour to the fragment shader
	lightColor = ambient + diffuse + specular;
	lightColor.a = 1.0f; //Ensure the alpha component is set to 1

	//Pass the UV onto the fragment shader
	UV = vUV;
}

///*
//	Vertex Shader

//	Uses GL's MVP stack to transform the incoming vertex.
//*/

//#version 330
//layout(location = 4) in vec3 vPos;
//layout(location = 5) in vec2 texture;
//layout(location = 6) in vec3 normal;
//layout(location = 7) in vec3 color;
//layout(location = 8) in vec3 vEnd;

//out vec3 normal0;
//out vec2 texCoord;
//out vec3 color0;

////lighting outs
//out vec3 lightDirection;

//uniform mat4 mvm; // modelview matrix
//uniform mat4 prm; // projection matrix

//uniform mat4 localTransform;

//uniform vec3 lightPosition;

//uniform float timeStep;

//void main()
//{
//	color0 = color;
//	normal0 = mat3(mvm) * mat3(localTransform) * normal;
//	texCoord = texture;

//	vec3 pos = mix(vPos, vEnd, timeStep);

//	vec4 localSpace = localTransform * vec4(pos, 1.0);
//	vec4 modelViewSpace = mvm * localSpace;
//	vec4 worldSpace = prm * modelViewSpace;

//	lightDirection = normalize(lightPosition - modelViewSpace.xyz);

//	gl_Position = worldSpace;	//every vert shader must set gl_Position
//}



