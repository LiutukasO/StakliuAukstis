class Config
{
    public:
        Config ();

        bool debug = false;

        bool save();
        void print();

        unsigned long getConfigTime();
        bool isConfigSaved();

        void setHeight(float height);
        float getHeight();

    private:
        bool saved = false;
        bool load();

        char configVersion[7] = {'O','P','U','0','0','1'};
        unsigned short readFromByte = 0;
        unsigned short sizeInBytes;
        unsigned long configTime = 0;

        struct configStruct {
            char version[7];
            unsigned short writeCounter; // 65536
            char wifi_ssid[100], wifi_pass[100];
            unsigned short  wifi_port;
            char api_token[100], api_host[100];
            unsigned short  api_port;
            float height;
        } config = {"OPU001",0,"ZARSKIS_S1","GINTARAS",80,"sess_zarskis","www.ismanusnamas.lt",80,0.0};

};