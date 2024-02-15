#include "CommandQueue.h"

void CommandQueue::Push(const Command& command)
{
	queue.push(command);
}

Command CommandQueue::Pop()
{
	Command command = queue.front();
	queue.pop();

	return command;
}

bool CommandQueue::IsEmpty() const
{
	return queue.empty();
}