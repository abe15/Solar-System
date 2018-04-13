#version 330 core


layout (location = 0) in vec3 position;



//uniform mat4 projection;
//uniform mat4 modelview;
//uniform mat4 model;




void main()
{   
   // gl_Position = projection * modelview * vec4(position.x, position.y, position.z, 1.0); 
	  gl_Position = vec4(position, 1.0);

}
