#ifndef IGAME_HPP_
#define IGAME_HPP_

class IGame
{
public:
    virtual ~IGame() = default;

    virtual void processEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif /* !IGAME_HPP_ */