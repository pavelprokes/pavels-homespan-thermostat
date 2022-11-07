#include <string>
#include <HTTPClient.h>

String baseUrl = "https://ryejdvulndyktcdkwiaw.supabase.co/rest/v1/";
String table = "";
String apikey = "your apikey";
String authorization = "Bearer your authorization token";

class LogIntoSupabase {
private:
  HTTPClient http;

public:
  LogIntoSupabase() {
  }

  int logStatusAndTemp(int targetState, bool heaterState, float temp) {
    String url, data;

    url = String(baseUrl);
    url += String(table);
    //url += String("?select=*");

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", apikey);
    http.addHeader("Authorization", authorization);

    data = String("{ \"state\": \"");
    data += String(targetState);
    data += String("\", \"current_temp\": ");
    data += String(temp);
    data += String(", \"heater_state\": ");
    data += String(heaterState);
    data += String("}");
    //JSON.parse("{ \"state\": \"" + "1" + "\", \"current_temp\": " + 20 + ", \"heater_state\": " + true + "}")

    int httpResponseCode = http.POST(data);

    if (httpResponseCode > 0) {
      String response = http.getString();

      //LOG1(httpResponseCode);
      //LOG1(response);
    } else {
      LOG1("Error on sending POST: ");
      LOG1(httpResponseCode);
    }

    return httpResponseCode;

    http.end();
  }
};