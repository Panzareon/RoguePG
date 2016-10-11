uniform sampler2D texture;
uniform float frameId;
uniform float numberFrames;

void main()
{
	gl_TexCoord[0].x += frameId / numberFrames;
	
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}