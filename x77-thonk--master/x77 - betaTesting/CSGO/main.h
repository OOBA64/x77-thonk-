#ifndef MAIN_H
#define MAIN_H
#ifdef _WIN32
#pragma once
#endif

// dependencies
#include <algorithm>
#include <Windows.h>
#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <Psapi.h>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <ctime>

// helpers
#include "helpers/address.h"
#include "helpers/vector.h"
#include "helpers/color.h"
#include "helpers/util/util.h"
#include "helpers/vmt.h"

// sdk
#include "sdk/sdk.h"

// global
#include "global/interfaces/interfaces.h"
#include "global/hooks/hooks.h"
#include "global/fonts/fonts.h"
#include "global/draw/draw.h"
#include "global/global.h"

// menu
#include "menu/vars/vars.h"
#include "menu/menu.h"

// features
#include "features/resolver/resolver.h"
#include "features/visuals/visuals.h"
#include "features/aimbot/aimbot.h"
#include "features/misc/misc.h"
#include "features/hvh/hvh.h"

// setup
#include "setup/setup.h"

#endif // !MAIN_H