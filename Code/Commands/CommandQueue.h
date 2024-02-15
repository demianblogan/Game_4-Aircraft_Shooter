#pragma once

#include <queue>

#include "Command.h"

// The CommandQueue class is a container for commands in the game.
// During one frame of the game, some objects generate commands
// and send them to this queue. The first command that was
// inserted should be executed first.
class CommandQueue
{
public:
	void Push(const Command& command);
	Command Pop();
	bool IsEmpty() const;

private:
	std::queue<Command> queue;
};