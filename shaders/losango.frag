// shaders/losango.frag
#version 120

// Uniforms (Parâmetros enviados do C++)
uniform float uTime;
uniform float uSpeed;       
uniform float uLineWidth;   
uniform vec4 uLineColor; // Cor da linha (Ciano Brilhante)
uniform float uPauseDuration; 
uniform float uOffset;      

varying vec3 vPosition; 

void main() {
    // 1. Definições e Coordenadas
    // Normaliza vPosition para o tamanho do losango (1.5f), usando Y e X
    vec2 position_uv = vPosition.yx / 0.75; 
    
    // 2. Lógica de Tempo e Linha
    float cycle_duration = uOffset + uPauseDuration;
    float adjusted_time = mod(uTime * uSpeed, cycle_duration);
    
    float line_position;
    if (adjusted_time <= uOffset) {
        line_position = uOffset - adjusted_time; 
    } else {
        line_position = -uLineWidth * 2.0; 
    }
    
    // 3. Cálculo da Diagonal
    vec2 rotated_uv = vec2(position_uv.x + position_uv.y, position_uv.y - position_uv.x) * 0.5;
    float dist = abs(rotated_uv.x - line_position);
    
    // 4. Intensidade da Linha (Suavização)
    float line_intensity = smoothstep(uLineWidth, 0.0, dist);
    
    // 5. Cor Final
    
    // --- Gradiente de Cores no Fundo ---
    
    // Normaliza a posição Y para o fator de mistura entre 0.0 e 1.0
    float mix_factor = (vPosition.y / 0.75) * 0.5 + 0.5; 
    
    // Cores de Base
    vec3 color_blue = vec3(0.0, 0.15, 0.3);       // Azul escuro (topo)
    // R: 0.5 (forte), G: 0.0 (nulo), B: 0.35 (suficiente para roxo)
    vec3 color_maroon = vec3(0.5, 0.0, 0.35); // Mais Vermelho/Magenta (base)
    
    // Mistura as duas cores base: Magenta na base, Azul no topo
    vec3 base_color_rgb = mix(color_maroon, color_blue, mix_factor); 
    
    // Aumenta o brilho geral da cor de fundo (Emissão)
    base_color_rgb *= 1.2; 
    
    vec4 base_color = vec4(base_color_rgb, 1.0);
    // -----------------------------------------
    
    // Mistura o fundo colorido (gradiente) com a cor brilhante da linha (scanline)
    vec3 final_color = mix(base_color.rgb, uLineColor.rgb, line_intensity * uLineColor.a);
    
    gl_FragColor = vec4(final_color, base_color.a);
}