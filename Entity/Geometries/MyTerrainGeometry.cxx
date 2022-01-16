#include "MyTerrainGeometry.hxx"
#include <stdio.h>
#include <glm/detail/compute_vector_relational.hpp>
float MyTerrainGeometry::noise_value(const glm::vec3 &v) const
{
    float xx = v[0] * glm::sqrt(50.0f * v[0]);
    float zz = v[2] * glm::sqrt(50.0f * v[2]);
    float noise = 0.5f * glm::perlin(glm::vec2(xx * 0.1f, zz * 0.1f));
    for (uint8_t i = 4; i < 10; ++i)
    {
        noise += (1.0f / (float)i) * noise * glm::perlin(glm::vec2(xx * 0.005, zz * 0.005));
    }
    return noise;
}

float MyTerrainGeometry::get_y(const float &x, const float &z) const
{
    int32_t x_floor = (int32_t)x;
    int32_t z_floor = (int32_t)z;

    float x_remain = x - (float)x_floor;
    float z_remain = z - (float)z_floor;

    if (x_floor < 0 || x_floor > width - 1) return 0.0f;
    if (z_floor < 0 || z_floor > depth - 1) return 0.0f;
    

    float floor_height =  terrain_ys[x_floor * depth + z_floor];
    float ceiling_height =  terrain_ys[(x_floor + 1) * depth + z_floor + 1];

    float left_fw_height = terrain_ys[x_floor * depth + z_floor + 1];

    float right_height =  terrain_ys[(x_floor + 1) * depth + z_floor];

    float temp1, temp2;

    temp1 = x_remain * right_height + (1 - x_remain) * floor_height;
    temp2 = (x_remain) * ceiling_height + (1 - x_remain) * left_fw_height;

    float est_height = z_remain * temp2 + (1 - z_remain) * temp1;
    return est_height;
    
}

MyTerrainGeometry::MyTerrainGeometry(uint32_t w, uint32_t h, uint32_t d): Geometry(), width(w), height(h), depth(d)
{
    const uint8_t count_vert_attr = 11;
    const uint32_t count_vertices = width * depth;
    const uint32_t count_faces = (width - 1) * (depth - 1) * 6;

    float *vertices = new float[count_vertices * count_vert_attr];
    terrain_ys = new float[count_vertices];

    uint32_t *faces = new uint32_t[count_faces];

    // Walking pointers
    float *current_vertex = vertices;
    float *current_y = terrain_ys;

    for (uint32_t r = 0; r < width; ++r)
    for (uint32_t c = 0; c < depth; ++c)
    {
        
        float noise = noise_value(glm::vec3((float)r, 0, (float)c));

        *current_y++ = height * noise;      

        *current_vertex++ = (float)r;
        *current_vertex++ = height * noise_value(glm::vec3((float)r, 0.0f, (float)c));
        *current_vertex++ = (float)c;

        *current_vertex++ = 0.0f;
        *current_vertex++ = 0.0f;
        *current_vertex++ = 0.0f;


        *current_vertex++ = 0.1f - noise * 0.25f;
        *current_vertex++ = 0.1f - noise * 0.1f;
        *current_vertex++ = 0.2f + noise;

        *current_vertex++ = ((float)r) / width;
        *current_vertex++ = ((float)c) / depth;
    }

    for (uint32_t x = 0; x < width; ++x)
    {
        for (uint32_t y = 0; y < depth; ++y)
        {
            uint8_t count_used_vert = 0;
            float *curr_vert = vertices + (11 * (x * depth + y));
            glm::vec3 normal(0.0f, 0.0f, 0.0f); // Contains averaged sum of all the normals in different planes the vertex is associated with

            if (x != 0) { // If there is a left side vertex, it definitely shapes a triangle with it. So we should consider it.
                float *vert_left = vertices + (11 * ((x - 1) * depth + y));
                glm::vec3 calced = glm::cross(glm::vec3(curr_vert[0], curr_vert[1], curr_vert[2]), glm::vec3(vert_left[0], vert_left[1], vert_left[2]));
                normal += calced;
                ++count_used_vert;
            }
            if (x != width - 1) {  // If there is a right side vertex, it definitely shapes a triangle with it. So we should consider it.
                float *vert_right = vertices + (11 * ((x + 1) * depth + y));
                glm::vec3 calced = glm::cross(glm::vec3(curr_vert[0], curr_vert[1], curr_vert[2]), glm::vec3(vert_right[0], vert_right[1], vert_right[2]));
                normal += calced;
                ++count_used_vert;
            }
            if (y != 0) { // If there is a vertex above this vertex, it creates triangle with it.
                float *vert_up = vertices + (11 * (x * depth + y - 1));
                glm::vec3 calced = glm::cross(glm::vec3(curr_vert[0], curr_vert[1], curr_vert[2]), glm::vec3(vert_up[0], vert_up[1], vert_up[2]));
                normal += calced;
                ++count_used_vert;
            }
            if (y != depth - 1) { // If there is a vertex below this vertex, it creates triangle with it
                float *vert_down = vertices + (11 * (x * depth + y + 1));
                glm::vec3 calced = glm::cross(glm::vec3(curr_vert[0], curr_vert[1], curr_vert[2]), glm::vec3(vert_down[0], vert_down[1], vert_down[2]));
                normal += calced;
                ++count_used_vert;
            }
            normal = normal * (1.0f / count_used_vert);
            normal = glm::normalize(normal); // Averaging and normalizing

            // Setting the normal values
            curr_vert[3] = normal.x;
            curr_vert[4] = normal.y;
            curr_vert[5] = normal.z;
        }
    }

    uint32_t *current_index = &faces[0];
    for (uint32_t r = 0; r < width - 1; ++r)
        for (uint32_t c = 0; c < depth - 1; ++c)
        { // NOTE: r * col_vertices + c === index of position[r][c]
            *current_index++ = r * depth + c;
            *current_index++ = (r + 1) * depth + c;
            *current_index++ = r * depth + c + 1;
            *current_index++ = (r + 1) * depth + c;
            *current_index++ = (r + 1) * depth + c + 1;
            *current_index++ = r * depth + c + 1;
        }
    load_vbo(vertices, count_vertices * count_vert_attr);
    load_ebo(faces, count_faces);
    set_size(count_faces);
    delete[] vertices;
    delete[] faces;
}

MyTerrainGeometry::~MyTerrainGeometry()
{
    delete[] terrain_ys;
}


float MyTerrainGeometry::max_x() const
{
    return width;
}

float MyTerrainGeometry::max_z() const
{
    return depth;
}