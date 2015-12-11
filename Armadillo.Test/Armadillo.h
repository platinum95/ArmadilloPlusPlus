#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Orion.h"
#include "Osiris.h"

#include "Graphics/Renderer.h"
#include "Graphics/Projection.h"
#include "Management/EntityControl.h"

#include "Maths/MathHelper.h"
#include "World/Landscape.h"
#include "World/Entity.h"
#include "World/EntityTypes.h"
#include "World/Light.h"
#include "World/RayCaster.h"

using namespace std;
using namespace Armadillo::Graphics;
using namespace Armadillo::World;
using namespace Armadillo::Management;
using namespace Armadillo::Maths;
using namespace Armadillo::Osiris;

extern void Render();
extern void Init(GLFWwindow*);
extern void Update();