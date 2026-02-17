package com.project1.services;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.util.function.Consumer;

public class ArduinoHTTPClient {
  public static final String IP = "http://192.168.1.1";
  private HttpClient _client; 
  private final Consumer<String> logger;
  // This is our constructor for the ArduinoClient method. That means when someone makes a new ArduinoClient object,
  // these will be the default 
  public ArduinoHTTPClient(Consumer<String> logger) {
    this.logger = logger;

    // we will start creating our HTTP request one part at a time (thats why we use the builder)
    _client = HttpClient.newBuilder()

      // for now we just make the HTTP request have a default timeout of 5 seconds, the rest we keep as default from the builder
      .connectTimeout(Duration.ofSeconds(2))

      // creates a brand new HttpClient object with that 5 second default 
      .build();
  }

  ///   This function sends a GET request to the arduino server at the given endpoint.
  ///   
  ///   e.g. Send("/forward") -> Sends the request, should move the robot forward.

  public HttpResponse<String> send(String endpoint) throws Exception {
    int tries = 0;
    while (tries < 3) {
      try {
        String url = IP + endpoint;
        HttpRequest req = HttpRequest.newBuilder()
        .uri(URI.create(url))
        .timeout(Duration.ofSeconds(2))
        .GET()
        .build();
          
        return _client.send(req, HttpResponse.BodyHandlers.ofString());
      } catch (Exception e) {
          tries++;
          logger.accept("HTTP Connection Failed (Retry attempt " + tries + "/3): " + e.getMessage());
          logger.accept("Retrying...");
          try { Thread.sleep(1200); } catch (InterruptedException ignored) {};
          
      }
    }

    return null;
  }
}
