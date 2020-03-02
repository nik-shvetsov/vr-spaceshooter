uniform samplerCube skybox;

void main () 
{
	gl_FragColor = textureCube(skybox, gl_TexCoord[0].xyz);
}