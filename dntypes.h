#ifndef DNTYPES_H
#define DNTYPES_H


class DNTypes
{
public:
    DNTypes();
    enum Messages{
        Heartbeat = 0x10,
        Format = 0x20,
        Command = 0x30,
        Quit = 0x40,
        Sensor = 0x50
    };
};

#endif // DNTYPES_H
