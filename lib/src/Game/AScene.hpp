/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#pragma once

#include "IScene.hpp"

namespace Game
{

    /// \class AScene
    /// \brief AScene interface
    class AScene : public IScene
    {

        public:
            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            inline void setName(const std::string &name);

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            inline virtual std::string name() const;

            /// \return a scene representing the state of the scene
            /// \brief run the scenes logic
            virtual void update() = 0;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            virtual void setVisible(bool b) = 0;
            
            /// \brief remove all the entities of the scene
            virtual void remove() = 0;

        protected:

            std::string _name;
    };
}