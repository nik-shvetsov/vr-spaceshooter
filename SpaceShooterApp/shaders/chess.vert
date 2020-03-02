varying vec2 texc;

void main(void)
{
    vec2 texc = vec2(gl_Vertex);
	gl_Position     = ftransform();
}