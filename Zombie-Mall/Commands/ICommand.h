
#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

class ICommand
{
public:
    virtual ~ICommand() {}

    virtual void Execute() = 0;

    virtual void Undo() {}
};

#endif // !_ICOMMAND_H_
