#ifndef ROOMDATA_HPP
#define ROOMDATA_HPP

class RoomData
{
    public:
        RoomData();
        ~RoomData();

        enum DoorFlags
        {
            None = 0,
            Top = 1,
            Right = 2,
            Bottom = 4,
            Left = 8
        };

        void setDoorFlags(DoorFlags doorFlags);
        DoorFlags getDoorFlags() const;

    private:
        DoorFlags mDoorFlags;
};

inline RoomData::DoorFlags operator|(RoomData::DoorFlags a, RoomData::DoorFlags b)
{
	return static_cast<RoomData::DoorFlags>(static_cast<int>(a) | static_cast<int>(b));
}

#endif // ROOMDATA_HPP
