#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "SDL2/SDL.h"
#include "main.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 640

#undef main

 bool running = true;

void sdl_error(const char *msg)
{
    printf("%s : %s\n", msg, SDL_GetError());
    exit(1);
}

void draw_pixel(SDL_Renderer *renderer, i32 x, i32 y, i32 color)
{
    u8 a = (color >> 24) & 0xFF;
    u8 r = (color >> 16) & 0xFF;
    u8 g = (color >>  8) & 0xFF;
    u8 b = (color >>  0) & 0xFF;
    
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

#if 0
void transform_point(v2 *a)
{
    a->x = a->x*WINDOW_WIDTH/2 + WINDOW_WIDTH/2;
    a->y = -a->y*WINDOW_HEIGHT/2 + WINDOW_HEIGHT/2;
}

void draw_line(SDL_Renderer *renderer, 
               v2 p0, v2 p1, v4 color)
{
    transform_point(&p0);
    transform_point(&p1);
    u32 color32 = ((((u32)round(color.a*255.0f)) << 24) |
                   (((u32)round(color.r*255.0f)) << 16) |
                   (((u32)round(color.g*255.0f)) << 8) |
                   (((u32)round(color.b*255.0f)) << 0));
    
    r32 dx = fabs(p0.x - p1.x);
    r32 dy = fabs(p0.y - p1.y);
    v2 min = p0;
    v2 max = p1;
    if(dx >= dy) {
        if(p0.x > p1.x) {
            min = p1;
            max = p0;
        }
        r32 y = min.y;
        r32 slope = (max.y-min.y)/(max.x-min.x);
        for(r32 x = min.x; x < max.x; x++, y+=slope) {
            draw_pixel(renderer, (i32)x, (i32)y, color32);
        }
    }
    else {
        if(p0.y > p1.y) {
            min = p1;
            max = p0;
        }
        r32 x = min.x;
        r32 slope = (max.x-min.x)/(max.y-min.y);
        for(r32 y = min.y; y < max.y; y++, x+=slope) {
            draw_pixel(renderer, (i32)x, (i32)y, color32);
        }
    }
}
#endif

v2i get_min_max(i32 p0, i32 p1, i32 p2)
{
    if(p0 > p1) { swap(p0, p1); }
    if(p0 > p2) { swap(p0, p2); }
    if(p1 > p2) { swap(p1, p2); }
    return V2i(p0, p2);
}

 r32 edge_test(v2i p0, v2i p1, v2i p3)
{
    v2i p = p3 - p0;
    v2i edge = p1 - p0;
    return (r32) cross(p, edge);
}

void draw_triangle(SDL_Renderer *renderer, 
                   v2i p0, v2i p1, v2i p2, 
                   v4 p0_col, v4 p1_col, v4 p2_col)
{
    v2i min_max_y = get_min_max(p0.y, p1.y, p2.y);
    v2i min_max_x = get_min_max(p0.x, p1.x, p2.x);
    i32 min_y = min_max_y.e[0];
    i32 max_y = min_max_y.e[1];
    i32 min_x = min_max_x.e[0];
    i32 max_x = min_max_x.e[1];

    r32 triangle_area = edge_test(p0, p1, p2);

    for(i32 y = min_y; y <= max_y; y++) 
    {
        for(i32 x = min_x; x <= max_x; x++) 
        {
            v2i test_p = V2i(x, y);
            r32 weight0 = edge_test(p1, p2, test_p);
            r32 weight1 = edge_test(p2, p0, test_p);
            r32 weight2 = edge_test(p0, p1, test_p);
            
            if((weight0 >= 0) && (weight1 >= 0) && (weight2 >= 0)) 
            {
                weight0 = weight0 / triangle_area;
                weight1 = weight1 / triangle_area;
                weight2 = weight2 / triangle_area;
                r32 a = weight0*p0_col.a + weight1*p1_col.a + weight2*p2_col.a;
                r32 r = weight0*p0_col.r + weight1*p1_col.r + weight2*p2_col.r;
                r32 g = weight0*p0_col.g + weight1*p1_col.g + weight2*p2_col.g;
                r32 b = weight0*p0_col.b + weight1*p1_col.b + weight2*p2_col.b;
                u32 color32 = ((((u32)(a*255.0f)) << 24) |
                             (((u32)(r*255.0f)) << 16) |
                             (((u32)(g*255.0f)) <<  8) |
                             (((u32)(b*255.0f)) <<  0));
                
                draw_pixel(renderer, x, y, color32);
            }
        }
    }
}

v2i map_to_screen(v2 p)
{
    i32 x = (i32) (p.x*WINDOW_WIDTH/2.0f + WINDOW_WIDTH/2.0f);
    i32 y = (i32) (-p.y*WINDOW_HEIGHT/2.0f + WINDOW_HEIGHT/2.0f);
    return V2i(x, y);
}

void draw_model(SDL_Renderer *renderer, model *model)
{
    v4 colors[] = {
        V4(0.4f, 0.3f, 0.6f, 1.0f),
        V4(0.5f, 0.2f, 0.3f, 1.0f),
        V4(0.3f, 0.7f, 0.4f, 1.0f),
        V4(0.5f, 0.3f, 0.2f, 1.0f),
        V4(1.0f, 0.0f, 0.0f, 1.0f),
        V4(0.0f, 1.0f, 0.0f, 1.0f),
        V4(0.0f, 0.0f, 1.0f, 1.0f),
        V4(1.0f, 1.0f, 0.0f, 1.0f),
        V4(0.0f, 1.0f, 1.0f, 1.0f),
        V4(0.6f, 0.7f, 0.1f, 1.0f),
        V4(0.3f, 0.7f, 0.9f, 1.0f),
        V4(0.2f, 0.2f, 0.8f, 1.0f),
    };
    v4 red = colors[4];
    v4 green = colors[5];
    v4 blue = colors[6];
    
    i32 color_index = 0;
    for(u32 i = 0; i < model->nr_indices; i+=3) {
        u32 vertex_index0 = model->indices[i];
        u32 vertex_index1 = model->indices[i+1];
        u32 vertex_index2 = model->indices[i+2];
        v3 p0 = model->vertices[vertex_index0] + model->origin;
        v3 p1 = model->vertices[vertex_index1] + model->origin;
        v3 p2 = model->vertices[vertex_index2] + model->origin;
        
        v3 normal = cross(p1 - p0, p2 - p0);
        bool culling = dot(p0, normal) >= 0.0f;
        
        if(!culling) {
            v4 color = colors[color_index];
            v2 projected_p0 = V2(p0.x/-p0.z, p0.y/-p0.z);
            v2 projected_p1 = V2(p1.x/-p1.z, p1.y/-p1.z);
            v2 projected_p2 = V2(p2.x/-p2.z, p2.y/-p2.z);
            
            #if 0
            draw_triangle(
                renderer, 
                map_to_screen(projected_p0),
                map_to_screen(projected_p1), 
                map_to_screen(projected_p2),
                color
                          );
            #endif
        }
        color_index++;
    }
}

void transform_model(model *model, m3x3 transform)
{
    for(u32 i = 0; i < model->nr_vertices; i++) {
        v3 p = model->vertices[i];
        model->vertices[i] = transform*p;
    }
}

model make_cube(v3 origin, r32 radius, v4 color)
{
    model result = {};
    result.color = color;
    result.origin = origin;
    result.nr_vertices = 8;
    result.vertices[0] = V3(-radius, -radius, radius);
    result.vertices[1] = V3(radius, -radius, radius);
    result.vertices[2] = V3(-radius, radius, radius);
    result.vertices[3] = V3(radius, radius, radius);
    result.vertices[4] = V3(-radius, -radius, -radius);
    result.vertices[5] = V3(radius, -radius, -radius);
    result.vertices[6] = V3(-radius, radius, -radius);
    result.vertices[7] = V3(radius, radius, -radius);
    
    result.nr_indices = 36;
    result.indices[0] = 0; result.indices[1] = 1; result.indices[2] = 2;
    result.indices[3] = 1; result.indices[4] = 3; result.indices[5] = 2;
    
    result.indices[6]  = 1; result.indices[7]  = 5; result.indices[8]  = 3;
    result.indices[9]  = 5; result.indices[10] = 7; result.indices[11] = 3;
    
    result.indices[12] = 7; result.indices[13] = 6; result.indices[14] = 3;
    result.indices[15] = 6; result.indices[16] = 2; result.indices[17] = 3;
    
    result.indices[18] = 0; result.indices[19] = 2; result.indices[20] = 4;
    result.indices[21] = 2; result.indices[22] = 6; result.indices[23] = 4;
    
    result.indices[24] = 4; result.indices[25] = 6; result.indices[26] = 5;
    result.indices[27] = 6; result.indices[28] = 7; result.indices[29] = 5;
    
    result.indices[30] = 0; result.indices[31] = 4; result.indices[32] = 1;
    result.indices[33] = 1; result.indices[34] = 4; result.indices[35] = 5;
    
    return result;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = 0;
    SDL_Renderer *renderer = 0;
    
    if(SDL_Init(SDL_INIT_VIDEO)) {
        sdl_error("Could not initialize SDL");
    }
    window = SDL_CreateWindow("3D Renderer",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(!window) {
        sdl_error("Could not create window");
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(!renderer) {
        sdl_error("Could not create renderer");
    }
    
    v4 color = V4(1.0f, 0.0f, 0.0f, 1.0f);
    model square = make_cube(V3(0.0f, 0.0f, -2.0f), 0.5f, color);
    
    while(running) {
        SDL_Event e;
        if(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                {
                running = false;
                } break;
                
                case SDL_KEYDOWN:
                {
                    r32 angle = (r32)(pi/100);
                    switch(e.key.keysym.scancode) {
                        case SDL_SCANCODE_S:
                        transform_model(&square, xrotation_m3x3(angle));
                        break;
                        case SDL_SCANCODE_W:
                        transform_model(&square, xrotation_m3x3(-angle));
                        break;
                        case SDL_SCANCODE_D:
                        transform_model(&square, yrotation_m3x3(angle));
                        break;
                        case SDL_SCANCODE_A:
                        transform_model(&square, yrotation_m3x3(-angle));
                        break;
                        case SDL_SCANCODE_Q:
                        transform_model(&square, zrotation_m3x3(angle));
                        break;
                        case SDL_SCANCODE_E:
                        transform_model(&square, zrotation_m3x3(-angle));
                        break;
                    }
                } break;                
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        // draw_model(renderer, &square);
        v2i p0 = V2i(100, 100);
        v2i p1 = V2i(100, 200);
        v2i p2 = V2i(200, 200);
        v4 p0_col = V4(1.0f, 0.0f, 0.0f, 1.0f);
        v4 p1_col = V4(0.0f, 1.0f, 0.0f, 1.0f);
        v4 p2_col = V4(0.0f, 0.0f, 1.0f, 1.0f);
        draw_triangle(renderer, p0, p1, p2, p0_col, p1_col, p2_col);
        v2i _p0 = V2i(400, 400);
        v2i _p1 = V2i(450, 500);
        v2i _p2 = V2i(500, 400);
        draw_triangle(renderer, _p0, _p1, _p2, p0_col, p1_col, p2_col);
        
        SDL_RenderPresent(renderer);
    }
    
    return 0;
}