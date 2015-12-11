#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

#include "Osiris.h"
#include "InputManager\Orion.h"

#include "Graphics/Renderer.h"
#include "Graphics/Projection.h"

#include "Maths/MathHelper.h"
#include "World/Landscape.h"
#include "World/Entity.h"
#include "World/Light.h"

#include "World\LivingManager.h"

#include "Physics\PhysicsWorld.h"
#include "Physics\PhysicsEntity.h"
#include "Physics\Renderer_TS.h"
#include "Physics\PhysicsConstants.h"

using namespace std;
using namespace Armadillo::Graphics;
using namespace Armadillo::World;
using namespace Armadillo::Management;
using namespace Armadillo::Maths;
using namespace Armadillo::Osiris;
using namespace Natura::World;
using namespace Armadillo::Physics;

extern void Render();
extern void Init();
extern void Update();
