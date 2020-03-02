varying vec4 texturecoord;
uniform sampler2D texture0;

void main(){
    gl_FragColor = texture2D(texture0,texturecoord.xy);
}
