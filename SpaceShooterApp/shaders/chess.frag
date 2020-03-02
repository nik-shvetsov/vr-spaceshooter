varying vec2 texc;

void main(void)
{   
	vec2 position = gl_FragCoord.xy;
	int x = int(position.x)/10;
	int y = int(position.y)/10;
	int xy = x + y;
	if /*(xy%2 == 0)*/   ((xy - ((xy / 2) * 2)) == 0) 
	{
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0 );
	} 
	else 
	{
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0 );
	}
}



