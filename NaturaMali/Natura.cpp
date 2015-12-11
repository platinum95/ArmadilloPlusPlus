#include "Natura.h"

Landscape* world = NULL;
Renderer* renderer = NULL;
PhysicsWorld* physWorld = NULL;
PhysicsEntity* viewEntity = NULL;
Renderer_TS* renderer_ts = NULL;
bool doPhysics;
const float physicsPS = 60;
const float physicsPeriod = 1 / physicsPS;

void Init()
{
	renderer = new Renderer(Vector3(-39.6f, 108, 13.3f), Vector3(0.5f, 4.44f, 0), Perspective, DisplayFieldOfView, DisplayAspectRatio, DisplayNearPlane, DisplayFarPlane);
	renderer->Init(DisplayWidth, DisplayHeight);

	physWorld = new PhysicsWorld(-19.81f, .0001f);

	viewEntity = new DynamicEntity(renderer->GetView()->Position, renderer->GetView()->Rotation);

	world = new Landscape(&WorldSeed, renderer->GetView());
	world->Lights.push_back(new DirectionalLight(Vector3(-0.2f, -1, -0.3f), Vector3(1, 1, 1)));
	world->Lights.push_back(new PointLight(Vector3(0, 20, 0), Vector3(1, 0, 0), Vector3(1, 0.09, 0.032)));
	world->Lights.push_back(new PointLight(Vector3(20, 80, 0), Vector3(0, 1, 0), Vector3(1, 0.09, 0.032)));
	world->Lights.push_back(new PointLight(Vector3(0, 80, 20), Vector3(0, 0, 1), Vector3(1, 0.09, 0.032)));

	Orion::SetWorld(world);
	Orion::SetView(renderer->GetView(), renderer->GetProjection());
	Orion::SetViewEntity(viewEntity);

	::PhysicsConstants::setWorld(world);

	physWorld->world = world;
	physWorld->addToWorld(viewEntity);
	doPhysics = true;

	renderer->SetTerrainManager(&world->GetTerrainManager());
}

void Render()
{
	renderer_ts->renderer->Process(world);
	renderer_ts->renderer->Render();
}

void Update()
{
	world->Gravity();
	world->Generate();
	Orion::Update();
	renderer->GetView()->Position = renderer_ts->pos2;
	std::cout << viewEntity->forces.x;
}

void updatePhysics() {
	float prevTime = Armadillo::Osiris::WorldTime;
	while (doPhysics) {
		float timeDiff = glfwGetTime() - prevTime;
		float timeDoing = glfwGetTime();
		physWorld->update(timeDiff);
		prevTime = glfwGetTime();

		viewEntity->Position = viewEntity->position + Vector3(0, 2, 0);
		//renderer_ts->getRenderer()->GetView()->Position = viewEntity->Position;
		if (renderer_ts->isLocked())
			renderer_ts->pos1 = viewEntity->Position;
		else
			renderer_ts->pos2 = viewEntity->Position;

		cout << viewEntity->position.y << endl;

		timeDoing = glfwGetTime() - timeDoing;


		if (timeDoing < physicsPeriod) {
			float sleepyFloat = (physicsPeriod - timeDoing) * 10e5;
			long sleepyTime = sleepyFloat;
			this_thread::sleep_for(chrono::microseconds(sleepyTime));
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

	Orion::GlutInit(window);

	Init();

	renderer_ts = new Renderer_TS();

	renderer_ts->renderer = renderer;

	thread physicsThread(updatePhysics);


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

		/* Update World */
		Update();
	}
	doPhysics = false;
	physicsThread.join();
	glfwTerminate();
	return 0;
}