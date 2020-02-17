//
// EPITECH PROJECT, 2020
// L
// File description:
// class for lib loader
//

#pragma once

#include <string>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include "Logger.hpp"

/// @def LIB_EXTENSION
/// @brief extention of shared library to load
#ifdef WIN32
    #include <windows.h>

    constexpr auto const LIB_EXTENSION = ".dll";
#else
    #include <sys/types.h>
    #include <dirent.h>
    #include <dlfcn.h>

    constexpr auto const LIB_EXTENSION = ".so";
#endif

namespace Utils
{
    /// \class LibraryLoader
    /// \brief templated class used to load shared library
    class LibraryLoader
    {
    public:
        /// \brief Destructor
        ~LibraryLoader();

        /// \brief get an instance of a shared library by calling entrypoint.c_str() function.
        /// \param file : path to the shared library.
        /// \param entrypoint.c_str() : entry point to be loaded.
        /// \return an instance of the disered object.
        template<typename T> T *getInstance(const std::string &filepath, const std::string &entrypoint);

        /// \brief open and return all instance of library in a specific directory.
        /// \param directory : path to the directory to search shared libraries.
        /// \return a vector of the needed instance.
        template<typename T> std::vector<T *> getDirectory(const std::string &directory);

        /// \brief clear all saved pointers librairies
        void clear();

    private:
        std::unordered_map<std::string, void *> _handles;
    };

    template<typename T>
    std::vector<T *> LibraryLoader::getDirectory(const std::string &directory)
    {
        std::vector<T *> libraries;

        // Check wether the directory exists or not.
        if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
            return libraries;

        // Reading the directory.
        for (const auto &file : std::filesystem::directory_iterator(directory))
        {
            // Getting the name of the file and position of the extension.
            std::string filepath = file.path().string();
            auto posExtension = filepath.find_last_of(".", std::string::npos);

            // Check wether the file is a dynamic library or not.
            if (file.is_regular_file() && posExtension != std::string::npos && filepath.substr(posExtension) == LIB_EXTENSION)
            {
                auto newElement = getInstance<T>(filepath);

                // Adding the library to the vector.
                if (newElement)
                    libraries.push_back(newElement);
            }
        }
        return libraries;
    }


#ifdef WIN32

    template<typename T>
    T *LibraryLoader::getInstance(const std::string &filepath, const std::string &entrypoint)
    {
        T *(*fct)(void) = nullptr;

        // Load the library.
        auto libPtr = _handles.find(filepath);

        // Check if the libraire instance was already loaded.
        if (libPtr != _handles.end())
        {
            // Getting the entry point. (casts are for windows -> can't make a static cast on the GetProcAddress function)
            fct = reinterpret_cast<T *(*)(void)>(GetProcAddress(static_cast<HMODULE>(libPtr->second), entrypoint.c_str()));

            if (fct)
                return (fct());
            else
                Debug::Logger::printDebug(Debug::WARNING, "Can't find the dll entry point.", "Utils::LibraryLoader::getInstance");
        }
        else
        {
            // Getting the library.
            std::cout << filepath.c_str() << std::endl;
            HINSTANCE newLibrary = LoadLibrary(filepath.c_str());

            if (newLibrary)
            {
                // Storing the handler.
                _handles.emplace(filepath, newLibrary);

                // Getting the entry point. (casts are for windows)
                fct = reinterpret_cast<T *(*)(void)>(GetProcAddress(static_cast<HMODULE>(newLibrary), entrypoint.c_str()));
                if (fct)
                    return (fct());
                Debug::Logger::printDebug(Debug::WARNING, "Can't find the dll entry point.", "Utils::LibraryLoader::getInstance");
            } 
            Debug::Logger::printDebug(Debug::WARNING, filepath + " couldn't be loaded.", "Utils::LibraryLoader::getInstance");
        }
        return (nullptr);
    }

#else

    template<typename T>
    T *LibraryLoader::getInstance(const std::string &filepath, const std::string &entrypoint)
    {
        T *(*fct)(void) = nullptr;
        auto lib_ptr = _handles.find(filepath);

        // Check if the libraire instance was already loaded.
        if (lib_ptr != _handles.end())
        {
            fct = static_cast<T *(*)()>(dlsym((*lib_ptr).second, entrypoint.c_str()));
            if (fct)
                return fct();
            Debug::Logger::printDebug(Debug::ERROR, filepath + " couldn't be loaded.", "Libraryloader::getInstance");
        }
        else
        {
            // Loading a new library.
            void *library = dlopen(filepath.c_str(), RTLD_LAZY);

            if (library)
            {
                fct = static_cast<T *(*)()>(dlsym(library, entrypoint.c_str()));

                if (fct)
                {
                    _handles.emplace(filepath, library);
                    return (fct());
                }
                Debug::Logger::printDebug(Debug::ERROR, filepath + " couldn't find the " + entrypoint.c_str() + " entry point." , "Libraryloader::getInstance");
            }
            Debug::Logger::printDebug(Debug::ERROR, filepath + " couldn't be loaded.", "Libraryloader::getInstance");
        }
        return (nullptr);
    }

#endif

}