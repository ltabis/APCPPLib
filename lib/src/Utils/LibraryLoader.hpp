//
// Created by tabis on 10/01/2020.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <cstring>
#include <vector>
#include <string>

namespace Utils {

    /// \class LibraryLoader
    /// \brief an object that loads dynamic libraries.
    class LibraryLoader {
    public:

        /// \brief opens a library via a filepath.
        /// \param lib : path of the library to open.
        /// \return a pointer to the new allocate entrypoint object
        template<typename T>
        T *openLibrary(const std::string &lib)
        {
            T *obj = nullptr;
            std::string cat = "./" + lib;
            void *handle = dlopen(cat.c_str(), RTLD_LAZY);
            char *error = nullptr;

            if (!handle) {
                std::cout << dlerror() << std::endl;
                return nullptr;
            }
            auto func = (T *(*)())dlsym(handle, "entryPoint");
            if ((error = dlerror())) {
                std::cout << "error : " << error << std::endl;
                return nullptr;
            }
            obj = func();
            _handles.push_back(handle);
            return obj;
        }

        /// \brief opens a library via a filepath.
        /// \param directory : directory .
        /// \return a pointer to the new allocate entrypoint object
        template<typename T>
        std::vector<T *> openDirectory(const std::string &directory)
        {
            DIR *dir = opendir(directory.c_str());
            struct dirent *stream = nullptr;
            std::vector<T *> v;

            if (!dir)
                return v;
            stream = readdir(dir);
            for (std::string str; stream; stream = readdir(dir)) {
                str = stream->d_name;
                if (str.length() >= 3 && stream->d_type == DT_REG &&
                str.find_last_of(".so", std::string::npos) != std::string::npos) {
                auto newElement = openLibrary<T>(directory + "/" + str);
                if (newElement)
                    v.push_back(newElement);
                }
            }
            closedir(dir);
            return v;
        }

    private:
        // bool checkIfLibraryInMemory();

        /// \brief deletes all handles
        void deleteHandles();

        /*! Vector of all the handles of currently loaded libraries */
        std::vector<void *> _handles;
    };
}