#include <GL/glew.h>
#include <GL/glut.h>
#include "CImg.h"
#include <iostream>

using namespace cimg_library;

void display();
void reshape(int width, int height);
GLuint makeTexture(const CImg<unsigned char>& img, GLenum format);
GLuint makeShader(const char* vertex, const char* fragment);

GLuint g_hash, g_offsets, g_coverage, g_program;
CImg<unsigned char> hash, offsets, coverage;

static const char m_vertex[] = "void main()\n"
		"{\n"
		"	gl_Position = ftransform();\n"
		"	gl_TexCoord[0] = gl_MultiTexCoord0;\n"
		"}\n";

static const char m_fragment[] = 
		"#extension GL_ARB_texture_rectangle : enable\n"
		"uniform sampler2DRect coverage, hash, offsets;\n"
		"uniform float hash_width, offsets_width;\n"
		"void main()\n"
		"{\n"
		"	vec4 coverage = texture2DRect(coverage, (gl_TexCoord[0].xy));\n"
		"	if (coverage.r == 0.) // no pixel\n"
		"	{\n"
		"		//gl_FragColor = vec4(0, 0, 1, 0);\n"
		"		gl_FragColor = coverage;\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		vec4 off = texture2DRect(offsets, (mod(gl_TexCoord[0].xy, offsets_width)));\n"
		"		off.xy = off.xy * vec2(255.);\n"
		"		vec4 color = texture2DRect(hash, mod(gl_TexCoord[0].xy + off.xy, hash_width));\n"
		"		gl_FragColor = color;\n"
		"	}\n"
		"}\n";


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	if (argc != 4)
	{
		std::cout << "Usage: hash offset coverage" << std::endl;
		return 1;
	}
	// load the images
	hash.load(argv[1]);
	offsets.load(argv[2]);
	coverage.load(argv[3]);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(coverage.dimx() + hash.dimx() + offsets.dimx(), coverage.dimy());
	glutCreateWindow("Perfect Spatial Hashing Decode Demo");

	glewInit();
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// init

	g_hash = makeTexture(hash, GL_RGBA);
	g_offsets = makeTexture(offsets, GL_RGBA);
	g_coverage = makeTexture(coverage, GL_RGBA);
	g_program = makeShader(m_vertex, m_fragment);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);	
}

void display(void)
{
	glClearColor(1, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, coverage.dimx() + hash.dimx() + offsets.dimx(), 0, coverage.dimy(), 1, -1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_RECTANGLE_ARB);

	int error;
	while ((error = glGetError()) != 0)
	{
		std::cout << "Before:" << gluErrorString(error) << std::endl;
	}
	int left = 0;
	int width = coverage.dimx();
	int height = coverage.dimy();
	glUseProgramObjectARB(g_program);
	GLuint loc = glGetUniformLocationARB(g_program, "coverage");
	std::cout << "location for coverage: " << loc << std::endl;
	glUniform1iARB(loc, 0); // texture unit 0
	loc = glGetUniformLocationARB(g_program, "hash");
	std::cout << "location for hash: " << loc << std::endl;
	glUniform1iARB(loc, 1); // texture unit 0
	loc = glGetUniformLocationARB(g_program, "offsets");
	std::cout << "location for offsets: " << loc << std::endl;
	glUniform1iARB(loc, 2); // texture unit 0
	loc = glGetUniformLocationARB(g_program, "hash_width");
	std::cout << "location for hash width: " << loc << std::endl;
	glUniform1fARB(loc, (float)hash.dimx());
	loc = glGetUniformLocationARB(g_program, "offsets_width");
	std::cout << "location for offsets_width: " << loc << std::endl;
	glUniform1fARB(loc, (float)offsets.dimx());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, g_coverage);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, g_hash);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, g_offsets);
	glActiveTexture(GL_TEXTURE0);
	glBegin(GL_QUADS);
		glTexCoord2i(0, height);
		glVertex2i(left, 0);
		glTexCoord2i(width, height);
		glVertex2i(left + width, 0);
		glTexCoord2i(width, 0);
		glVertex2i(left + width, height);
		glTexCoord2i(0, 0);
		glVertex2i(left, height);
	glEnd();
	while ((error = glGetError()))
	{
		std::cout << "after" << std::endl;
		gluErrorString(error);
	}
	glUseProgramObjectARB(0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, 0);
	glActiveTexture(GL_TEXTURE0);
	left += width;
	width = hash.dimx();
	height = hash.dimy();
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, g_hash);
	glBegin(GL_QUADS);
		glTexCoord2i(0, height);
		glVertex2i(left, 0);
		glTexCoord2i(width, height);
		glVertex2i(left + width, 0);
		glTexCoord2i(width, 0);
		glVertex2i(left + width, height);
		glTexCoord2i(0, 0);
		glVertex2i(left, height);
	glEnd();
	left += width;
	width = offsets.dimx();
	height = offsets.dimy();
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, g_offsets);
	glBegin(GL_QUADS);
		glTexCoord2i(0, height);
		glVertex2i(left, 0);
		glTexCoord2i(width, height);
		glVertex2i(left + width, 0);
		glTexCoord2i(width, 0);
		glVertex2i(left + width, height);
		glTexCoord2i(0, 0);
		glVertex2i(left, height);
	glEnd();

	glDisable(GL_TEXTURE_RECTANGLE_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, 0);

	glutSwapBuffers();
}

GLuint makeTexture(const CImg<unsigned char>& img, GLenum format)
{
	unsigned char* pixels = new unsigned char[img.dimx() * img.dimy() * img.dimv()];
	unsigned char* p = pixels;
	for (int y = 0; y < img.dimy(); y++)
		for (int x = 0; x < img.dimx(); x++)
			for (int v = 0; v < img.dimv(); v++)
				*(p++) = img(x,y,v);	
			
	
	GLuint tex;
	GLenum dataFormat = 0;

	switch (img.dimv())
	{
		case 1:
			dataFormat = GL_ALPHA;
			break;
		case 2:
			dataFormat = GL_LUMINANCE_ALPHA;
			break;
		case 3:
			dataFormat = GL_RGB;
			break;
		case 4:
			dataFormat = GL_RGBA;
			break;
		default:
			dataFormat = GL_RGBA;
			break;
	}

	GLenum target = GL_TEXTURE_RECTANGLE_ARB;
	glGenTextures(1, &tex);
	glBindTexture(target, tex);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(target, 0, format, img.dimx(), img.dimy(), 0, dataFormat, GL_UNSIGNED_BYTE, pixels);
	delete[] pixels;
	return tex;
}

GLuint makeShader(const char* vertex, const char* fragment)
{
	GLuint vid = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	GLuint fid = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
	glShaderSourceARB(vid, 1, &vertex, 0);
	glShaderSourceARB(fid, 1, &fragment, 0);
	
	glCompileShaderARB(vid);
	glCompileShaderARB(fid);
	GLuint pid = glCreateProgramObjectARB();

	glAttachObjectARB(pid, vid);
	glAttachObjectARB(pid, fid);

	// delete shader objects as soon as they have been attached to a program
	glDeleteObjectARB(vid);
	glDeleteObjectARB(fid);
	
	glLinkProgramARB(pid);

	char glslLog[1024];
	GLsizei glslLogSize;
	glGetInfoLogARB(pid, 1024, &glslLogSize, glslLog);
	if(glslLogSize>0)
	{
		std::cerr << "shader error log: " << glslLog << std::endl;
	}
	else
	{
		std::cout <<  "shader all ok" << std::endl;
	}

	return pid;
}

