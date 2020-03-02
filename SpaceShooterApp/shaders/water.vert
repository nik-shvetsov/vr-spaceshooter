uniform vec4 camPos;
uniform float waveTime;
varying vec3 normal;
varying vec3 incident;

float waveWidth = 1.5;
float waveHeight = 1.0;

void main() 
{
gl_TexCoord[0] = gl_MultiTexCoord0;
vec4 position = gl_Vertex;
position.y = sin(waveWidth * position.x + waveTime) * cos(waveWidth * position.z + waveTime) * waveHeight;
//position.z = cos(waveTime*100.0)/(waveWidth * position.x + waveTime) * (waveWidth * position.y + waveTime) * waveHeight;
position.y += 2.5;
normal = gl_Normal;
incident = normalize(position.xyz - camPos.xyz);
gl_Position = gl_ModelViewProjectionMatrix * position;
}