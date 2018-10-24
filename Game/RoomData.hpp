#ifndef ROOMDATA_HPP
#define ROOMDATA_HPP

#include <vector>
#include <map>

class RoomData
{
    public:
        RoomData();
        RoomData(unsigned int roomIndex, int x, int y);
        ~RoomData();

        unsigned int getRoomIndex() const;
        int getRoomX() const;
        int getRoomY() const;

        enum DoorFlags
        {
            None = 0,
            Top = 1,
            Right = 2,
            Bottom = 4,
            Left = 8
        };

        void addConnection(DoorFlags doorFlag, unsigned int destinationIndex);
        unsigned int getConnectionIndex(DoorFlags doorFlag) const;
        DoorFlags getDoorFlags() const;
        unsigned int getDoorAmount() const;

        struct Stain
        {
            int type;
            float x;
            float y;
            float scale;
            float angle;
        };

        void addStain(int type, float x, float y, float scale, float angle);
        const Stain& getStain(unsigned int index) const;
        unsigned int getStainCount() const;

    private:
        unsigned int mRoomIndex;
        int mRoomX;
        int mRoomY;
        DoorFlags mDoorFlags;
        std::map<DoorFlags, unsigned int> mConnections;
        std::vector<Stain> mStains;
};

inline RoomData::DoorFlags operator|(RoomData::DoorFlags a, RoomData::DoorFlags b)
{
	return static_cast<RoomData::DoorFlags>(static_cast<int>(a) | static_cast<int>(b));
}

#endif // ROOMDATA_HPP
