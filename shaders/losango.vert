// shaders/losango.vert
#version 120 

varying vec3 vPosition; // Passa a posição local do vértice para o Fragment Shader
    
void main()
{
    // Passa a posição local do vértice (X, Y, Z)
    vPosition = gl_Vertex.xyz; 
    
    // Projeta a posição (sem distorção)
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}