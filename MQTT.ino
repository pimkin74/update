void Monitor_MQTT() {
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 10000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
  }
}


boolean reconnect() {
  String clientId = name_mqtt;
  Topic_lwt = name_mqtt + "_" + unit_id + "/Status/LWT";

  clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqttUser, mqttPassword, Topic_lwt.c_str(), willQoS, willRetain, willMessage)) {
    Mqtt_Flag = true;
    
    client.publish(Topic_lwt.c_str(), "1", true);

  } else {
    Mqtt_Flag = false;
  }
  return client.connected();
}


// Публикация в MQTT
void Publish_Msg_Mqtt(String msg_txt, String payload) {
  //boolean Retrain = Retr;
  String message = msg_txt;
  const char* msg_pointer = message.c_str();
  String msg_payload = payload;
  const char* msg_payload_pointer = msg_payload.c_str();
  client.publish(msg_pointer, msg_payload_pointer, true);
}
