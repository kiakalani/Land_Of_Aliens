#include "CylinderGeometry.hxx"
#include <stdio.h>
CylinderGeometry::CylinderGeometry(float height, float circle_radius, int num_height_samples, int num_circle_samples): Geometry()
{
	// Create a cylinder

	// Number of vertices and faces to be created
	const GLuint vertex_num = num_height_samples * num_circle_samples + 2; // plus two for top and bottom
	const GLuint face_num = (num_height_samples - 1)* (num_circle_samples) * 2 + 2 * num_circle_samples; // two extra rings worth for top and bottom

																										// Number of attributes for vertices and faces
	const int vertex_att = 11;  // 11 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3), 2D texture coordinates (2)
	const int face_att = 3; // Vertex indices (3)

							// Data buffers for the shape
	// GLfloat *vertex = NULL;
	// GLuint *face = NULL;


	// Allocate memory for buffers
	
	float	*vertex = new float[vertex_num * vertex_att + 2];
	uint32_t	*face = new uint32_t[face_num * face_att + 2];
	

	// Create vertices 
	float theta; // Angle for circle
	float h; // height
	float s, t; // parameters zero to one
	glm::vec3 loop_center;
	glm::vec3 vertex_position;
	glm::vec3 vertex_normal;
	glm::vec3 vertex_color;
	glm::vec2 vertex_coord;

	for (int i = 0; i < num_height_samples; i++) { // along the side

		s = i / (float)num_height_samples; // parameter s (vertical)
		h = (-0.5 + s)*height;
		for (int j = 0; j < num_circle_samples; j++) { // small circle
			t = j / (float)num_circle_samples;
			theta = 2.0*glm::pi<GLfloat>()*t; // circle sample (angle theta)

											  // Define position, normal and color of vertex
			vertex_normal = glm::vec3(cos(theta), 0.0f, sin(theta));
			vertex_position = glm::vec3(cos(theta)*circle_radius, h, sin(theta)*circle_radius);
			vertex_color = glm::vec3(1.0 - s,
				t,
				s);
			vertex_coord = glm::vec2(s, t);

			// Add vectors to the data buffer
			for (int k = 0; k < 3; k++) {
				vertex[(i*num_circle_samples + j)*vertex_att + k] = vertex_position[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 3] = vertex_normal[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 6] = vertex_color[k];
			}
			vertex[(i*num_circle_samples + j)*vertex_att + 9] = vertex_coord[0];
			vertex[(i*num_circle_samples + j)*vertex_att + 10] = vertex_coord[1];
		}
	}

	int topvertex = num_circle_samples * num_height_samples;
	int bottomvertex = num_circle_samples * num_height_samples + 1; // indices for top and bottom vertex

	vertex_position = glm::vec3(0, (-0.5+(num_height_samples-1.0f)/num_height_samples)*height, 0); // location of top middle of cylinder
	vertex_normal = glm::vec3(0, 1, 0);
	vertex_color = glm::vec3(1, 0.6, 0.4);
	vertex_coord = glm::vec2(0, 0); // no good way to texture top and bottom

	for (int k = 0; k < 3; k++) {
		vertex[topvertex*vertex_att + k] = vertex_position[k];
		vertex[topvertex*vertex_att + k + 3] = vertex_normal[k];
		vertex[topvertex*vertex_att + k + 6] = vertex_color[k];
	}
	vertex[(topvertex)*vertex_att + 9] = vertex_coord[0];
	vertex[(topvertex)*vertex_att + 10] = vertex_coord[1];

	//================== bottom vertex
	vertex_position = glm::vec3(0, (-0.5)*height, 0); // location of bottom middle of cylinder
	vertex_normal = glm::vec3(0, -1, 0);
	// leave the color and uv alone

	for (int k = 0; k < 3; k++) {
		vertex[bottomvertex*vertex_att + k] = vertex_position[k];
		vertex[bottomvertex*vertex_att + k + 3] = vertex_normal[k];
		vertex[bottomvertex*vertex_att + k + 6] = vertex_color[k];
	}
	vertex[(bottomvertex)*vertex_att + 9] = vertex_coord[0];
	vertex[(bottomvertex)*vertex_att + 10] = vertex_coord[1];

	//===================== end of vertices

	// Create triangles
	for (int i = 0; i < num_height_samples - 1; i++) {
		for (int j = 0; j < num_circle_samples; j++) {
			// Two triangles per quad
			glm::vec3 t1(((i + 1) % num_height_samples)*num_circle_samples + j,
				i*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + j);
			glm::vec3 t2(((i + 1) % num_height_samples)*num_circle_samples + j,
				((i + 1) % num_height_samples)*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + ((j + 1) % num_circle_samples));
			// Add two triangles to the data buffer
			for (int k = 0; k < 3; k++) {
				face[(i*num_circle_samples + j)*face_att * 2 + k] = (GLuint)t1[k];
				face[(i*num_circle_samples + j)*face_att * 2 + k + face_att] = (GLuint)t2[k];
			}
		}
	}
	int cylbodysize = num_circle_samples * (num_height_samples - 1) * 2; // amount of array filled so far, start adding from here
																		 // triangles for top disc (fan shape)
	int i = num_height_samples - 1;
        printf("STILL FINE\n");

	for (int j = 0; j < num_circle_samples; j++) {
		// Bunch of wedges pointing to the centre
		glm::vec3 topwedge(
			i*num_circle_samples + j,
			topvertex,
			i*num_circle_samples + (j + 1) % num_circle_samples
		);

		// note order reversed so that all triangles point outward
		glm::vec3 botwedge(
			0 + (j + 1) % num_circle_samples,
			bottomvertex,
			0 + j
		);

		// Add the triangles to the data buffer
		for (int k = 0; k < 3; k++) {
			face[(cylbodysize + j)*face_att + k] = (GLuint)topwedge[k];
			face[(cylbodysize + j + num_circle_samples)*face_att + k] = (GLuint)botwedge[k];
		}
	}
    load_vbo(vertex, vertex_num * vertex_att);

    load_ebo(face, face_num * face_att);
    set_size(face_num * face_att);
	// Free data buffers
	delete[] vertex;
	delete[] face;



}
CylinderGeometry::~CylinderGeometry()
{

}