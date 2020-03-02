uniform samplerCube cubeMap;
//uniform sampler2D texture0;   //diffuse map
uniform sampler2D normalMap;   //normal map
varying vec3 normal;
varying vec3 incident;

void main() 
{
vec3 normalVec = normalize(normal);
vec3 incidentVec = normalize(incident);

// Calculate reflection color
vec3 reflectColor = textureCube(cubeMap, reflect(incidentVec, normalVec)).xyz;
// Extract the normal from the normal map
vec3 normal = normalize(texture2D(normalMap, gl_TexCoord[0].st).rgb * 2.0 - 1.0);

// Determine where the light is positioned (this can be set however you like)
vec3 light_pos = normalize(vec3(1.0, 1.0, 1.5));

// Calculate the lighting diffuse value
float diffuse = max(dot(normal, light_pos), 0.0);
vec3 color = diffuse * reflectColor;//texture2D(texture0, gl_TexCoord[0].st).rgb;

// Set the output color of our current pixel
gl_FragColor = vec4(color, 1.0);
}





