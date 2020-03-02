varying vec4 texturecoord;
uniform sampler2D heightmap;

void main(){
    texturecoord = gl_MultiTexCoord0;
    vec4 pos = gl_Vertex;
    pos.y = texture2D(heightmap,texturecoord)*30;
    pos.y -= 2.5;
    gl_Position = gl_ModelViewProjectionMatrix*pos;
}
