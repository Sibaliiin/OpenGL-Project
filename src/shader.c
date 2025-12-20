#include	"shader.h"

#include	<stdio.h>
#include	<stdlib.h>



// file loading
static char *read_file(const char *path)
{
	FILE *file = fopen(path, "rb");
	if (!file)
	{
		fprintf(stderr, "ERROR: Could not open file %s\n", path);

		return NULL;
	}
	
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char *buffer = malloc(size + 1);
	if (!buffer)
	{
		fclose(file);

		return NULL;

	}

	fread(buffer, 1, size, file);
	buffer[size] = '\0';

	fclose(file);

	return buffer;

}

// error handling
static void check_compile_errors(GLuint object, const char *type)
{
	GLint success;
	GLchar info_log[1024];

	if (type[0] != 'P')
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
            		glGetShaderInfoLog(object, 1024, NULL, info_log);
           		 fprintf(stderr, "ERROR::SHADER_COMPILATION (%s)\n%s\n", type, info_log);
       		 }
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
           		 glGetProgramInfoLog(object, 1024, NULL, info_log);
           		 fprintf(stderr, "ERROR::PROGRAM_LINKING\n%s\n", info_log);
       		 }	
	}
}

// shader initialization
int shader_init(Shader *shader,
                const char *vertex_path,
                const char *fragment_path)
{
    char *vertex_source = read_file(vertex_path);
    char *fragment_source = read_file(fragment_path);

    if (!vertex_source || !fragment_source)
        return 0;

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char * const *)&vertex_source, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char * const *)&fragment_source, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    shader->program = glCreateProgram();
    glAttachShader(shader->program, vertex);
    glAttachShader(shader->program, fragment);
    glLinkProgram(shader->program);
    check_compile_errors(shader->program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertex_source);
    free(fragment_source);

    return 1;
}

// usage and uniforms
void shader_use(const Shader *shader)
{
    glUseProgram(shader->program);
}

void shader_set_bool(const Shader *shader, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(shader->program, name), value);
}

void shader_set_int(const Shader *shader, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(shader->program, name), value);
}

void shader_set_float(const Shader *shader, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(shader->program, name), value);
}

// cleanup
void shader_destroy(Shader *shader)
{
    glDeleteProgram(shader->program);
    shader->program = 0;
}
