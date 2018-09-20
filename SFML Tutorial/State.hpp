#pragma once

namespace g35 {//abstract class for States of the game
    class State{
    public:
        virtual void Init() = 0;
        virtual void HandleInput() = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw(float dt) = 0;
        virtual void Pause(){}
        virtual void Resume() {}
    };
}
