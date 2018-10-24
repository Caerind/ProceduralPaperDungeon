#ifndef FLOORDATA_HPP
#define FLOORDATA_HPP

#include <memory>

#include "RoomData.hpp"

class FloorData
{
    public:
        FloorData(const std::string& globalSeed, unsigned int level);
        ~FloorData();

        typedef std::unique_ptr<FloorData> Ptr;

        const std::string& getSeed() const;
        unsigned int getLevel() const;

        unsigned int getRoomCount() const;
        RoomData& getRoomData(unsigned int index);

    private:
        void generateRoomGrid();
        void generateDoors();
        void generateRooms();

        bool isRoomCreated(int x, int y, unsigned int* roomIndex = nullptr) const;

    private:
        unsigned int mSeedNum;
        std::string mSeed;
        unsigned int mLevel;
        std::vector<RoomData> mRoomData;
};

#endif // FLOORDATA_HPP
