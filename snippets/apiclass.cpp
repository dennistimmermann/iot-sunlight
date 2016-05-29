class API {
  public:
    size_t parseTime(String t);
    int getTimezone(String t);

    void fetchAPI(String lat, String lon);
    void fetchTime();

    int timeOffset = 0;
    size_t sunrise = 0;
    size_t sunset = 1;
};
