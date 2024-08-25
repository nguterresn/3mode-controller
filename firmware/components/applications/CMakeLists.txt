idf_component_register(SRCS "nrf24.c" "espnow.cpp"
  INCLUDE_DIRS "."
  PRIV_REQUIRES
    include
    arduino
    esp_wifi
)
