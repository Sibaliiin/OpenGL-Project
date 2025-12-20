#ifndef	SHADER_H
#define	SHADER_H

#include	<glad/glad.h>

typedef struct
{
	GLuint program;
} Shader;

// create and link the shader program
int shader_init(Shader *shader, 
		const char *vertex_path,
		const char *fragment_path);

// activate the shader program
void shader_use(const Shader *shader);

// uniform helpers
void shader_set_bool	(const Shader *shader, const char *name, int value);
void shader_set_int	(const Shader *shader, const char *name, int value);
void shader_set_float	(const Shader *shader, const char *name, float value);

// destroy the shader program
void shader_destroy(Shader *shader);

#endif
