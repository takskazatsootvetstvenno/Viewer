 #version 460
 layout(location = 0) in vec3 vertex_position; 
 layout(location = 1) in vec3 vertex_normal;
 layout(location = 2) in vec2 texture_coords; 

  layout(location = 0) out vec3 out_vertex_pos; 
  layout(location = 1) out vec3 out_vertex_normal; 
  layout(location = 2) out vec2 out_texture_coords; 

 layout(std140) uniform GlobalMatrices
{
    mat4 ProjMatrix;
    mat4 ViewMatrix;
    mat4 ModelMatrix;
};

 void main() { 
    out_vertex_pos = vertex_position;
    out_vertex_normal = vertex_normal;
    out_texture_coords = texture_coords;
    gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.0);
 } ;