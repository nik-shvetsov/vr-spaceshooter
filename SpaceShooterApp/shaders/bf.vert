varying vec4 texCoord;
uniform sampler2D heightMap;

void main()
{
  texCoord = gl_MultiTexCoord0;
  vec4 pos = gl_Vertex ;
  pos.y = vec4(texture2D(heightMap, gl_MultiTexCoord0.xy)).x * 100.0f;
  gl_Position = gl_ModelViewProjectionMatrix * pos;
}