#include <iostream>
#include <cmath>
// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera Libre
Camera  camera(glm::vec3(-100.0f, 2.0f, -45.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;

bool modoIsometrico = true; // Establece el modo inicial como isométrico


void vista1() {
	// Cambiar la posición inicial de la cámara para una vista isométrica
	Camera camera(glm::vec3(-2.0f, 200.0f, 50.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Ajusta la orientación inicial hacia abajo
}
void vista2() {
	// Cambiar la posición inicial de la cámara para una vista isométrica
	Camera camera(glm::vec3(-2.0f, 200.0f, 50.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Ajusta la orientación inicial hacia abajo
}
void vista3() {
	// Cambiar la posición inicial de la cámara para una vista isométrica
	Camera camera(glm::vec3(-100.0f, 2.0f, -45.0f));
}
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-13.0f, 11.5f, 0.5f);
bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
//float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0, rotRodDer = 0, rotBrzDer = 0, rotBrzIzq = 0, rotBrzDer2 = 0, rotBrzIzq2 = 0;
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotX = 0, rotY = 0, rotZ = 0;


#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;
	float posY;
	float posZ;
	float incX;
	float incY;
	float incZ;
	float rotX;
	float rotY;
	float rotZ;
	float rotIncX;
	float rotIncY;
	float rotIncZ;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(posX,posY,posZ),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0)
};

glm::vec3 LightP1;



void saveFrame(void)
{

	//printf("SAVED\n", FrameIndex);
	printf("frameindex %d\n", FrameIndex);
	printf("%f %f %f %f %f %f\n", posX, posY, posZ, rotX, rotY, rotZ);
	printf("%d\n", FrameIndex);
	/*
	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	KeyFrame[FrameIndex].rotX = rotX;
	KeyFrame[FrameIndex].rotY = rotY;
	KeyFrame[FrameIndex].rotZ = rotZ;
	

	FrameIndex++;*/

	KeyFrame[0].posX = -13.5f;
	KeyFrame[0].posY = 13.0f;
	KeyFrame[0].posZ = 0.5f;
	KeyFrame[0].rotX = 0.0f;
	KeyFrame[0].rotY = 0.0f;
	KeyFrame[0].rotZ = 0.0f;

	KeyFrame[1].posX = -14.0f;
	KeyFrame[1].posY = 12.0f;
	KeyFrame[1].posZ = 0.5f;
	KeyFrame[1].rotX = 0.0f;
	KeyFrame[1].rotY = 10.0f;
	KeyFrame[1].rotZ = 0.0f;

	KeyFrame[2].posX = -12.5f;
	KeyFrame[2].posY = 10.5f;
	KeyFrame[2].posZ = 1.5f;
	KeyFrame[2].rotX = 0.0f;
	KeyFrame[2].rotY = -5.0f;
	KeyFrame[2].rotZ = 0.0f;

	KeyFrame[3].posX = -11.0f;
	KeyFrame[3].posY = 12.5f;
	KeyFrame[3].posZ = 0.5f;
	KeyFrame[3].rotX = 0.0f;
	KeyFrame[3].rotY = 5.0f;
	KeyFrame[3].rotZ = 0.0f;

	KeyFrame[4].posX = -13.0f;
	KeyFrame[4].posY = 14.0f;
	KeyFrame[4].posZ = -1.5f;
	KeyFrame[4].rotX = 0.0f;
	KeyFrame[4].rotY = 10.0f;
	KeyFrame[4].rotZ = 0.0f;

	KeyFrame[5].posX = -11.0f;
	KeyFrame[5].posY = 10.5f;
	KeyFrame[5].posZ = 0.5f;
	KeyFrame[5].rotX = 0.0f;
	KeyFrame[5].rotY = -20.0f;
	KeyFrame[5].rotZ = 0.0f;

	KeyFrame[6].posX = -11.0f;
	KeyFrame[6].posY = 15.5f;
	KeyFrame[6].posZ = 1.5f;
	KeyFrame[6].rotX = 0.0f;
	KeyFrame[6].rotY = 5.0f;
	KeyFrame[6].rotZ = 0.0f;

	KeyFrame[7].posX = -13.0f;
	KeyFrame[7].posY = 13.5f;
	KeyFrame[7].posZ = 0.5f;
	KeyFrame[7].rotX = 0.0f;
	KeyFrame[7].rotY = -15.0f;
	KeyFrame[7].rotZ = 0.0f;

	KeyFrame[8].posX = -10.0f;
	KeyFrame[8].posY = 11.5f;
	KeyFrame[8].posZ = -1.5f;
	KeyFrame[8].rotX = 0.0f;
	KeyFrame[8].rotY = 3.0f;
	KeyFrame[8].rotZ = 0.0f;
	FrameIndex++;
}



void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	rotX = KeyFrame[0].rotX;
	rotY = KeyFrame[0].rotY;
	rotZ = KeyFrame[0].rotZ;

}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	KeyFrame[playIndex].rotIncX = (KeyFrame[playIndex + 1].rotX - KeyFrame[playIndex].rotX) / i_max_steps;
	KeyFrame[playIndex].rotIncY = (KeyFrame[playIndex + 1].rotY - KeyFrame[playIndex].rotY) / i_max_steps;
	KeyFrame[playIndex].rotIncZ = (KeyFrame[playIndex + 1].rotZ - KeyFrame[playIndex].rotZ) / i_max_steps;

}


//Puerta
float rotPuerta = 0.0f;
float rotVentana1 = 0.0f;

// TV
float posX1 = 1.42f;
float posX2 = 2.0f;
float posX3 = 3.0f;

// PESA
float posPesa = 0.0f;
float rotPesa = 0.0f;

// Estado inicial
float pantalla1 = posX1;
float pantalla2 = posX2;
float pantalla3 = posX3;
const int ESTADO_INICIAL = 0;
const int SEGUNDO_ESTADO = 1;
const int TERCER_ESTADO = 2;
int estadoActual = ESTADO_INICIAL;
bool teclaPresionadaTV = false;
float tiempo;
float velocidad;
int direccion = 1;
int direccionCola = 1;
float movCola = 1.0f;
float movResorte = 0.0f;
int contaResorte = 0;
float test1 = 1.0f;
float test2 = 0.0f;
float movPalanca = 0.0f;
float movPaleta1 = 0.0f;
float movPaleta2 = 0.0f;

//MOV NEMO
float movNemoX = 0.0f;
float movNemoY = 0.0f;
float movNemoZ = 0.0f;

//MOV PALETAS
int direccionPaleta1 = 1;
int direccionPaleta2 = 1;


//MOUSE CALLBACK
bool mousePresionado = false;
double mouseX, mouseY;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mousePresionado = true;
			glfwGetCursorPos(window, &mouseX, &mouseY);
		}
		else if (action == GLFW_RELEASE) {
			mousePresionado = false;
		}
	}
}

