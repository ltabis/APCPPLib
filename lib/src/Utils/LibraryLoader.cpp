//
// EPITECH PROJECT, 2020
// Utils
// File description:
// class for lib loader
//

#include <iostream>
#include "LibraryLoader.hpp"

Utils::LibraryLoader::~LibraryLoader()
{
    clear();
}

#if WIN32

void Utils::LibraryLoader::clear()
{
    // Terminating all handlers.
    for (auto& it : _handles)
        FreeLibrary(static_cast<HMODULE>(it.second));

    // Clearing the container.
    _handles.clear();
}

#else

void Utils::LibraryLoader::clear()
{
    for (auto &it : _handles)
        dlclose(it.second);
    _handles.clear();
}

#endif
