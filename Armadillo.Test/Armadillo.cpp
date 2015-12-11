#include "Armadillo.h"

EntityControl* eControl = NULL;
EntityTypes* eTypes = NULL;
Landscape* world = NULL;
Renderer* renderer = NULL;
Orion* orion = NULL;

void Init(GLFWwindow* window)
{
	renderer = new Renderer(Vector3(-39.6f, 108, 13.3f), Vector3(0.5f, 4.44f, 0), Perspective, DisplayFieldOfView, DisplayAspectRatio, DisplayNearPlane, DisplayFarPlane);
	renderer->Init(DisplayWidth, DisplayHeight);

	world = new Landscape(&WorldSeed, renderer->GetView());
	world->Lights.push_back(new DirectionalLight(Vector3(-0.2f, -1, -0.3f), Vector3(1, 1, 1)));
	world->Lights.push_back(new PointLight(Vector3(0, 20, 0), Vector3(1, 0, 0), Vector3(1, 0.09, 0.032)));
	world->Lights.push_back(new PointLight(Vector3(20, 80, 0), Vector3(0, 1, 0), Vector3(1, 0.09, 0.032)));
	world->Lights.push_back(new PointLight(Vector3(0, 80, 20), Vector3(0, 0, 1), Vector3(1, 0.09, 0.032)));	

	renderer->SetTerrainManager(&world->GetTerrainManager());

	eTypes = new EntityTypes();
	eTypes->Load();

	eControl = new EntityControl();
	eControl->Load();
	eControl->SetEntityTypes(eTypes);

	renderer->SetEntityTypes(eTypes);

	orion = new Orion(window, world, renderer->GetView(), renderer->GetProjection());
}

void Render()
{
	renderer->Process(eControl->Entities);
	renderer->Process(world);
	renderer->Render();
}

void Update()
{
	world->Gravity();
	world->Generate();
	orion->Update();
	if (orion->Caster != NULL)
		if (orion->Caster->WorldPoint != NULL)
		{
			Entity* e = eControl->Spawnable();
			if (e != NULL)
				e->Position = *orion->Caster->WorldPoint;
		}

	if (orion->ButtonPress(GLFW_MOUSE_BUTTON_MIDDLE, GLFW_CLICK))
		eControl->CreateSpawnable();

	if (orion->KeyboardPress(GLFW_KEY_F10, GLFW_CLICK))
		eControl->Save();

	if (orion->KeyboardPress(GLFW_KEY_F9, GLFW_CLICK))
		eControl->Load();

	if (orion->KeyboardPress(GLFW_KEY_1, GLFW_CLICK))
	{
		eControl->FermatIndex = (eControl->FermatIndex + 1) % eTypes->Length;
		Entity* e = eControl->Spawnable();
		if (e != NULL)
			e->Type = eTypes->GetKey(eControl->FermatIndex);
	}

	if (orion->MouseWheelY() != 0)
	{
		Entity* e = eControl->Spawnable();
		if (e != NULL)
		{
			e->Scale = Max(e->Scale + (orion->MouseWheelY() * 0.01f), 0.005);
			e->Rotation.y += orion->MouseWheelY() * 0.01f;
		}
	}
}

void UpdateTitle(GLFWwindow *pWindow)
{
	WorldTime = glfwGetTime();
	double delta = WorldTime - DisplayFrameTime;
	DisplayFrame++;
	if (delta >= 1.0)
	{
		double fps = double(DisplayFrame) / delta;

		std::stringstream ss;
		ss << Name << " [" << fps << " FPS]";

		glfwSetWindowTitle(pWindow, ss.str().c_str());

		DisplayFrame = 0;
		DisplayFrameTime = WorldTime;
	}
}

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWmonitor* monitor = DisplayFullscreen ? glfwGetPrimaryMonitor() : NULL;
	window = glfwCreateWindow(DisplayWidth, DisplayHeight, Name.c_str(), monitor, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
		return -1;

	Init(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		UpdateTitle(window);

		/* Poll for and process events */
		glfwPollEvents();
		//glfwWaitEvents();
		
		Update();		
	}
	glfwTerminate();
	return 0;
}