void movimientoResorte() {
	if (test1 <= 0.3)
	{
		rotPuerta = test1;
		movResorte = test2;
		movPalanca = movPalanca;
	}
	else {
		test1 -= 0.05f;
		test2 += 3.83f;
		rotPuerta = test1;
		movResorte = test2;
		movPalanca += 0.22;
	}
}
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "317144262_PROYECTOFINAL2024-1_GRUPO07", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader Anim2("Shaders/anim2.vs", "Shaders/anim2.frag");


	Model Pinball((char*)"Models/Pinball/pinball.obj");
	Model cristal((char*)"Models/Pinball/glass.obj");
	Model tunel((char*)"Models/Pinball/tunel.obj");
	Model paleta1((char*)"Models/Pinball/paletazquierda.obj");
	Model paleta2((char*)"Models/Pinball/paletaDerecha.obj");
	Model canica1((char*)"Models/Pinball/canica1.obj");
	Model Yuta((char*)"Models/Yuta/yuta.obj");
	Model Rika((char*)"Models/Yuta/rika.obj");
	Model Estatuas((char*)"Models/Valley/estatuas.obj");
	//Model PisoValle((char*)"Models/Valley/piso.obj");
	//Model ParedesValleIzq((char*)"Models/Valley/paredIzq.obj");
	//Model ParedesValleDer((char*)"Models/Valley/paredDer.obj");
	Model tiburon((char*)"Models/Tiburon/tiburon.obj");
	Model itachi((char*)"Models/Itachi/itachi.obj");
	//NEMO
	Model NemoCuerpo((char*)"Models/Nemo/NemoCuerpo.obj");
	Model cola((char*)"Models/Nemo/cola.obj");
	Model aletaGrande((char*)"Models/Nemo/aletaGrande.obj");
	Model aletaPequena((char*)"Models/Nemo/aletaPequena.obj");
	Model templo((char*)"Models/Templo/templo.obj");
	Model templo2((char*)"Models/Templo/templo2.obj");
	//PALANCA
	Model estructura((char*)"Models/Palanca/estructura.obj");
	Model palanca((char*)"Models/Palanca/palanca.obj");
	Model resorte((char*)"Models/Palanca/resorte.obj");
	


	// Build and compile our shader program

	//Inicialización de KeyFrames
	
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0.0f;
		KeyFrame[i].posY = 0.0f;
		KeyFrame[i].posZ = 0.0f;
		KeyFrame[i].incX = 0.0f;
		KeyFrame[i].incY = 0.0f;
		KeyFrame[i].incZ = 0.0f;
		KeyFrame[i].incX = 0.0f;
		KeyFrame[i].incY = 0.0f;
		KeyFrame[i].incZ = 0.0f;
		KeyFrame[i].rotIncX = 0.0f;
		KeyFrame[i].rotIncY = 0.0f;
		KeyFrame[i].rotIncZ = 0.0f;
	}


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");
	
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	//MOUSE CALLBACK
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//MOUSE CALLBACK
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			double newMouseX, newMouseY;
			glfwGetCursorPos(window, &newMouseX, &newMouseY);

			// Calcula la diferencia en la posición Y del mouse
			double deltaY = newMouseY - mouseY;

			// Solo realiza ajustes si el mouse se arrastra hacia abajo
			if (deltaY > 0.0) {
				movimientoResorte();
				mouseX = newMouseX;
				mouseY = newMouseY;

			}
		}
		else {
			test1 = 1.0f;
			test2 = 0.0f;
			rotPuerta = 1.0f;
			movResorte = 0.0f;
			movPalanca = 0.0f;
		}





		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp



		//Carga de modelo 
		//Personaje
		view = camera.GetViewMatrix();
		glm::mat4 model(1);
		// Dibuja el objeto 'Pinball' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pinball.Draw(lightingShader);

		// Dibuja el objeto 'Tunel' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tunel.Draw(lightingShader);

		// Dibuja el objeto 'Canica #1' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		canica1.Draw(lightingShader);

		// Dibuja el objeto 'Yuta' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Yuta.Draw(lightingShader);

		// Dibuja el objeto 'Rika' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Rika.Draw(lightingShader);

		// Dibuja el objeto 'Estatuas' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estatuas.Draw(lightingShader);

		// Dibuja el objeto 'PisoValle' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//PisoValle.Draw(lightingShader);

		// Dibuja el objeto 'ParedesValle' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ParedesValleDer.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ParedesValleIzq.Draw(lightingShader);



		// Dibuja el objeto 'Tiburon' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tiburon.Draw(lightingShader);
		
		// Dibuja el objeto 'Itachi' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		itachi.Draw(lightingShader);

		//// Dibuja el objeto 'nemo' 
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//nemo.Draw(lightingShader);



		// Dibuja el objeto 'NEMO' 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.0f,movNemoY, movNemoZ));
		//model = glm::rotate(model, glm::radians(-rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(10.0f, -40.0f, -15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NemoCuerpo.Draw(lightingShader);

		view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-2.3f, 100.0f, 49.9f));
		model = glm::rotate(model, glm::radians(movCola), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(2.3f, -100.0f, -49.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cola.Draw(lightingShader);

		view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-3.6f, 100.0f , 47.2f + movNemoZ));
		model = glm::rotate(model, glm::radians(rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(3.6f, -100.0f , -47.2f ));
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		aletaGrande.Draw(lightingShader);
			
		view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-1.0f, 100.0f , 47.2f));
		model = glm::rotate(model, glm::radians(-rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(1.0f, -100.0f, -47.2f ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		aletaPequena.Draw(lightingShader);
			


		// Dibuja el objeto 'templo' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		templo.Draw(lightingShader);

		// Dibuja el objeto 'templo2' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		templo2.Draw(lightingShader);

		// Dibuja el objeto 'Palanca Estructura' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		estructura.Draw(lightingShader);

		// Dibuja el objeto 'Palanca Sola' 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, movPalanca));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		palanca.Draw(lightingShader);

		// Dibuja el objeto 'Resorte' 
		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, movResorte));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, rotPuerta));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		resorte.Draw(lightingShader);



		//PALETAS
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-13.0f, 100.0f, 62.0f));
		model = glm::rotate(model, glm::radians(movPaleta1), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(13.0f, -100.0f, -62.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		paleta1.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.3f, 100.0f, 62.0f));
		model = glm::rotate(model, glm::radians(-movPaleta2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-4.3f, -100.0f, -62.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		paleta2.Draw(lightingShader);


		glBindVertexArray(0);


		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Piso.Draw(lightingShader);
		//// Dibuja el objeto 'tv'
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//tv.Draw(lightingShader);

		//// Dibuja el objeto 'pantallaNegra'
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(pantalla1, -4.165f, -0.168f)); //Parte oculta -> 2.0 En X  & 1.42 cuando se muestra
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pantallaNegra.Draw(lightingShader);

		//// Dibuja el objeto 'pantallaEsperanza'
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(pantalla2, -2.0f, 0.0f)); //Parte oculta -> 2.0 En X  & 0.77 cuando se muestra
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pantallaEspernza.Draw(lightingShader);

		//// Dibuja el objeto 'pantallaSinCanal'
		////model = glm::mat4(1);
		////model = glm::translate(model, glm::vec3(pantalla3, 0.0f, 0.0f)); //Parte oculta -> 3.0 En X & 1.78 cuando se muestra
		////glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		////pantallaSinCanal.Draw(lightingShader);

		//

		////lightingShader.Use();

		//// Dibuja el objeto 'piano' 
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//piano.Draw(lightingShader);
		//
		//// Dibuja el objeto 'nota' 
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::rotate(model, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));

		//// Establece la matriz de modelo en el shader
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//// Dibuja el objeto 'nota'
		//nota.Draw(lightingShader);





		//// Dibuja el objeto 'ventana' 
		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(-7.7f, 0.0f, 15.7f));
		//model = glm::rotate(model, glm::radians(-rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(7.7f, 0.0f, -15.7f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ventana1.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(-4.1f, 0.0f, 15.7f));
		//model = glm::rotate(model, glm::radians(rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(4.1f, 0.0f, -15.7f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ventana2.Draw(lightingShader);


		//// Dibuja el objeto 'ventana2' 
		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(-15.6f, 0.0f, 15.7f));
		//model = glm::rotate(model, glm::radians(-rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(7.6f, 0.0f, -15.7f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ventana1.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(-12.1f, 0.0f, 15.7f));
		//model = glm::rotate(model, glm::radians(rotVentana1), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(4.1f, 0.0f, -15.7f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//ventana2.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, -4.0f));
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.95f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f);
		//cristal.Draw(lightingShader);
		glDisable(GL_BLEND); //Desactiva el canal alfa 

		//Anim2.Use();
		//tiempo = glfwGetTime() * 10.0f;
		//// Get location objects for the matrices on the lamp shader (these could be different on a different shader)

		//model = glm::mat4(1.0f); // Inicializa la matriz de modelo como una matriz de identidad
		//float translationX = velocidad * glfwGetTime(); // Ajusta la velocidad de traslación según tus necesidades
		//model = glm::translate(model, glm::vec3(0.0f, 0.1f, translationX));
		//model = glm::translate(model, glm::vec3(pantalla3, -0.1f, 0.0f)); // Parte oculta -> 3.0 En X & 1.78 cuando se muestra

		//modelLoc = glGetUniformLocation(Anim2.Program, "model");
		//viewLoc = glGetUniformLocation(Anim2.Program, "view");
		//projLoc = glGetUniformLocation(Anim2.Program, "projection");
		//// Set matrices
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1f(glGetUniformLocation(Anim2.Program, "time"), tiempo);
		//model = glm::translate(model, glm::vec3(0.0, 0.0f * glfwGetTime(), 0.0f));
		//model = glm::translate(model, glm::vec3(pantalla3, 0.0f, 0.0f)); // Parte oculta -> 3.0 En X & 1.78 cuando se muestra
		//pantallaSinCanal.Draw(Anim2);
		//glBindVertexArray(0);








		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{
    // Movimiento del personaje
    if (play)
    {
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
			
		}
        else
        {
            // Dibuja animación con los valores de KeyFrame actuales
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

            rotX += KeyFrame[playIndex].rotIncX;
            rotY += KeyFrame[playIndex].rotIncY;
            rotZ += KeyFrame[playIndex].rotIncZ;

            i_curr_steps++;
        }
    }
}



// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_5])
	{	
		for (int i = 0; i < 9; i++)
		{
			saveFrame();
		}
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
	}

	if (keys[GLFW_KEY_6])
	{
		FrameIndex = 0;

		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

	}


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
		static bool ventanaAbierta = false;
		static bool teclaPresionada = false;

		static bool puertaAbierta = false;
		static bool teclaPresionada2 = false;

		static bool pesaMovida = false;
		static bool teclaPresionada3 = false;
		static bool teclaPresionadaPaleta1 = false;
		static bool teclaPresionadaPaleta2 = false;
		static bool Paleta1abierta = false;
		static bool Paleta2abierta = false;

		if (keys[GLFW_KEY_1]) {
			// Movimientos ALETAS
			if (direccion==1)
			{
				rotVentana1 += 0.5f;
				movPaleta2 += 0.5f;
				movPaleta1 += 0.5f;
				if (rotVentana1>=45.0f)
				{
					direccion = 0;
				}
			}
			if (direccion == 0)
			{
				rotVentana1 -= 0.5f;
				movPaleta2 -= 0.5f;
				movPaleta1 -= 0.5f;
				if (rotVentana1 <= 0.0f)
				{
					direccion = 1;
				}
			}
			//Parte de la Cola
			if (direccionCola ==1)
			{
				movCola += 0.5f;
				if (movCola >=10.0f)
				{
					direccionCola = 0;
				}
			}
			if (direccionCola == 0)
			{
				movCola -= 0.5f;
				if (movCola <= -10.0f)
				{
					direccionCola = 1;
				}
			}


		}
		

	//ANIMACION PUERTA
		if (keys[GLFW_KEY_2])
		{
			if (!teclaPresionada2) {
				teclaPresionada2 = true;  // Marcar la tecla como presionada

				if (!puertaAbierta) {
					// Estado: Ventana Cerrada
					puertaAbierta = true;
				}
				else {
					// Estado: Ventana Abierta
					puertaAbierta = false;
				}
			}

		}
		else {
			teclaPresionada2 = false;  // Restablecer la tecla como no presionada
		}
		// Actualizar el estado de la ventana segun ventanaAbierta
		if (puertaAbierta) {
			if (rotPuerta > 0.3f) {
				rotPuerta -= 0.05f;
				movResorte -= 3.83;
			}
		}
		else {
			if (rotPuerta < 1.0f) {
				rotPuerta += 0.4f;
				movResorte += 30.64;
			}
		}

	//ANIMACIÓN PANTALLAS
	if (keys[GLFW_KEY_3])
	{
		if (!teclaPresionada) {
			// Cambiar estado según el estado actual
			if (estadoActual == ESTADO_INICIAL) {
				pantalla1 = posX2;
				pantalla2 = 0.768f;
				pantalla3 = posX3;
				estadoActual = SEGUNDO_ESTADO;
			}
			else if (estadoActual == SEGUNDO_ESTADO) {
				pantalla1 = posX2;
				pantalla2 = posX2;
				pantalla3 = 1.78f;
				estadoActual = TERCER_ESTADO;
			}
			else if (estadoActual == TERCER_ESTADO) {
				pantalla1 = posX1;
				pantalla2 = posX2;
				pantalla3 = posX3;
				estadoActual = ESTADO_INICIAL;
			}
			else {
				std::cerr << "Estado no reconocido." << std::endl;
			}

			teclaPresionada = true;
		}
	}
	else {
		teclaPresionada = false;
	}

	//ANIMACIÓN PESA
	if (keys[GLFW_KEY_4]) {
		if (!teclaPresionada3) {
			teclaPresionada3 = true;  // Marcar la tecla como presionada

			if (!pesaMovida) {
				// Estado: Ventana Cerrada
				pesaMovida = true;
			}
			else {
				// Estado: Ventana Abierta
				pesaMovida = false;
			}
		}
	}
	else {
		teclaPresionada3 = false;  // Restablecer la tecla como no presionada
	}

	// Ajusta las velocidades según sea necesario
	if (pesaMovida) {
		if (posPesa < 12.5f) {
			posPesa += 0.005f;  // Ajusta la velocidad de desplazamiento
		}
		else {
			posPesa = 12.5f;
		}
	}
	else {
		if (posPesa > 0.0f) {
			posPesa -= 0.005f;  // Ajusta la velocidad de rotación
		}
		else {
			posPesa = 0.0f;
		}
	}
	if (keys[GLFW_KEY_C]) {
		if (!teclaPresionadaPaleta1) {
			teclaPresionadaPaleta1 = true;  // Marcar la tecla como presionada

			if (!Paleta1abierta) {
				// Estado: Ventana Cerrada
				Paleta1abierta = true;
			}
			else {
				// Estado: Ventana Abierta
				Paleta1abierta = false;
			}
		}
	}
	else {
		teclaPresionadaPaleta1 = false;
	}
	if (Paleta1abierta) {
		if (movPaleta1 < 45.0f) {
			movPaleta1 += 3.0f;
		}
		else {
			movPaleta1 = 45.0f;
		}
	}
	else {
		if (movPaleta1 > 0.0f) {
			movPaleta1 -= 3.0f;
		}
		else {
			movPaleta1 = 0.0f;
		}
	}

	if (keys[GLFW_KEY_V]) {
		if (!teclaPresionadaPaleta2) {
			teclaPresionadaPaleta2 = true;  // Marcar la tecla como presionada

			if (!Paleta2abierta) {
				// Estado: Ventana Cerrada
				Paleta2abierta = true;
			}
			else {
				// Estado: Ventana Abierta
				Paleta2abierta = false;
			}
		}
	}
	else {
		teclaPresionadaPaleta2 = false;
	}
	if (Paleta2abierta) {
		if (movPaleta2 < 45.0f) {
			movPaleta2 += 3.0f;
		}
		else {
			movPaleta2 = 45.0f;
		}
	}
	else {
		if (movPaleta2 > 0.0f) {
			movPaleta2 -= 3.0f;
		}
		else {
			movPaleta2 = 0.0f;
		}
	}
	//Mov Personaje
	//EJE X
	if (keys[GLFW_KEY_H])
	{
		posZ += 0.1;
		movNemoY -= -0.016081f;
		movNemoZ += -0.10f;
	}
	if (keys[GLFW_KEY_Y])
	{
		posZ -= 0.1;
	}
	//EJE Z
	if (keys[GLFW_KEY_G])
	{
		posX -= 0.1;
	}

	if (keys[GLFW_KEY_J])
	{
		posX += 0.1;
	}
	//EJE Y
	if (keys[GLFW_KEY_I])
	{
		posY -= 0.1;
	}

	if (keys[GLFW_KEY_K])
	{
		posY += 0.1;
	}




	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime*20);


	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}






}


