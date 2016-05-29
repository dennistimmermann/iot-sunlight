class Config {
  public:
    void begin();

    void handleRoot();
    void handleSave();

    void startAP(const char* ssid, const char* password);
    void loop();

    String getValue(int start);
    void saveValue(int start, String value);

  private:
    String _ssid = "";
    String _pass = "";
    String _lat = "";
    String _lon = "";
};
