#shader vertex
/// Phong Vertex shader.
#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;

out vec3 vertNormal;
out vec3 lightDir;
out vec3 eyeDir; 
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main() {
	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	lightDir = normalize(lightPos - vertPos); /// Create the light direction. I do the math with in class 
	
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex; 
}

#shader fragment
/// Phong fragment shader.
#version 410
in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;
out vec4 fragColor;

void main() {
	const vec4 ks = vec4(0.6, 0.6, 0.6, 0.0);
	const vec4 kd = vec4(0.6, 0.6, 0.6, 0.0); /// const means it cannot be changed just like C++
	const vec4 ka = 0.1 * kd;
	
	float diff = max(dot(vertNormal, lightDir), 0.0);
	/// Reflection is based incedent which means a vector from the light source
	/// not the direction to the light source
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float spec = max(dot(eyeDir, reflection), 0.0);
	if(diff > 0.0){
		spec = pow(spec,14.0);
	}
	fragColor =  ka + (diff * kd) + (spec * ks);
} 