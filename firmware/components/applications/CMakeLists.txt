idf_component_register(SRCS "app.c" "espnow.cpp" "nrf24.cpp"
  INCLUDE_DIRS "."
  PRIV_REQUIRES
    utils
    arduino
    esp_wifi
    mirf
)
