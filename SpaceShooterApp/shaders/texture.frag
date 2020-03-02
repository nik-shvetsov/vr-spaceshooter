varying vec4 texturecoord;
uniform sampler2D texture0;
uniform sampler2D texture1;


void main()
{
    gl_FragColor = 0.5f*(texture2D(texture0,texturecoord.xy)+texture2D(texture1,texturecoord.xy));
}
