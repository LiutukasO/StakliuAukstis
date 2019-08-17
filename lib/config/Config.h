class Config
{
    public:
        Config ();

        bool debug = false;

        bool save();
        void print();

        unsigned long getConfigTime();
        bool isConfigSaved();

        void setHeight(unsigned int height);
        unsigned int getHeight();

    private:
        bool saved = false;
        bool load();

        char CONFIG_VERSION[7] = "OPU001";
        unsigned short CONFIG_START = 0;
        unsigned short CONFIG_SIZE;
        unsigned long config_time = 0;

        struct configStruct {
            char version[7];
            unsigned short write_counter; // 65536
            char wifi_ssid[100], wifi_pass[100];
            unsigned short  wifi_port;
            char api_token[100], api_host[100];
            unsigned short  api_port;
            unsigned int height;
        } config = {"OPU001",0,"ZARSKIS_S1","GINTARAS",80,"sess_zarskis","www.ismanusnamas.lt",80,320};

};