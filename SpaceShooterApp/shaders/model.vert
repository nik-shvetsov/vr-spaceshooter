varying vec4 texturecoord;

void main(){
    texturecoord = gl_MultiTexCoord0;
    vec4 pos = gl_Vertex;

    gl_Position = gl_ModelViewProjectionMatrix*pos;
}
