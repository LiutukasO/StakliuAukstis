#ifndef Config_h
#define Config_h

class Config
{
    public:
        Config ();
        Config (unsigned short maxWriteCount);

        void setPosition(signed int position);
        signed int getPosition();
        
        unsigned short getWriteCounter();
        unsigned short getReadFromByte();

        bool save();
        void print();

    private:
        bool saved = false;
        bool load();
        bool isValidSecondConfig(unsigned short readFromByte);

        unsigned short maxWriteCount = 1000;

        char configVersion[7] = {'O','P','U','0','0','1'};
        unsigned short sizeInBytes = sizeof(this->config);
        unsigned short readFromByte = 0;

        struct configStruct {
            char version[7];
            unsigned short writeCounter;
            signed int position;
        } config = {"OPU001", 0, 0};

};

#endif