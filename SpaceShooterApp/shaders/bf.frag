varying vec4 texCoord;
uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
  vec4 color = texture2D(tex0, texCoord.xy);
  gl_FragColor = 0.5f * color + 0.5f * texture2D(tex1, texCoord.xy);
}