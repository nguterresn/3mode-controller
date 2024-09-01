### Notes

Based on [ESP-IDF v5.1.4](https://docs.espressif.com/projects/esp-idf/en/v5.1.4/esp32/api-reference/index.html)

- Before anything do `get_idf`
- Build with `idf.py build`
- Check for serial devices with `ls /dev/tty.*`
- Flash with `idf.py -p DEVICE flash`

### CMake Notes

> In CMake terms, REQUIRES & PRIV_REQUIRES are approximate wrappers around the CMake functions target_link_libraries(... PUBLIC ...) and target_link_libraries(... PRIVATE ...).

### Arduino

- Installing [Arduino as a component](https://docs.espressif.com/projects/arduino-esp32/en/latest/esp-idf_component.html).

### Concepts about nRF24L01+

Channels control the frequency, pipes are a software term to channel.
